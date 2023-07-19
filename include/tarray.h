#pragma once
#include <string>
#include <driver.h>

template <typename T>
struct TArray {
	T* Data;
	__int32 Count;
	__int32 Max;

	operator bool() {
		return Data && Count != 0;
	}

	T operator[](int index);


	T* read_every_elements();
};

struct FString : TArray<wchar_t> {
	std::string to_string();
};

template<typename T>
inline T* TArray<T>::read_every_elements()
{
	T* bufferData = new T[Count];

	if (!driver::read((uintptr_t)Data, (uintptr_t)bufferData, (uintptr_t)(sizeof(T) * Count)))
	{
		delete[] bufferData;
		return nullptr;
	}

	return bufferData;
}

template<typename T>
T TArray<T>::operator[](int index)
{
	T buffer;

	if (!driver::read((uintptr_t)Data + (sizeof(T) * index), (uintptr_t)&buffer, sizeof(T))) {
		return T{ 0 };
	}

	return buffer;
}