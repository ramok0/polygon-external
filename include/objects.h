#pragma once
#include <optional>
#include <cstdint>
#include <string>
#include <names.h>

struct UObjectBase {
private:
	void** VTable;
	/** Flags used to track and report various object states. This needs to be 8 byte aligned on 32-bit
	platforms to reduce memory waste */
	int32_t					ObjectFlags;

	/** Index into GObjectArray...very private. */
	int32_t							InternalIndex;

	/** Class the object belongs to. */
	struct UClass* ClassPrivate;

	/** Name of this object */
	FName							NamePrivate;
	/** Object this object resides in. */
	UObjectBase* OuterPrivate;

public:

	int32_t getInternalIndex();
	struct UClass* getClassPrivate();
	std::string getName();
	std::string getRelativeName();
	std::string getFullName();
	struct UObjectBase* getOuter();

};

struct FField {
	FField* get_next(void);
	std::string get_name(void);
	int32_t get_offset(void);
};

struct UStruct {
	FField* get_child_properties(void);
};

struct FUObjectItem
{
	// Pointer to the allocated object
	struct UObjectBase* Object;
	// Internal flags
	int32_t Flags;
	// UObject Owner Cluster Index
	int32_t ClusterRootIndex;
	// Weak Object Pointer Serial number associated with the object
	int32_t SerialNumber;
};


class FChunkedFixedUObjectArray
{
public:
	enum
	{
		NumElementsPerChunk = 64 * 1024,
	};

	/** Primary table to chunks of pointers **/
	FUObjectItem** Objects;
	/** If requested, a contiguous memory where all objects are allocated **/
	FUObjectItem* PreAllocatedObjects;
	/** Maximum number of elements **/
	int32_t MaxElements;
	/** Number of elements we currently have **/
	int32_t NumElements;
	/** Maximum number of chunks **/
	int32_t MaxChunks;
	/** Number of chunks we currently have **/
	int32_t NumChunks;

	static std::optional<FChunkedFixedUObjectArray> get_array(void) {
		RPM(FChunkedFixedUObjectArray, data::base_address + offsets::objects, Array);
		if (!ArraySuccess) return std::nullopt;

		return Array;
	}

	static UObjectBase* find_object(std::string objectName) {
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

	struct UObjectBase* operator[](uint32_t Index);
};