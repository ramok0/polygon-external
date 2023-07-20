#include "scanner.h"
#include <driver.h>
#include <polygon.h>
#include <Windows.h>
#include <iostream>

std::vector<int> pattern_to_bytes(const char* pattern)
{
	auto bytes = std::vector<int>{};
	auto start = const_cast<char*>(pattern);
	auto end = const_cast<char*>(pattern) + strlen(pattern);

	for (auto current = start; current < end; ++current) {
		if (*current == '?') {
			++current;
			if (*current == '?')
				++current;
			bytes.push_back(0xFF);
		}
		else {
			bytes.push_back(strtoul(current, &current, 16));
		}
	}
	return bytes;
}

std::tuple<uint8_t*, size_t> clone_image(void)
{

	IMAGE_DOS_HEADER dosHeaders = driver::unsafe_read<IMAGE_DOS_HEADER>(data::base_address);
	IMAGE_NT_HEADERS ntHeaders = driver::unsafe_read<IMAGE_NT_HEADERS>(data::base_address + dosHeaders.e_lfanew);

	DWORD sizeOfImage = ntHeaders.OptionalHeader.SizeOfImage;

	BYTE* data = new BYTE[sizeOfImage];

	ZeroMemory(data, sizeOfImage);

	if (!driver::read((uintptr_t)data::base_address, (uintptr_t)data, sizeOfImage))
	{
		return std::make_tuple(nullptr, 0);
	}

	return std::make_tuple(data, sizeOfImage);
}

unsigned long pattern_scan(unsigned char* data, unsigned long long length, const char* pattern)
{
	std::vector<int> signature = pattern_to_bytes(pattern);
	size_t toScanLength = length - signature.size();
	for (unsigned long i = 0ul; i < toScanLength; i++) {
		bool found = true;
		for (unsigned int j = 0; j < signature.size() && found; j++) {
			if (signature[j] != 0XFF)
				found = data[i + j] == (unsigned char)(signature[j]);
		}

		if (found) {
			std::cout << "Found pattern at 0x" << std::hex << i << std::endl;
			return i;
		}
	}

	return 0;
}

uint64_t  relative_to_absolute(uint64_t address, int offset)
{
	address += data::base_address;
	int instruction_length = (int)offset + 4;

	auto relativeOffset = static_cast<uint64_t>(driver::unsafe_read<uint32_t>(address + offset));

	return (address + relativeOffset + instruction_length) - data::base_address;
}

uint64_t find_gworld(uint8_t* image, size_t image_length)
{
	constexpr const char* WORLD_PATTERN = "48 8B 1D ? ? ? ? 48 85 DB 74 ? 41 B0 01";

	unsigned long relative = pattern_scan(image, image_length, WORLD_PATTERN);
	if (!relative) return 0;

	return relative_to_absolute(relative, 3);
}

uint64_t find_gobjects(uint8_t* image, size_t image_length)
{
	constexpr const char* OBJECTS_PATTERN = "48 8B 05 ? ? ? ? 48 8B 0C C8 4C 8D 04 D1";

	unsigned long relative = pattern_scan(image, image_length, OBJECTS_PATTERN);
	if (!relative) return 0;

	return relative_to_absolute(relative, 3);
}

uint64_t find_namepooldata(uint8_t* image, size_t image_length)
{
	constexpr const char* NAMES_PATTERN = "4C 8D 05 ? ? ? ? EB ? 48 8D 0D ? ? ? ? E8";

	unsigned long relative = pattern_scan(image, image_length, NAMES_PATTERN);
	if (!relative) return 0;

	return relative_to_absolute(relative, 3);
}
