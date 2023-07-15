#include <ue4.hpp>
#include <polygon.hpp>
#include <game.hpp>
#include <cache.hpp>

Vector2Float world_to_screen(Vector3 world_location)
{
	Vector2Float screen_location;
	FMatrix rotation_matrix = FMatrix::from_rotator(cache::view_info.Rotation);

	Vector3 vDelta = world_location - cache::view_info.Location;

	Vector3 vAxisX = Vector3(rotation_matrix.M[0][0], rotation_matrix.M[0][1], rotation_matrix.M[0][2]);
	Vector3 vAxisY = Vector3(rotation_matrix.M[1][0], rotation_matrix.M[1][1], rotation_matrix.M[1][2]);
	Vector3 vAxisZ = Vector3(rotation_matrix.M[2][0], rotation_matrix.M[2][1], rotation_matrix.M[2][2]);

	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.0) {
		return { 0 };
	}

	screen_location.x = (float)(data::ScreenCenterX + vTransformed.x * (data::ScreenCenterX / tan(cache::view_info.FOV * DEG_TO_RAD2)) / vTransformed.z);
	screen_location.y = (float)(data::ScreenCenterY - vTransformed.y * (data::ScreenCenterX / tan(cache::view_info.FOV * DEG_TO_RAD2)) / vTransformed.z);

	return screen_location;
}



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

			//if (fieldName.contains("GameState")) {
			//	std::cout << className << "::" << fieldName << " : " << std::hex << "0x" << fieldOffset << std::endl;
			//}

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

UWorld* get_world(void)
{
	RPM(UWorld*, data::base_address + offsets::world, world);
	if (!worldSuccess) {
		return 0;
	}

	return world;
}

