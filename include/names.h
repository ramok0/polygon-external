#pragma once
#include <string>
#include <unordered_map>
#include <optional>

struct FName {
	int32_t ComparisonIndex;
	int32_t Unknown;
};
constexpr int Stride = 2;

class FNamePool {	
public:
	inline static std::unordered_map<uint32_t, std::string> Cache;

	uint8_t Lock[8];
	uint32_t CurrentBlock;
	uint32_t CurrentByteCursor;
	uint8_t* Blocks[8192];

	static std::optional<FNamePool> get_fname_pool(void);
};

std::string get_name_by_index(uint32_t Index);