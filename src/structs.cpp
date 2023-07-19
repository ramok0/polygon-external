#include <objects.h>
#include <driver.h>
#include <game.h>

FField* UStruct::get_child_properties(void)
{
	if (this == nullptr) return nullptr;

	RPM(uint8_t*, (uintptr_t)this + offsets::ustruct_childproperties, ChildProperties);

	if (!ChildPropertiesSuccess || ChildProperties == 0) {
		return nullptr;
	}

	return (FField*)ChildProperties;
}