#include <windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

void __cdecl wmain(void)
{
	DWORD  CharCount = 0;
	WCHAR  DeviceName[MAX_PATH] = L"";
	DWORD  Error = ERROR_SUCCESS;
	HANDLE FindHandle = INVALID_HANDLE_VALUE;
	BOOL   Found = FALSE;
	size_t Index = 0;
	BOOL   Success = FALSE;
	WCHAR  VolumeName[MAX_PATH] = L"";
	//  Enumerate all volumes in the system.
	FindHandle = FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));

	if (FindHandle == INVALID_HANDLE_VALUE)
	{
		Error = GetLastError();
		wprintf(L"FindFirstVolumeW failed with error code %d\n", Error);
		return;
	}

	for (;;)
	{
		Index = wcslen(VolumeName) - 1;

		if (VolumeName[0] != L'\\' ||
			VolumeName[1] != L'\\' ||
			VolumeName[2] != L'?' ||
			VolumeName[3] != L'\\' ||
			VolumeName[Index] != L'\\')
		{
			Error = ERROR_BAD_PATHNAME;
			wprintf(L"FindFirstVolumeW/FindNextVolumeW returned a bad path: %s\n", VolumeName);
			break;
		}


		VolumeName[Index] = L'\0';

		CharCount = QueryDosDeviceW(&VolumeName[4], DeviceName, ARRAYSIZE(DeviceName));

		VolumeName[Index] = L'\\';

		if (CharCount == 0)
		{
			Error = GetLastError();
			wprintf(L"QueryDosDeviceW failed with error code %d\n", Error);
			break;
		}
		wprintf(L"\n");
		wprintf(L"\nAvalible Hard Disk Drive: %s\n", DeviceName);
		wprintf(L"Volume name: %s", VolumeName);
		//move to next vol
		Success = FindNextVolumeW(FindHandle, VolumeName, ARRAYSIZE(VolumeName));

		if (!Success)
		{
			Error = GetLastError();

			if (Error != ERROR_NO_MORE_FILES)
			{
				wprintf(L"FindNextVolumeW failed with error code %d\n", Error);
				break;
			}
			Error = ERROR_SUCCESS;
			break;
		}
	}

	FindVolumeClose(FindHandle);
	FindHandle = INVALID_HANDLE_VALUE;

	return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	int n;
	char dd[4];
	DWORD dr = GetLogicalDrives();
	cout << "PHYSICAL HDD INFO:" << endl;
	wmain();
	cout << "\n--------------------------------------------------------------------------------------------------------" << endl;
	cout << "LOGICAL HDD INFO:\n" << endl;

	for (int i = 0; i < 10; i++)
	{
		n = ((dr >> i) & 0x020000001);
		if (n == 1)
		{
			dd[0] = char(65 + i); dd[1] = ':'; dd[2] = '\\'; dd[3] = 0;
			cout << "Available disk drives : " << dd << endl;
			//------------------------------------------------------------------------
			int a, b, c, d, e;
			a = GetDriveType(dd);
			if (a == DRIVE_UNKNOWN) cout << "  UNKNOWN" << endl;
			if (a == DRIVE_NO_ROOT_DIR) cout << "  DRIVE NO ROOT DIR" << endl;
			if (a == DRIVE_REMOVABLE) cout << "  REMOVABLE" << endl;
			if (a == DRIVE_FIXED) cout << "  FIXED" << endl;
			if (a == DRIVE_REMOTE) cout << "  REMOTE" << endl;
			if (a == DRIVE_CDROM) cout << "  CDROM" << endl;
			if (a == DRIVE_RAMDISK) cout << "  RAMDISK" << endl;
			//------------------------------------------------------------------------
			char VolumeNameBuffer[100];
			char FileSystemNameBuffer[100];
			unsigned long VolumeSerialNumber;

			BOOL GetVolumeInformationFlag = GetVolumeInformationA(
				dd,
				VolumeNameBuffer,
				100,
				&VolumeSerialNumber,
				NULL, //&MaximumComponentLength,
				NULL, //&FileSystemFlags,
				FileSystemNameBuffer,
				100
			);

			if (GetVolumeInformationFlag != 0)
			{
				cout << "  Volume Name is " << VolumeNameBuffer << endl;
				cout << "  Volume Serial Number is " << VolumeSerialNumber << endl;
				cout << "  File System is " << FileSystemNameBuffer << endl;
			}
			else cout << "Not Present (GetVolumeInformation)" << endl;
			//------------------------------------------------------------------------
			DWORD FreeBytesAvailable;
			DWORD TotalNumberOfBytes;
			DWORD TotalNumberOfFreeBytes;

			BOOL GetDiskFreeSpaceFlag = GetDiskFreeSpaceEx(
				dd,					  // directory name
				(PULARGE_INTEGER)&FreeBytesAvailable,     // bytes available to caller
				(PULARGE_INTEGER)&TotalNumberOfBytes,     // bytes on disk
				(PULARGE_INTEGER)&TotalNumberOfFreeBytes  // free bytes on disk
			);

			if (GetDiskFreeSpaceFlag != 0)
			{
				cout << "  Total Number Of Free Bytes = " << (unsigned long)TotalNumberOfFreeBytes
					<< "( " << double(unsigned long(TotalNumberOfFreeBytes)) / 1024 / 1000
					<< " Mb )" << endl;
				cout << "  Total Number Of Bytes = " << (unsigned long)TotalNumberOfBytes
					<< "( " << double(unsigned long(TotalNumberOfBytes)) / 1024 / 1000
					<< " Mb )" << endl;
			}
			else	cout << "Not Present (GetDiskFreeSpace)" << endl;
			//------------------------------------------------------------------------
			char path[100];

			GetSystemDirectory(path, 100);
			cout << "  System Directory is " << path << endl;
			GetTempPath(100, path);
			cout << "  Temp path is " << path << endl;
			GetWindowsDirectory(path, 100);
			cout << "  Windows directory is " << path << endl;
			GetCurrentDirectory(100, path);
			cout << "  Current directory is " << path << endl;
			cout << "--------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	system("pause");
}