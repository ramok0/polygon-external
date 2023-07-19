#include <tarray.h>
#include <driver.h>
#include <Windows.h>
#include <Windows.h>

std::string FString::to_string()
{
	if (!Data || Count == 0) return std::string();
	wchar_t buf[1024];

	if (!driver::read((uintptr_t)Data, (uintptr_t)buf, this->Count * 2ull))
	{
		return std::string();
	}

	int bufferSize = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
	char* narrowString = new char[bufferSize];
	WideCharToMultiByte(CP_ACP, 0, buf, -1, narrowString, bufferSize, NULL, NULL);

	std::string out = std::string(narrowString, bufferSize);

	delete[] narrowString;

	return out;
}