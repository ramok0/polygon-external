#pragma once
#include <vector>

std::vector<int> pattern_to_bytes(const char* pattern);
std::tuple<uint8_t*, size_t> clone_image(void);
unsigned long pattern_scan(unsigned char* data, unsigned long long length, const char* pattern);
uint64_t  relative_to_absolute(uint64_t address, int offset);

uint64_t find_gworld(uint8_t* image, size_t image_length);
uint64_t find_gobjects(uint8_t* image, size_t image_length);
uint64_t find_namepooldata(uint8_t* image, size_t image_length);