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
	if (this == nullptr) return { 0 };

	auto bone_array = this->get_bone_array();
	if (!bone_array) return { 0 };

	FTransform bone = (*bone_array)[Index];
	FTransform component_to_world = this->get_component_to_world();

	FMatrix matrix = bone.ToMatrixWithScale() * component_to_world.ToMatrixWithScale();

	return Vector3(matrix.M[3][0], matrix.M[3][1], matrix.M[3][2]);
}

FTransform USkeletalMeshComponent::get_component_to_world(void)
{
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

bool USkeletalMeshComponent::set_force_wireframe(bool new_val)
{
	if (!this) return false;

	//char pad_7C6_0 : 3; // 0x7c6(0x01)
	//char bOverrideMinLod : 1; // 0x7c6(0x01)
	//char bUseBoundsFromLeaderPoseComponent : 1; // 0x7c6(0x01)
	//char bForceWireframe : 1; // 0x7c6(0x01)
	//char bDisableMorphTarget : 1; // 0x7c6(0x01)
	//char bHideSkin : 1; // 0x7c6(0x01)

	ONCE_GET_OFFSET("/Script/Engine.SkinnedMeshComponent", "bOverrideMinLod", bOverrideMinLodOffset);
	if (!bOverrideMinLodOffset) return false;

	uint8_t data = driver::unsafe_read<uint8_t>((uintptr_t)this + bOverrideMinLodOffset);

	bool current_wireframe = (data >> 5) & 0x01;

	if (current_wireframe == new_val) return true;

	if (new_val)
	{
		data |= (1 << 5);
	}
	else {
		data &= ~(1 << 5);
	}

	return driver::write<uint8_t>((uintptr_t)this + bOverrideMinLodOffset, data);
}

bool USkeletalMeshComponent::was_recently_rendered(void)
{
	if (!this) return false;
	//struct bitfield_t {
	//	char bPerBoneMotionBlur : 1; // 0x7c7(0x01)
	//	char bComponentUseFixedSkelBounds : 1; // 0x7c7(0x01)
	//	char bConsiderAllBodiesForBounds : 1; // 0x7c7(0x01)
	//	char bSyncAttachParentLOD : 1; // 0x7c7(0x01)
	//	char bCanHighlightSelectedSections : 1; // 0x7c7(0x01)
	//	char bRecentlyRendered : 1; // 0x7c7(0x01)
	//	char bCastCapsuleDirectShadow : 1; // 0x7c7(0x01)
	//	char bCastCapsuleIndirectShadow : 1; // 0x7c7(0x01)
	//} data;

	ONCE_GET_OFFSET("/Script/Engine.SkinnedMeshComponent", "bPerBoneMotionBlur", bPerBoneMotionBlurOffset);

	uint8_t bitfield = driver::unsafe_read<uint8_t>((uintptr_t)this + bPerBoneMotionBlurOffset);

	return (bitfield >> 5) & 0x01;
}

//USkeletalMesh* USkeletalMeshComponent::get_skeletal_mesh_asset(void)
//{
//	SIMPLE_READ_PTR(USkeletalMesh*, "/Script/Engine.SkeletalMeshComponent", "SkeletalMeshAsset", SkeletalMeshAsset);
//}
