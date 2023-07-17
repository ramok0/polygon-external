#include <ue4structs.hpp>

std::string FText::get_string(void)
{
	if (!this) return std::string();

	FString str = driver::unsafe_read<FString>((uintptr_t)Data + offsetof(FTextData, string));
	if (!str) return std::string();

	return str.to_string();
}