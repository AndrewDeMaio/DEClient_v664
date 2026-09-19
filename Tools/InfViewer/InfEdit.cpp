// InfEdit.cpp - byte-level edit operations on a decoded .inf image.
//
// Every operation takes the current bytes plus the InfDoc decoded from those
// same bytes, and returns a new byte image. The caller re-decodes the result
// and keeps it only when the whole file is still accounted for.
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include "InfParser.h"

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cwctype>

namespace {

std::wstring efmt(const wchar_t* f, ...)
{
    wchar_t buf[512];
    va_list ap;
    va_start(ap, f);
    _vsnwprintf_s(buf, _countof(buf), _TRUNCATE, f, ap);
    va_end(ap);
    return buf;
}

long long readLE(const uint8_t* p, int size, bool asSigned)
{
    unsigned long long v = 0;
    for (int i = 0; i < size; i++) v |= (unsigned long long)p[i] << (8 * i);
    if (asSigned && size < 8)
    {
        unsigned long long sign = 1ull << (size * 8 - 1);
        if (v & sign) return (long long)v - (long long)(sign << 1);
    }
    return (long long)v;
}

void writeLE(uint8_t* p, int size, long long v)
{
    for (int i = 0; i < size; i++) p[i] = (uint8_t)((unsigned long long)v >> (8 * i));
}

bool parseNumber(std::wstring text, long long& v)
{
    while (!text.empty() && iswspace(text.back())) text.pop_back();
    size_t s = 0;
    while (s < text.size() && iswspace(text[s])) s++;
    text = text.substr(s);
    if (text.empty()) return false;
    wchar_t* end = nullptr;
    v = wcstoll(text.c_str(), &end, 0);   // base 0: decimal, or 0x.. hex
    return end && *end == L'\0';
}

bool fits(long long v, int size)
{
    if (size >= 8) return true;
    long long          lo = -(1ll << (size * 8 - 1));
    unsigned long long hi = (1ull << (size * 8)) - 1;
    return v >= lo && (v < 0 || (unsigned long long)v <= hi);
}

bool checkRec(const InfDoc& doc, size_t rec, std::wstring& err)
{
    if (rec >= doc.records.size()) { err = L"No such record."; return false; }
    if (doc.records[rec].length == 0)
    {
        err = L"This schema does not track record boundaries, so records cannot be cloned or deleted here.";
        return false;
    }
    return true;
}

void bump(std::vector<uint8_t>& out, size_t off, int size, long long delta)
{
    long long v = readLE(&out[off], size, false);
    writeLE(&out[off], size, v + delta);
}

std::string mstring(const std::string& bytes)
{
    std::string s(4, '\0');
    writeLE((uint8_t*)&s[0], 4, (long long)bytes.size());
    return s + bytes;
}

} // namespace

bool InfWideToBytes(const std::wstring& w, std::string& out)
{
    out.clear();
    if (w.empty()) return true;
    BOOL bad = FALSE;
    int len = WideCharToMultiByte(949, WC_NO_BEST_FIT_CHARS, w.c_str(), (int)w.size(), nullptr, 0, nullptr, &bad);
    if (len <= 0 || bad) return false;
    out.resize((size_t)len);
    WideCharToMultiByte(949, WC_NO_BEST_FIT_CHARS, w.c_str(), (int)w.size(), &out[0], len, nullptr, &bad);
    return !bad;
}

long long InfReadInt(const std::vector<uint8_t>& data, const InfField& f, bool asSigned)
{
    if (f.kind != INF_INT || f.offset + (size_t)f.size > data.size()) return 0;
    return readLE(&data[f.offset], f.size, asSigned);
}

std::wstring InfReadStr(const std::vector<uint8_t>& data, const InfField& f)
{
    if (f.kind != INF_STR || f.offset + 4 > data.size()) return L"";
    size_t len = (size_t)readLE(&data[f.offset], 4, false);
    if (f.offset + 4 + len > data.size()) return L"";
    return InfBytesToWide((const char*)&data[f.offset + 4], len);
}

