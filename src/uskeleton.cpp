#include <ue4.hpp>

TArray<USkeletalMeshSocket*> USkeleton::get_sockets(void)
{
	if (this == nullptr) return { 0 };
	ONCE_GET_OFFSET("/Script/Engine.Skeleton", "Sockets", SocketsOffset);

	TArray<struct USkeletalMeshSocket*> sockets = driver::unsafe_read<TArray<USkeletalMeshSocket*>>((uintptr_t)this + SocketsOffset);

	return sockets;
}