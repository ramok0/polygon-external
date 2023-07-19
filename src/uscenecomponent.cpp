#include <wrappers.h>
#include <offsets.h>

Vector3 USceneComponent::relative_location(void)
{
	ONCE_GET_OFFSET("/Script/Engine.SceneComponent", "RelativeLocation", RelativeLocationOffset);
	if (!RelativeLocationOffset) return { 0,0,0 };

	RPM(Vector3, (uintptr_t)this+RelativeLocationOffset, RelativeLocation);
	if (!RelativeLocationSuccess) return { 0,0,0 };

	return RelativeLocation;
}

FBoxSphereBounds USceneComponent::get_cached_bounds(void)
{
	ONCE_GET_OFFSET("/Script/Engine.SceneComponent", "RelativeLocation", RelativeLocationOffset);
	if (!RelativeLocationOffset) return { 0 };

	RPM(FBoxSphereBounds, (uintptr_t)this + RelativeLocationOffset - sizeof(FBoxSphereBounds), Bounds);
	if (!BoundsSuccess) return { 0 };

	return Bounds;
}

render_info_t USceneComponent::get_render_data(void)
{
	if (!this) return { 0 };
	ONCE_GET_OFFSET("/Script/Engine.PrimitiveComponent", "BoundsScale", BoundsScaleOffset);
	if (!BoundsScaleOffset) return { 0 };

	RPM(render_info_t, (uintptr_t)this + BoundsScaleOffset + sizeof(float), RenderInfo);

	if (!RenderInfoSuccess) return { 0 };

	return RenderInfo;
}
