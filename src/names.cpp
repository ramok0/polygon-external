#include <names.h>
#include <polygon.hpp>

std::string get_name_by_index(uint32_t Index)
{
	if (FNamePool::Cache.contains(Index)) {
		return FNamePool::Cache.at(Index);
	}
	constexpr uint16_t LenBit = 6;
	constexpr uint16_t WideBit = 0;
	constexpr uint16_t InfoOffset = 0;
	constexpr uint16_t HeadersSizeOffset = 2;

	uint32_t Block = (Index >> 16);
	uint32_t Offset = (Index & 65535);


	std::optional<FNamePool> pool = FNamePool::get_fname_pool();
	if (!pool) return std::string();

	if (Block > 8192u) return std::string();

	uint8_t* EntryPtr = (uint8_t*)(pool.value().Blocks[Block] + (Stride * (uint64_t)(Offset)));

	RPM(uint16_t, (uintptr_t)EntryPtr + InfoOffset, Info);
	if (!InfoSuccess) return std::string();

	int len = Info >> LenBit;
	bool wide = (Info >> WideBit) & 1;

	uint64_t DataPtr = (uint64_t)EntryPtr + HeadersSizeOffset;

	if (wide) {
		wchar_t buf[1024];

		if (!driver::read(DataPtr, (uintptr_t)buf, len * 2ull)) {
			return std::string();
		}

		int bufferSize = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
		char* narrowString = new char[bufferSize];
		WideCharToMultiByte(CP_ACP, 0, buf, -1, narrowString, bufferSize, NULL, NULL);

		std::string out = std::string(narrowString, bufferSize);
		
		delete[] narrowString;

		//std::string result(buf.begin(), buf.end());
		FNamePool::Cache.insert(std::make_pair(Index, out));
		return out;
	}
	else {
		std::string data("\0", len);

		if (!driver::read(DataPtr, (uintptr_t)data.data(), len)) {
			return std::string();
		}

		FNamePool::Cache.insert(std::make_pair(Index, data));
			
		return data;
	}

	return std::string();
}
