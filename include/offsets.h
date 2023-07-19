#pragma once
#include <unordered_map>
#include <mutex>
#include <string>
#include <driver.h>

typedef unsigned long long uint64;

inline std::unordered_map<std::string, std::unordered_map<std::string, int32_t>> offset_cache;

#define UNIQUE_VARAIBLE_NAME(base) base

#define ONCE_GET_OFFSET(className, propertyName, seed) \
	static std::once_flag UNIQUE_VARAIBLE_NAME(flag##seed); \
	static uint64_t UNIQUE_VARAIBLE_NAME(seed); \
	std::call_once(UNIQUE_VARAIBLE_NAME(flag##seed), []() { \
		UNIQUE_VARAIBLE_NAME(seed) = get_offset(className, propertyName);	\
		});

#define SIMPLE_READ_PTR(retType, className, propertyName, seed) \
	if(this == nullptr) return nullptr; \
	ONCE_GET_OFFSET(className, propertyName, seed##Offset); \
	if(!seed##Offset) return nullptr; \
	RPM(retType, (uintptr_t)this + seed##Offset, seed##Ptr); \
	if(!seed##Ptr##Success) return nullptr; \
	return seed##Ptr;

void cache_offsets(void);
uint64_t get_offset(std::string ClassName, std::string PropertyName);

