#pragma once

#include <cstdint>
#include <string>

struct EfpkgAsset
{
	std::string name;
	uint32_t size;
	uint32_t offset;
};