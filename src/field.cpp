#include <objects.h>
#include <game.h>
#include <driver.h>

FField* FField::get_next(void)
{
	if (this == nullptr) return nullptr;

	RPM(FField*, (uintptr_t)this+offsets::ffield_next, Next);
	if (!NextSuccess || Next == 0) return nullptr;

	return Next;
}

std::string FField::get_name(void)
{
	if (this == nullptr) return std::string();

	RPM(FName, (uintptr_t)this + offsets::ffield_name, Name);
	if (!NameSuccess) return std::string();

	return get_name_by_index(Name.ComparisonIndex);
}

int32_t FField::get_offset(void)
{
	if (this == nullptr) return 0;

	RPM(int32_t, (uintptr_t)this + offsets::fproperty_offset, Offset);
	if (!OffsetSuccess) return 0;

	return Offset;
}
