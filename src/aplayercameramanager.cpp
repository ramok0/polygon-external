#include <wrappers.h>
#include <offsets.h>

std::optional<FMinimalViewInfo> APlayerCameraManager::get_camera(void)
{
	if (this == nullptr) return std::nullopt;

	ONCE_GET_OFFSET("/Script/Engine.PlayerCameraManager", "LastFrameCameraCachePrivate", LastFrameCameraCachePrivateOffset);

	if (!LastFrameCameraCachePrivateOffset) return std::nullopt;

	RPM(FCameraCacheEntry, (uintptr_t)this + LastFrameCameraCachePrivateOffset, CameraCacheEntry);
	if (!CameraCacheEntrySuccess) return std::nullopt;

	return CameraCacheEntry.POV;
}
