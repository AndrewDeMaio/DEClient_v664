import re
import sys
import shutil
import time

import requests


TRANSLATE_URL = "https://translate.googleapis.com/translate_a/single"

BATCH_SIZE = 10

# Delay between successful batches.
BATCH_DELAY = 2

# Retry delays when Google returns HTTP 429.
RETRY_DELAYS = [5, 10, 20, 40, 60]


def contains_korean(text):
    return re.search(
        r"[\uac00-\ud7a3]",
        text
    ) is not None


def translate_batch(comments):
    """
    Send one batch of comments to Google and wait for the response.

    Comments are separated by a unique marker so they can be split
    back apart after translation.
    """

    marker = "\n<<<COMMENT_SEPARATOR_9F3A>>>\n"

    combined = marker.join(comments)

    params = {
        "client": "gtx",
        "sl": "ko",
        "tl": "en",
        "dt": "t",
        "q": combined
    }

    for attempt in range(len(RETRY_DELAYS) + 1):

        try:

            print()
            print(
                "Sending batch of "
                + str(len(comments))
                + " comments..."
            )

            response = requests.get(
                TRANSLATE_URL,
                params=params,
                timeout=30
            )

            if response.status_code == 429:

                if attempt >= len(RETRY_DELAYS):

                    print("Too many requests. Giving up on batch.")

                    return None

                delay = RETRY_DELAYS[attempt]

                print(
                    "Rate limited. Waiting "
                    + str(delay)
                    + " seconds..."
                )

                time.sleep(delay)

                continue

            response.raise_for_status()

            result = response.json()

            translated = ""

            for item in result[0]:

                if item[0]:
                    translated += item[0]

            translated_comments = translated.split(
                "<<<COMMENT_SEPARATOR_9F3A>>>"
            )

            if len(translated_comments) != len(comments):

                print()
                print("WARNING:")
                print(
                    "Google returned "
                    + str(len(translated_comments))
                    + " comments instead of "
                    + str(len(comments))
                )

                return None

            return translated_comments

        except Exception as e:

            print()
            print("Translation error:")
            print("  " + str(e))

            if attempt >= len(RETRY_DELAYS):

                return None

            delay = RETRY_DELAYS[attempt]

            print(
                "Retrying in "
                + str(delay)
                + " seconds..."
            )

            time.sleep(delay)

    return None


def translate_comments(comments):
    """
    Translate all comments in sequential batches.

    The next batch is NOT sent until the previous batch has
    completely returned and been processed.
    """

    results = []

    total = len(comments)

    for start in range(0, total, BATCH_SIZE):

        end = min(
            start + BATCH_SIZE,
            total
        )

        batch = comments[start:end]

        print()
        print("=" * 70)
        print(
            "Batch "
            + str((start // BATCH_SIZE) + 1)
            + " / "
            + str((total + BATCH_SIZE - 1) // BATCH_SIZE)
        )
        print("=" * 70)

        translated = translate_batch(batch)

        if translated is None:

            print()
            print("BATCH FAILED.")
            print(
                "The source file will NOT be modified."
            )

            return None

        results.extend(translated)

        # Wait before sending the next batch.
        if end < total:

            print()
            print(
                "Batch complete. Waiting "
                + str(BATCH_DELAY)
                + " seconds before next batch..."
            )

            time.sleep(BATCH_DELAY)

    return results


def process_file(filename):

    print()
    print("Reading:")
    print("  " + filename)
    print()

    # ------------------------------------------------------------
    # Read the source as CP949.
    # ------------------------------------------------------------

    with open(
        filename,
        "r",
        encoding="cp949",
        newline=""
    ) as f:

        source = f.read()

    # ------------------------------------------------------------
    # Find all comments.
    # ------------------------------------------------------------

    comments = []

    def find_line_comment(match):

        comment = match.group(0)

        body = comment[2:]

        if contains_korean(body):

            comments.append(body)

        return comment

    source_with_markers = re.sub(
        r"//[^\r\n]*",
        find_line_comment,
        source
    )

    def find_block_comment(match):

        comment = match.group(0)

        body = comment[2:-2]

        if contains_korean(body):

            comments.append(body)

        return comment

    re.sub(
        r"/\*.*?\*/",
        find_block_comment,
        source,
        flags=re.DOTALL
    )

    # ------------------------------------------------------------
    # Nothing to translate.
    # ------------------------------------------------------------

    if not comments:

        print("No Korean comments found.")
        return

    print(
        "Found "
        + str(len(comments))
        + " Korean comments."
    )

    # ------------------------------------------------------------
    # Translate ALL comments before touching the file.
    # ------------------------------------------------------------

    translations = translate_comments(comments)

    if translations is None:

        print()
        print("No changes were made to the source file.")
        return

    # ------------------------------------------------------------
    # Replace comments.
    #
    # We use an iterator so translations are inserted in the
    # exact same order they were discovered.
    # ------------------------------------------------------------

    translation_index = 0

    def replace_line_comment(match):

        nonlocal translation_index

        prefix = match.group(1)
        body = match.group(2)

        if contains_korean(body):

            translated = translations[translation_index]

            translation_index += 1

            return prefix + translated

        return match.group(0)

    source = re.sub(
        r"(//)([^\r\n]*)",
        replace_line_comment,
        source
    )

    def replace_block_comment(match):

        nonlocal translation_index

        opening = match.group(1)
        body = match.group(2)
        closing = match.group(3)

        if contains_korean(body):

            translated = translations[translation_index]

            translation_index += 1

            return (
                opening +
                translated +
                closing
            )

        return match.group(0)

    source = re.sub(
        r"(/\*)(.*?)(\*/)",
        replace_block_comment,
        source,
        flags=re.DOTALL
    )

    # ------------------------------------------------------------
    # Safety check.
    # ------------------------------------------------------------

    if translation_index != len(translations):

        print()
        print("ERROR:")
        print("Translation count does not match comment count.")
        print("NO changes were made.")
        return

    # ------------------------------------------------------------
    # Backup original.
    # ------------------------------------------------------------

    backup = filename + ".bak"

    shutil.copy2(
        filename,
        backup
    )

    # ------------------------------------------------------------
    # Write CP949.
    # ------------------------------------------------------------

    with open(
        filename,
        "w",
        encoding="cp949",
        newline=""
    ) as f:

        f.write(source)

    print()
    print("=" * 70)
    print("SUCCESS")
    print("=" * 70)
    print()
    print(
        "Translated "
        + str(len(translations))
        + " comments."
    )
    print()
    print("Original backed up to:")
    print("  " + backup)
    print()


def main():

    if len(sys.argv) != 2:

        print()
        print("Usage:")
        print(
            "  python3 translate_comment.py <file>"
        )
        print()

        return

    filename = sys.argv[1]

    try:

        process_file(filename)

    except Exception as e:

        print()
        print("ERROR:")
        print("  " + str(e))
        print()


if __name__ == "__main__":
    main()