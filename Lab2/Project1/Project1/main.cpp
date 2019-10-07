#include <atlstr.h>
#include <Windows.h>
#include <winioctl.h>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <ntddscsi.h>
#include <sstream>

#define bThousand 1024
#define BYTE_SIZE 8

using namespace std;

const char* busType[] = { "UNKNOWN", "SCSI", "ATAPI", "ATA", "ONE_TREE_NINE_FOUR", "SSA", "FIBRE", "USB", "RAID", "ISCSI", "SAS", "SATA", "SD", "MMC" };
const char* driveType[] = { "UNKNOWN", "INVALID", "CARD_READER/FLASH", "HARD", "REMOTE", "CD_ROM", "RAM" };

HANDLE initDeviceHandle(int number, STORAGE_PROPERTY_QUERY &storagePropertyQuery) {
	DWORD dwSerialNumberOffset = 0;
	ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
	storagePropertyQuery.PropertyId = StorageDeviceProperty;
	storagePropertyQuery.QueryType = PropertyStandardQuery;
	stringstream driveName;
	driveName << "\\\\.\\PhysicalDrive" << number;
	string driveNameString = driveName.str();
	return CreateFile(driveNameString.data(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
}

void checkFlag(DWORD flags, DWORD flag, string meaning) {
	if (flags&flag) cout << meaning << endl;
}

void printMemoryData()
{
	_ULARGE_INTEGER diskSpace;
	_ULARGE_INTEGER freeSpace;
	_ULARGE_INTEGER totalDiskSpace;
	totalDiskSpace.QuadPart = 0;
	_ULARGE_INTEGER totalFreeSpace;
	totalFreeSpace.QuadPart = 0;

	const int volumeListSize = 100;
	char volumeList[volumeListSize];
	char* volumePointer = volumeList;
	GetLogicalDriveStrings(volumeListSize, volumeList);

	for (volumePointer; *volumePointer; volumePointer += 4) {
		GetDiskFreeSpaceEx(volumePointer, 0, &diskSpace, &freeSpace);
		diskSpace.QuadPart = diskSpace.QuadPart / (bThousand * bThousand);
		freeSpace.QuadPart = freeSpace.QuadPart / (bThousand * bThousand);

		cout << endl << "Disk:\t" << volumePointer << endl;
		cout << "Total space[Mb]:" << diskSpace.QuadPart << endl;
		cout << "Free space[Mb]:\t" << freeSpace.QuadPart << endl;
		cout << "Busy space[%]:\t" << setprecision(3) << 100.0 - (double)freeSpace.QuadPart / (double)diskSpace.QuadPart * 100 << endl;
		cout << "Driver type:\t" << driveType[GetDriveType(volumePointer)] << endl;

		DWORD flags;
		char fileSystemNameBuffer[100];

		BOOL GetVolumeInformationFlag = GetVolumeInformationA(
			volumePointer,
			NULL,
			NULL,
			NULL,
			NULL, 
			&flags, 
			fileSystemNameBuffer,
			100
		);

		cout << "File system:\t" << fileSystemNameBuffer << endl;
		cout << "Volume supports:" << endl;
		checkFlag(flags, 0x00000002, "supports preserved case of file names when it places a name on disk");
		checkFlag(flags, 0x00000001, "supports case-sensitive file names");
		checkFlag(flags, 0x20000000, "is a direct access (DAX) volume");
		checkFlag(flags, 0x00000010, "supports file-based compression");
		checkFlag(flags, 0x00040000, "supports named streams");
		checkFlag(flags, 0x00000008, "preserves and enforces access control lists (ACL). For example, the NTFS file system preserves and enforces ACLs, and the FAT file system does not");
		checkFlag(flags, 0x00080000, "is read-only");
		checkFlag(flags, 0x00100000, "supports a single sequential write");
		checkFlag(flags, 0x00020000, "supports the Encrypted File System (EFS)");
		checkFlag(flags, 0x00800000, "supports extended attributes. An extended attribute is a piece of application-specific metadata that an application can associate with a file and is not part of the file's data");
		checkFlag(flags, 0x00400000, "The specified volume supports hard links.");
		checkFlag(flags, 0x00010000, "supports object identifiers");
		checkFlag(flags, 0x01000000, "The file system supports open by FileID");
		checkFlag(flags, 0x00000080, "supports reparse points");
		checkFlag(flags, 0x00000040, "supports sparse files");
		checkFlag(flags, 0x00200000, "supports transactions");
		checkFlag(flags, 0x02000000, "supports update sequence number (USN) journals");
		checkFlag(flags, 0x00000004, "supports Unicode in file names as they appear on disk");
		checkFlag(flags, 0x00008000, "is a compressed volume, for example, a DoubleSpace volume");
		checkFlag(flags, 0x00000020, "supports disk quotas");

		if (GetDriveType(volumePointer) == 3) {
			totalDiskSpace.QuadPart += diskSpace.QuadPart;
			totalFreeSpace.QuadPart += freeSpace.QuadPart;

		}
	}

	cout << endl << endl << "ALL DRIVES" << endl;
	cout << "Total space[Mb]:" << totalDiskSpace.QuadPart << endl;
	cout << "Free space[Mb]:\t" << totalFreeSpace.QuadPart << endl;
	cout << "Busy space[%]:\t" << setprecision(3) << 100.0 - (double)totalFreeSpace.QuadPart / (double)totalDiskSpace.QuadPart * 100 << endl;
}



char* removeSpaces(char* source)
{
	while (*source == ' ' || *source == '\n' || *source == '\t' || *source == '\f' || *source == '\v' || *source == '\r') source++;
	return source;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while(true){
	STORAGE_PROPERTY_QUERY    storagePropertyQuery;
	STORAGE_DESCRIPTOR_HEADER storageDescHeader = { 0 };
	STORAGE_DEVICE_DESCRIPTOR *pDeviceDesc, *pDeviceDesc1;
	DWORD dwBytes = 0;
	DWORD dwOutBufferSize = 0;
	BYTE *pOutBuffer = nullptr;
	for (int i = 0; true; i++)
	{
		HANDLE hDevice = initDeviceHandle(i, storagePropertyQuery);
		if (hDevice == INVALID_HANDLE_VALUE) break;


		bool bResult = DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
			&storagePropertyQuery, sizeof(storagePropertyQuery),
			&storageDescHeader, sizeof(storageDescHeader),
			&dwBytes, NULL);

		dwOutBufferSize = storageDescHeader.Size;

		try {
			pOutBuffer = new BYTE[dwOutBufferSize];
			ZeroMemory(pOutBuffer, sizeof(dwOutBufferSize));
		}
		catch (bad_alloc exp) {
			CloseHandle(hDevice);
			cout << exp.what() << endl;
			return FALSE;
		}
		bResult = DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
			&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
			pOutBuffer, dwOutBufferSize, &dwBytes, NULL);

		pDeviceDesc1 = (STORAGE_DEVICE_DESCRIPTOR *)&storageDescHeader;//без текстовых полей
		pDeviceDesc = (STORAGE_DEVICE_DESCRIPTOR *)pOutBuffer;//с текстовыми полями полями
		string model(removeSpaces((char*)pOutBuffer + pDeviceDesc->ProductIdOffset)), vendor;
		if (pDeviceDesc->VendorIdOffset) vendor = string(removeSpaces((char*)pOutBuffer + pDeviceDesc->VendorIdOffset));
		else vendor = model.substr(0, model.find(' '));

		cout << "Model: " << model << endl;
		cout << "Vendor: " << vendor << endl;
		cout << "Serial Number: " << removeSpaces((char*)pOutBuffer + pDeviceDesc->SerialNumberOffset) << endl;
		cout << "Version: " << removeSpaces((char*)pOutBuffer + pDeviceDesc->ProductRevisionOffset) << endl;
		cout << "Interface Type: " << busType[pDeviceDesc->BusType] << endl;
		cout << "\n\n|------------------------------------------------|\n\n";

		delete[] pOutBuffer;
		CloseHandle(hDevice);
	}
	printMemoryData();
	Sleep(10000);
	system("cls");
}
	system("pause");
	return 0;
}