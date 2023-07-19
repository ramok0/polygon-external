#include <objects.h>
#include <polygon.h>
#include <game.h>
#include <driver.h>

std::optional<FChunkedFixedUObjectArray> FChunkedFixedUObjectArray::get_array(void)
{
	RPM(FChunkedFixedUObjectArray, data::base_address + offsets::objects, Array);
	if (!ArraySuccess) return std::nullopt;

	return Array;
}

UObjectBase* FChunkedFixedUObjectArray::find_object(std::string objectName)
{
	std::optional<FChunkedFixedUObjectArray> array = get_array();
	if (!array) return nullptr;

	for (int i = 0; i < (*array).NumElements; i++)
	{
		UObjectBase* obj = (*array)[i];
		if (!obj) continue;

		if (obj->getFullName() == objectName)
		{
			return obj;
		}
	}

	return nullptr;
}

struct UObjectBase* FChunkedFixedUObjectArray::operator[](uint32_t Index)
{
	if ((int32_t)Index >= this->NumElements) 
		return nullptr;

	uint64_t chunkIndex = Index / 65536;
	if (chunkIndex >= NumChunks) 
		return nullptr;
	
	RPM(uint8_t*, (uintptr_t)Objects + chunkIndex, chunk);
	if (!chunkSuccess || chunk == 0) 
		return nullptr;
	
	uint32_t withinChunkIndex = Index % 65536 * sizeof(FUObjectItem);
	RPM(uint8_t*, (uintptr_t)chunk + withinChunkIndex, item);
	if (!itemSuccess) 
		return nullptr;
	

	return (struct UObjectBase*)item;
}