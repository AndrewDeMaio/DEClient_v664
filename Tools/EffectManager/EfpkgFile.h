#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "EfpkgAsset.h"

class EfpkgFile
{
public:
	bool Open(const std::string& filename);
	void Close();

	bool IsOpen() const;

	const std::vector<uint8_t>& GetData() const;
	const std::vector<EfpkgAsset>& GetAssets() const;

	size_t GetFileSize() const;

private:
	bool Parse();

	std::string m_fileName;
	std::vector<uint8_t> m_data;
	std::vector<EfpkgAsset> m_assets;
};