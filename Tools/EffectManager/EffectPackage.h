#pragma once

#include <cstdint>
#include <string>
#include <vector>

class EffectPackage
{
public:

    bool Open(const std::wstring& filename);
    void Close();
    bool IsOpen() const;
    size_t GetSize() const;
    std::wstring DumpBytes(size_t count) const;
	std::wstring miniDump(size_t count) const;

private:

    bool LoadFile(const std::wstring& filename);

    std::wstring m_filename;
    std::vector<uint8_t> m_data;
};