#include <ue4.hpp>


USkeleton* USkeletalMesh::get_skeleton(void)
{
	SIMPLE_READ_PTR(USkeleton*, "/Script/Engine.SkeletalMesh", "Skeleton", Skeleton)
}