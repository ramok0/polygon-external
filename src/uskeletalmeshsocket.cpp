#include <ue4.hpp>


std::string USkeletalMeshSocket::get_bone_name(void)
{
	if (!this) return std::string();
	ONCE_GET_OFFSET("/Script/Engine.SkeletalMeshSocket", "BoneName", BoneNameOffset);

	uint32_t ComparisonIndex = driver::unsafe_read<uint32_t>((uintptr_t)this + BoneNameOffset);

	return get_name_by_index(ComparisonIndex);
}

std::string USkeletalMeshSocket::get_socket_name(void)
{
	if (!this) return std::string();
	ONCE_GET_OFFSET("/Script/Engine.SkeletalMeshSocket", "SocketName", SocketNameOffset);

	uint32_t ComparisonIndex = driver::unsafe_read<uint32_t>((uintptr_t)this + SocketNameOffset);

	return get_name_by_index(ComparisonIndex);
}