bool InfSetField(const InfDoc& doc, const std::vector<uint8_t>& in, size_t rec, size_t field,
                 const std::wstring& text, std::vector<uint8_t>& out, std::wstring& err)
{
    if (rec >= doc.records.size() || field >= doc.records[rec].fields.size()) { err = L"No such field."; return false; }
    const InfField& f = doc.records[rec].fields[field];
    if (f.kind == INF_NONE)
    {
        err = L"This value is derived from several bytes or is a structural count. "
              L"Edit the individual fields instead, or add/remove list lines from the Edit menu.";
        return false;
    }
    out = in;
    if (f.kind == INF_INT)
    {
        long long v;
        if (!parseNumber(text, v)) { err = L"Enter a whole number (decimal, or 0x.. for hex)."; return false; }
        if (!fits(v, f.size)) { err = efmt(L"%lld does not fit in %d byte(s).", v, f.size); return false; }
        writeLE(&out[f.offset], f.size, v);
        return true;
    }
    std::string bytes;
    if (!InfWideToBytes(text, bytes)) { err = L"The text contains a character that cannot be stored as CP949 (the Korean code page)."; return false; }
    if (bytes.size() > 0xFFFF) { err = L"String too long."; return false; }
    std::string ins = mstring(bytes);
    out.erase(out.begin() + f.offset, out.begin() + f.offset + f.length);
    out.insert(out.begin() + f.offset, ins.begin(), ins.end());
    return true;
}

bool InfCloneRecord(const InfDoc& doc, const std::vector<uint8_t>& in, size_t rec,
                    std::vector<uint8_t>& out, std::wstring& err, long long* newId)
{
    if (newId) *newId = -1;
    if (doc.tableKind == 0) { err = L"This file is not a single record table; the viewer cannot add records to it."; return false; }
    if (!checkRec(doc, rec, err)) return false;
    const InfRecord& r = doc.records[rec];
    if (doc.tableEnd > in.size() || r.offset + r.length > in.size()) { err = L"Record span is outside the file."; return false; }

    out = in;
    std::string copy((const char*)&in[r.offset], r.length);
    size_t at = doc.tableEnd;
    out.insert(out.begin() + at, copy.begin(), copy.end());
    bump(out, doc.countOffset, doc.countSize, +1);

    if (doc.tableKind == 2 && doc.idFieldIndex >= 0 && (size_t)doc.idFieldIndex < r.fields.size())
    {
        const InfField& idf = r.fields[(size_t)doc.idFieldIndex];
        if (idf.kind == INF_INT)
        {
            long long mx = -1;
            for (const auto& other : doc.records)
                if ((size_t)doc.idFieldIndex < other.fields.size())
                    mx = std::max(mx, InfReadInt(in, other.fields[(size_t)doc.idFieldIndex], false));
            long long id = mx + 1;
            if (!fits(id, idf.size)) { err = L"No free id left in this table."; return false; }
            writeLE(&out[at + (idf.offset - r.offset)], idf.size, id);
            if (newId) *newId = id;
        }
    }
    return true;
}

bool InfDeleteRecord(const InfDoc& doc, const std::vector<uint8_t>& in, size_t rec,
                     std::vector<uint8_t>& out, std::wstring& err)
{
    if (doc.tableKind == 0) { err = L"This file is not a single record table; the viewer cannot delete records from it."; return false; }
    if (!checkRec(doc, rec, err)) return false;
    const InfRecord& r = doc.records[rec];
    out = in;
    out.erase(out.begin() + r.offset, out.begin() + r.offset + r.length);
    bump(out, doc.countOffset, doc.countSize, -1);
    return true;
}

bool InfListAppend(const InfDoc& doc, const std::vector<uint8_t>& in, size_t rec, size_t list,
                   const std::wstring& text, std::vector<uint8_t>& out, std::wstring& err)
{
    if (rec >= doc.records.size() || list >= doc.records[rec].lists.size()) { err = L"No such list."; return false; }
    const InfList& L = doc.records[rec].lists[list];
    if (!fits(L.count + 1, L.countSize) || (L.countSize == 1 && L.count >= 255)) { err = L"The list is full."; return false; }
    std::string bytes;
    if (!InfWideToBytes(text, bytes)) { err = L"The text contains a character that cannot be stored as CP949 (the Korean code page)."; return false; }
    out = in;
    std::string ins = mstring(bytes);
    out.insert(out.begin() + L.insertOffset, ins.begin(), ins.end());
    bump(out, L.countOffset, L.countSize, +1);
    return true;
}

bool InfListRemoveLast(const InfDoc& doc, const std::vector<uint8_t>& in, size_t rec, size_t list,
                       std::vector<uint8_t>& out, std::wstring& err)
{
    if (rec >= doc.records.size() || list >= doc.records[rec].lists.size()) { err = L"No such list."; return false; }
    const InfList& L = doc.records[rec].lists[list];
    if (L.count <= 0) { err = L"The list is already empty."; return false; }
    out = in;
    out.erase(out.begin() + L.lastOffset, out.begin() + L.lastOffset + L.lastLength);
    bump(out, L.countOffset, L.countSize, -1);
    return true;
}
