#include "EfpkgFile.h"

#include <fstream>
#include <iostream>

bool EfpkgFile::Open(const std::string& filename)
{
    Close();

    m_fileName = filename;

    std::ifstream file(
        filename,
        std::ios::binary | std::ios::ate
    );

    if (!file.is_open())
    {
        return false;
    }

    std::streamsize size = file.tellg();

    if (size <= 0)
    {
        return false;
    }

    file.seekg(0, std::ios::beg);

    m_data.resize(static_cast<size_t>(size));

    if (!file.read(
        reinterpret_cast<char*>(m_data.data()),
        size))
    {
        Close();
        return false;
    }

    return Parse();
}


void EfpkgFile::Close()
{
    m_fileName.clear();
    m_data.clear();
    m_assets.clear();
}


bool EfpkgFile::IsOpen() const
{
    return !m_data.empty();
}


const std::vector<uint8_t>& EfpkgFile::GetData() const
{
    return m_data;
}


const std::vector<EfpkgAsset>& EfpkgFile::GetAssets() const
{
    return m_assets;
}


size_t EfpkgFile::GetFileSize() const
{
    return m_data.size();
}


bool EfpkgFile::Parse()
{
    if (m_data.size() < 4)
    {
        return false;
    }

    std::cout << "Loaded: " << m_fileName << '\n';
    std::cout << "Size:   " << m_data.size() << " bytes\n";

    return true;
}