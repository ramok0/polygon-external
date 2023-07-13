#include <objects.h>
#include <polygon.hpp>
#include <game.hpp>

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