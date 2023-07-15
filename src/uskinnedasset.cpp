#include <ue4.hpp>
#include <cache.hpp>

std::unordered_map<std::string, int> USkinnedAsset::get_bones()
{
	if (!this) return std::unordered_map<std::string, int>();
	TArray<FMeshBoneInfo> bonesInfo = driver::unsafe_read<TArray<FMeshBoneInfo>>((uint64_t)this + offsets::ref_skeleton + offsets::FinalRefBoneInfo);
	
	std::unordered_map<std::string, int> result;
	for (int i = 0; i < bonesInfo.Count; i++) {
		FMeshBoneInfo data = bonesInfo[i];
		result[get_name_by_index(data.Name.ComparisonIndex)] = i;
	}

	return result;
}

std::vector<std::string> USkinnedAsset::get_bones_as_vector()
{
	if (!this) return std::vector<std::string>();
	TArray<FMeshBoneInfo> bonesInfo = driver::unsafe_read<TArray<FMeshBoneInfo>>((uint64_t)this + offsets::ref_skeleton + offsets::FinalRefBoneInfo);

	std::vector<std::string> result;
	
	for (int i = 0; i < bonesInfo.Count; i++) {
		FMeshBoneInfo data = bonesInfo[i];
		result.push_back(get_name_by_index(data.Name.ComparisonIndex));
	}

	return result;
}
