#pragma once
#include <cstdint>
#include <tuple>

#define RPM(type, address, varName) auto [varName, varName##Success] = driver::read<type>(address);

namespace driver {
	bool init(void);
	uint64_t get_base_address(void);
	bool read(uintptr_t address, uintptr_t buffer, uintptr_t size);
	bool write(uintptr_t address, uintptr_t buffer, uintptr_t size);
	template <typename T> std::tuple<T, bool> read(uintptr_t address)
	{
		T buf;
		if (address == 0) {
			return { buf, false };
		}

		bool success = read(address, (uintptr_t)&buf, sizeof(T));
		if (!success) {
			return { buf, false };
		}

		return { buf, true };
	}

	template <typename T> T unsafe_read(uintptr_t address) {
		if (!address) {
			return T{ 0 };
		}

		T buf;

		bool success = driver::read(address, (uintptr_t)&buf, sizeof(T));

		if (!success) {
			return T{ 0 };
		}

		return buf;
	}

	template <typename T> bool write(uintptr_t address, T buffer)
	{
		return write(address, (uintptr_t)&buffer, sizeof(T));
	}
}
