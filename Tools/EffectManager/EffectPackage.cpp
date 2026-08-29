#include "framework.h"
#include "EffectPackage.h"

#include <fstream>
#include <iomanip>
#include <sstream>

bool EffectPackage::Open(const std::wstring& filename)
{
    Close();

    if (!LoadFile(filename))
    {
        return false;
    }

    m_filename = filename;

    return true;
}


void EffectPackage::Close()
{
    m_filename.clear();
    m_data.clear();
}


bool EffectPackage::IsOpen() const
{
    return !m_data.empty();
}


size_t EffectPackage::GetSize() const
{
    return m_data.size();
}


bool EffectPackage::LoadFile(const std::wstring& filename)
{
    std::ifstream file(
        filename,
        std::ios::binary | std::ios::ate
    );

    if (!file.is_open())
    {
        return false;
    }

    std::streamsize fileSize = file.tellg();

    if (fileSize <= 0)
    {
        return false;
    }

    file.seekg(0, std::ios::beg);

    m_data.resize(static_cast<size_t>(fileSize));

    if (!file.read(
        reinterpret_cast<char*>(m_data.data()),
        fileSize))
    {
        m_data.clear();

        return false;
    }

    return true;
}

std::wstring EffectPackage::DumpBytes(size_t count) const 
{
    if (m_data.empty()) return L"";

    if (count > m_data.size()) count = m_data.size();

    std::wstringstream output;

    output << L"First " << count << L"bytes:";

    for (size_t i = 0; i < count; i++) {

        if (i % 16 == 0) {
            output << L"\r\n";
            output << std::hex << std::setw(8) << std::setfill(L'0') << i << L" ";
        }

        output << std::hex << std::setw(2) << std::setfill(L'0') << static_cast<unsigned>(m_data[i]) << L' ';
    }

    return output.str();
}

std::wstring EffectPackage::miniDump(size_t count) const
{
    std::wstringstream output;

    size_t valueCount = m_data.size() / sizeof(uint16_t);

    if (count > valueCount) count = valueCount;

    const uint16_t* values =
        reinterpret_cast<const uint16_t*>(m_data.data());

    for (size_t i = 0; i < count; ++i)
    {
        if (i % 8 == 0)
        {
            output << L"\r\n";

            output
                << std::hex
                << std::setw(8)
                << std::setfill(L'0')
                << (i * sizeof(uint16_t))
                << L"  ";
        }

        output
            << std::setw(4)
            << std::setfill(L'0')
            << values[i]
            << L' ';
    }

    return output.str();
}