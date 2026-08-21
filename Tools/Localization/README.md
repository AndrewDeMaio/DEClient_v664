# Localization tooling

Scripts for translating DEClient's Korean text to English.

## Which file feeds what

This is the part that is easy to get wrong. There are four separate sources and
they are not interchangeable.

| What you see in game            | Comes from                                  | Side   |
|---------------------------------|---------------------------------------------|--------|
| UI labels, system messages      | `Data\Info\String.inf`                      | client |
| NPC dialogue and menu options   | `Data\Info\NPCScript.inf`                   | client |
| Floating name above an NPC      | `Data\Info\creature.inf` (creature table)   | client |
| Speaker name in the dialogue box| `NPCScript.inf` -> `OwnerID`                | client |
| Front-page buttons              | `TitleMenuDefault.spk`, `CommonButton.spk`  | client |

All of it is client side. Two consequences:

* **No rebuild is needed.** These are data files. But the client reads them
  once at startup, so you must fully close and reopen it to see changes.
* **Loose files override the dpk** (`_access` check in `RarFile.cpp` and
  `vfstream.cpp`), so editing the file on disk is enough. Never repack the
  archives - see the memory note on `.rpk`.

### The server database is NOT the source for NPC dialogue

`GCNPCAsk` carries only `ObjectID + ScriptID + NPCID`. The server never sends
the text; the client resolves the ScriptID against `NPCScript.inf`. Translating
the server's `Script` table changes nothing on screen. It was done anyway (the
English is there, and `npcscript.ps1` reads it), but the client file is what
matters.

Likewise `NPC.Name` in the database is **not** the floating label outside zones
1500-1506 - `GCAddNPCHandler` uses the client creature table instead. Do not
rename NPCs in the database: `NPC.cpp:182` uses that same column as the trigger
join key, so renaming there strikes the NPC mute.

Note some `NPC.Name` values are stored in Chinese GBK, not Korean CP949, so
they decode to Hanja nonsense under CP949. They are lookup keys only.

## Tools

| Script                   | Purpose                                              |
|--------------------------|------------------------------------------------------|
| `stringtable.ps1`        | read/write `String.inf` (round-trip verified)         |
| `translations.ps1`       | 1838 index -> English entries for `String.inf`        |
| `apply_translations.ps1` | validate + install `String.inf`                       |
| `npcscriptinf.ps1`       | read/write `NPCScript.inf` (round-trip verified)      |
| `npcscript.ps1`          | read/write the server `Script` table                  |
| `npc_rename.ps1`         | rename NPCs in `creature.inf` + `NPCScript.inf`       |
| `npc_port_to_client.ps1` | copy DB translations into `NPCScript.inf`             |
| `npc_*_en.ps1`           | applied dialogue for Tanya / Zach / Kaiser            |
| `npc_carmen_en.sql`      | applied dialogue for Carmen                           |

Rebuild `String.inf` any time with:

    powershell -File Tools\Localization\apply_translations.ps1

## Rules that will bite you

* **printf specifiers must match the source exactly, in order.** The client
  passes arguments positionally. `apply_translations.ps1` refuses to write if
  they differ. Beware a literal `50% discount` - that parses as the specifier
  `% d`. Phrase percentages so the `%` lands at the end of the clause.
* **Menu option order is load-bearing.** `Triggers` maps AnswerID 1..N to the
  Nth option. Zach's script 4105 maps options 1-8 to
  SWORD/BLADE/AR/SMG/SG/SR/CROSS/MACE - reordering hands out the wrong weapon.
* **Option separators differ per NPC** in the server table: Tanya `CR LF`,
  Zach `LF`, Kaiser `LF TAB TAB`, Carmen `LF TAB`. `Set-DEScript` reuses
  whatever the source row had rather than assuming. (`NPCScript.inf` avoids
  this entirely - options are separate array entries there.)
* **Encoding.** Data files are CP949. PowerShell 5.1 reads `.ps1` files as
  ANSI, so a Korean literal inside a script is corrupted before it can match
  CP949 data - build such patterns from codepoints instead.
* **`LENGTH` vs `CHAR_LENGTH` cannot detect Korean** on a latin1 MySQL column;
  they are always equal. Check for bytes >= 0x80 instead.

## Rollbacks

`rollback/` holds byte-exact `UNHEX()` statements for the server `Script` rows.
Client files have `.orig` backups beside them:

* `Release\Data\Info\NPCScript.inf.orig`
* `Release\Data\Info\creature.inf.orig`
* `Release\Data\Info\String.inf.kr` (the original Korean string table)

`reference/slayer_teachers_kr.txt` is the original Korean for the three Slayer
skill teachers.

## Still Korean

* 15 idle RandomSay lines (Zach 4118-4124, Tanya 4310-4317) have no entry in
  `NPCScript.inf` at all - nothing to translate.
* `String.inf` index 1608 is the original publisher's data-consent notice
  naming real companies. Left as shipped deliberately; replace it with your own
  privacy text.
* Front-page button labels are pixels in `.spk` sprites, not text.
