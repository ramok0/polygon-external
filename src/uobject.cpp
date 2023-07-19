#include <objects.h>
#include <driver.h>


int32_t UObjectBase::getInternalIndex()
{
	if (this == nullptr) return 0;
	RPM(int32_t, (uintptr_t)this + offsetof(UObjectBase, InternalIndex), InternalIndex);
	if (!InternalIndexSuccess) return 0;

	return InternalIndex;
}

UClass* UObjectBase::getClassPrivate()
{
	if (this == nullptr) return nullptr;
	RPM(UClass*, (uintptr_t)this + offsetof(UObjectBase, ClassPrivate), ClassPrivate);
	if (!ClassPrivateSuccess) return nullptr;

	return ClassPrivate;
}

std::string UObjectBase::getName()
{
	if (this == nullptr) return std::string();
	RPM(FName, (uintptr_t)this + offsetof(UObjectBase, NamePrivate), NamePrivate);
	if (!NamePrivateSuccess) return std::string();

	return get_name_by_index(NamePrivate.ComparisonIndex);
}

std::string UObjectBase::getRelativeName()
{
	UObjectBase* outer = this->getOuter();
	std::string out = (outer ? outer->getName() + "." : "") + this->getName();
	return out;
}

std::string UObjectBase::getFullName()
{
	std::string temp;
	for (auto outer = getOuter(); outer; outer = outer->getOuter())
	{
		temp = outer->getName() + "." + temp;
	}

	std::string name = ((UObjectBase*)this->getClassPrivate())->getName() + " " + temp + this->getName();
	return name;
}

UObjectBase* UObjectBase::getOuter()
{
	if (this == nullptr) return nullptr;
	RPM(UObjectBase*, (uintptr_t)this + 0x20, OuterPrivate);
	if (!OuterPrivateSuccess) return nullptr;

	return OuterPrivate;
}

