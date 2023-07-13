#include <ue4.hpp>

std::optional<TArray<FTransform>> USkeletalMeshComponent::get_bone_array(void)
{
	if (this == nullptr) return std::nullopt;

	BoneArray bones_array = driver::unsafe_read<BoneArray>((uintptr_t)this + offsets::bone_array);

	TArray<FTransform> bone_array = bones_array.ComponentSpaceTransformsArray[0].Data && bones_array.ComponentSpaceTransformsArray[0].Count != 0 ? bones_array.ComponentSpaceTransformsArray[0] : bones_array.ComponentSpaceTransformsArray[1];

	

	return bone_array;
}

Vector3 USkeletalMeshComponent::get_bone_with_rotation(int Index)
{
	if (this == nullptr) return { 0,0,0 };

	std::optional<TArray<FTransform>> bone_array = this->get_bone_array();
	if (!bone_array) return { 0,0,0 };

	//sale fils de pute

	//FTransform bone = driver::unsafe_read<FTransform>((uintptr_t)bone_array.value().Data + (0x60 * Index));
	FTransform bone = (*bone_array)[Index];
	FTransform component_to_world = this->get_component_to_world();

	FMatrix matrix = bone.ToMatrixWithScale() * component_to_world.ToMatrixWithScale();

	return Vector3(matrix.M[3][0], matrix.M[3][1], matrix.M[3][2]);
}

FTransform USkeletalMeshComponent::get_component_to_world(void)
{
	//RPM(FTransform, (uintptr_t)this + offsets::component_to_world, ComponentToWorld);
	//if (!ComponentToWorldSuccess || !ComponentToWorld) return { 0 };
	//return ComponentToWorld;
	FTransform ComponentToWorld = driver::unsafe_read<FTransform>((uintptr_t)this + offsets::component_to_world);
	return ComponentToWorld;
}

USkinnedAsset* USkeletalMeshComponent::get_skinned_asset(void)
{
	if (!this) return nullptr;
	ONCE_GET_OFFSET("/Script/Engine.SkinnedMeshComponent", "SkeletalMesh", SkeletalMeshOffset);
	ONCE_GET_OFFSET("/Script/Engine.SkinnedMeshComponent", "SkinnedAsset", SkinnedAssetOffset);

	if (!SkeletalMeshOffset || !SkinnedAssetOffset) return nullptr;

	USkinnedAsset* SkeletalMesh = driver::unsafe_read<USkinnedAsset*>((uintptr_t)this + SkeletalMeshOffset);
	if(!SkeletalMesh)
		SkeletalMesh = driver::unsafe_read<USkinnedAsset*>((uintptr_t)this + SkinnedAssetOffset);

	return SkeletalMesh;
}

//USkeletalMesh* USkeletalMeshComponent::get_skeletal_mesh_asset(void)
//{
//	SIMPLE_READ_PTR(USkeletalMesh*, "/Script/Engine.SkeletalMeshComponent", "SkeletalMeshAsset", SkeletalMeshAsset);
//}
