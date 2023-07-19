#include <offsets.h>
#include <objects.h>
#include <array>

void cache_offsets(void)
{
	const std::array<std::string, 2> to_dump_types = { "Class", "ScriptStruct" }; //not the fastest way to do this but its the most functionnal

	std::optional<FChunkedFixedUObjectArray> array = FChunkedFixedUObjectArray::get_array();
	if (!array) return;
	for (int i = 0; i < (*array).NumElements; i++) {
		UObjectBase* obj = (*array)[i];
		if (!obj) continue;

		std::string data = (((UObjectBase*)obj->getClassPrivate())->getName());

		if (std::find(to_dump_types.begin(), to_dump_types.end(), data) == to_dump_types.end()) {
			continue;
		}
		std::string className = obj->getRelativeName();
		//std::cout << className << std::endl;

		if (offset_cache.contains(className)) continue;
		std::unordered_map<std::string, int32_t> offsetMap;


		for (auto field = ((UStruct*)obj)->get_child_properties(); field; field = field->get_next())
		{
			std::string fieldName = field->get_name();
			int32_t fieldOffset = field->get_offset();

			if (fieldOffset != 0) {
				offsetMap.insert({ fieldName, fieldOffset });
			}
		}

		offset_cache.insert({ className, offsetMap });
	}
}

uint64_t get_offset(std::string ClassName, std::string PropertyName)
{
	if (!offset_cache.contains(ClassName)) return 0;

	if (!offset_cache.at(ClassName).contains(PropertyName)) return 0;

	return offset_cache[ClassName][PropertyName];
}
