// InfParser.h - decoders (and byte-level editors) for DarkEden client
// "Data\Info\*.inf" tables.
//
// Every layout here is transcribed from the client's own LoadFromFile bodies
// (UI/game/*.cpp, UI/*.cpp, MLib/MString.cpp, DXLib/CTypeTable.h). Where a
// file is no longer loaded by the client the schema says so in its note.
//
// Editing never patches bytes blindly: the decoder records where each field,
// each string list and each record sits, the edit functions splice a new byte
// image, and the caller re-decodes that image and only keeps it when the whole
// file is still accounted for.
#pragma once

#include <cstdint>
#include <string>
#include <vector>

enum InfKind
{
    INF_NONE = 0,   // composite / derived value, not editable
    INF_INT,        // little-endian integer of `size` bytes at `offset`
    INF_STR         // MString: 4-byte length + CP949 bytes at `offset`
};

struct InfField
{
    std::wstring name;
    std::wstring value;
    size_t       offset = 0;
    size_t       length = 0;
    InfKind      kind   = INF_NONE;
    int          size   = 0;
};

// A string list inside a record (count + MStrings) that can grow or shrink.
struct InfList
{
    std::wstring name;
    size_t       countOffset  = 0;
    int          countSize    = 4;
    int          count        = 0;
    size_t       insertOffset = 0;   // where a new element goes (after the last one)
    size_t       lastOffset   = 0;   // span of the last element, for removal
    size_t       lastLength   = 0;
};

struct InfRecord
{
    std::wstring          key;      // table index or map id
    std::wstring          summary;  // one-line description for the list
    size_t                offset = 0;
    size_t                length = 0;
    std::vector<InfField> fields;
    std::vector<InfList>  lists;
};

struct InfDoc
{
    std::wstring              schemaId;
    std::wstring              schemaTitle;
    std::wstring              note;
    std::vector<InfField>     header;
    std::vector<InfRecord>    records;
    std::vector<std::wstring> warnings;
    size_t                    fileSize = 0;
    size_t                    consumed = 0;
    bool                      ok       = true;   // false: decoder threw

    // Single-table files: where the record count lives and where records end,
    // so records can be cloned / deleted. tableKind 0 = not a single table.
    int    tableKind    = 0;   // 1 = CTypeTable (index is the id), 2 = keyed (an id field is stored)
    size_t countOffset  = 0;
    int    countSize    = 4;
    size_t tableEnd     = 0;
    int    idFieldIndex = -1;  // field holding the record id, for tableKind 2

    bool complete() const { return ok && consumed == fileSize && warnings.empty(); }
};

struct InfSchemaInfo
{
    const wchar_t* id;
    const wchar_t* title;
};

// All selectable schemas, in display order.
const std::vector<InfSchemaInfo>& InfSchemaList();

// Pick a schema from the file name (and, failing that, the content).
std::wstring InfGuessSchema(const std::wstring& path, const std::vector<uint8_t>& data);

// Decode `data` with the given schema id. Never throws; failures land in doc.ok/warnings.
void InfParse(const std::vector<uint8_t>& data, const std::wstring& schemaId, InfDoc& doc);

// Whole document as printable text (what Export writes).
std::wstring InfDocToText(const InfDoc& doc, const std::wstring& sourcePath);

// CP949 (EUC-KR) bytes <-> UTF-16.
std::wstring InfBytesToWide(const char* s, size_t n);
bool         InfWideToBytes(const std::wstring& w, std::string& out);   // false if a char has no CP949 form

// Raw values behind a field (independent of how the field is displayed).
long long    InfReadInt(const std::vector<uint8_t>& data, const InfField& f, bool asSigned);
std::wstring InfReadStr(const std::vector<uint8_t>& data, const InfField& f);

// Editing. Each produces a new byte image in `out`; on failure returns false with `err` set.
bool InfSetField(const InfDoc& doc, const std::vector<uint8_t>& in, size_t rec, size_t field,
                 const std::wstring& text, std::vector<uint8_t>& out, std::wstring& err);
bool InfCloneRecord(const InfDoc& doc, const std::vector<uint8_t>& in, size_t rec,
                    std::vector<uint8_t>& out, std::wstring& err, long long* newId);
bool InfDeleteRecord(const InfDoc& doc, const std::vector<uint8_t>& in, size_t rec,
                     std::vector<uint8_t>& out, std::wstring& err);
bool InfListAppend(const InfDoc& doc, const std::vector<uint8_t>& in, size_t rec, size_t list,
                   const std::wstring& text, std::vector<uint8_t>& out, std::wstring& err);
bool InfListRemoveLast(const InfDoc& doc, const std::vector<uint8_t>& in, size_t rec, size_t list,
                       std::vector<uint8_t>& out, std::wstring& err);
