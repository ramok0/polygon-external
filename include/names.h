#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>

#include <polygon.hpp>
#include <game.hpp>

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

	static std::optional<FNamePool> get_fname_pool(void)
	{
		RPM(FNamePool, data::base_address + offsets::names, NamePool);
		if (!NamePoolSuccess) return std::nullopt;

		return NamePool;
	}
};

std::string get_name_by_index(uint32_t Index);