#include <driver.h>
#include <polygon.h>
#include <Windows.h>

#define DRIVER_NAME L"\\\\.\\RamokDriver"
#define IOCTL_READ_MEM CTL_CODE(FILE_DEVICE_UNKNOWN, 0x999, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_WRITE_MEM CTL_CODE(FILE_DEVICE_UNKNOWN, 0x998, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_BASEADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x992, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

bool driver::init()
{
	data::driver_handle = CreateFileW(DRIVER_NAME, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	return data::driver_handle != INVALID_HANDLE_VALUE;
}

uint64_t driver::get_base_address(void)
{
	struct BaseaddrData
	{
		int pid;
		PVOID SourceAddress;
		PVOID TargetAddress;
		SIZE_T Size;
	} data;

	PVOID baseAddress = nullptr;
	DWORD bytesReturned = 0;

	data.pid = (int)data::pid;

	DeviceIoControl(data::driver_handle, IOCTL_BASEADDRESS, &data, sizeof(data), &baseAddress, sizeof(baseAddress), &bytesReturned, (LPOVERLAPPED)NULL);

	return (uint64_t)baseAddress;
}

bool driver::read(uintptr_t address, uintptr_t buffer, uintptr_t size)
{
	if (!address) return false;

	struct Rpmdata
	{
		int pid;
		PVOID SourceAddress;
		PVOID TargetAddress;
		SIZE_T Size;
	} rpm;
	rpm.pid = (int)data::pid;
	rpm.SourceAddress = (PVOID)address;
	rpm.TargetAddress = (PVOID)buffer;
	rpm.Size = size;
	BOOL bResult = FALSE;
	DWORD bytesReturned = 0;

	bResult = DeviceIoControl(data::driver_handle, IOCTL_READ_MEM, &rpm, sizeof(rpm), (LPVOID)buffer, (DWORD)size, &bytesReturned, (LPOVERLAPPED)NULL);

	return bResult && bytesReturned == (DWORD)size;
}

bool driver::write(uintptr_t address, uintptr_t buffer, uintptr_t size)
{
	if (!address) return false;

	struct Wpmdata
	{
		int pid;
		PVOID SourceAddress;
		PVOID TargetAddress;
		int Size;
	} wpm;

	wpm.pid = (int)data::pid;
	wpm.SourceAddress = (PVOID)address;
	wpm.TargetAddress = (PVOID)buffer;
	wpm.Size = (int)size;

	BOOL bResult = FALSE;
	DWORD bytesReturned = 0;

	bResult = DeviceIoControl(data::driver_handle, IOCTL_WRITE_MEM, &wpm, sizeof(wpm), (LPVOID)buffer, (DWORD)size, &bytesReturned, (LPOVERLAPPED)NULL);

	return bResult;
}
