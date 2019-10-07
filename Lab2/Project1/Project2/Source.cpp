#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <ntddscsi.h>

using namespace std;

#define bThousand 1024
#define BYTE_SIZE 8

const char* busType[] = { "UNKNOWN", "SCSI", "ATAPI", "ATA", "ONE_TREE_NINE_FOUR", "SSA", "FIBRE", "USB", "RAID", "ISCSI", "SAS", "SATA", "SD", "MMC" };
const char* driveType[] = { "UNKNOWN", "INVALID", "CARD_READER/FLASH", "HARD", "REMOTE", "CD_ROM", "RAM" };

void getMemoryInfo();
void getDeviceInfo(HANDLE diskHandle, STORAGE_PROPERTY_QUERY storageProtertyQuery);
void getMemoryTransferMode(HANDLE diskHandle);

int main() {
	STORAGE_PROPERTY_QUERY storagePropertyQuery0;
	storagePropertyQuery0.QueryType = PropertyStandardQuery;
	storagePropertyQuery0.PropertyId = StorageDeviceProperty;
	HANDLE diskHandle0 = CreateFile("\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if (diskHandle0 == INVALID_HANDLE_VALUE) {
		cout << GetLastError();
		getchar();
		return -1;
	}

	STORAGE_PROPERTY_QUERY storagePropertyQuery1;
	storagePropertyQuery1.QueryType = PropertyStandardQuery;
	storagePropertyQuery1.PropertyId = StorageDeviceProperty;
	HANDLE diskHandle1 = CreateFile("\\\\.\\PhysicalDrive1", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if (diskHandle1 == INVALID_HANDLE_VALUE) {
		cout << GetLastError();
		getchar();
		return -1;
	}

	getDeviceInfo(diskHandle0, storagePropertyQuery0); //SSD
	getMemoryTransferMode(diskHandle0);
	cout << endl << endl;

	getDeviceInfo(diskHandle1, storagePropertyQuery1); //HDD
	getMemoryTransferMode(diskHandle1);
	cout << endl << endl;

	getMemoryInfo();

	CloseHandle(diskHandle0);
	CloseHandle(diskHandle1);
	getchar();
	return 0;
}



void getMemoryInfo() {
	string path;
	_ULARGE_INTEGER diskSpace;
	_ULARGE_INTEGER freeSpace;
	_ULARGE_INTEGER totalDiskSpace;
	totalDiskSpace.QuadPart = 0;
	_ULARGE_INTEGER totalFreeSpace;
	totalFreeSpace.QuadPart = 0;

	unsigned long int logicalDrivesCount = GetLogicalDrives();

	for (char var = 'A'; var < 'Z'; var++) {
		if ((logicalDrivesCount >> var - 65) & 1 && var != 'F') {
			path = var;
			path.append(":\\");
			GetDiskFreeSpaceEx(path.c_str(), 0, &diskSpace, &freeSpace);
			diskSpace.QuadPart = diskSpace.QuadPart / (bThousand * bThousand);
			freeSpace.QuadPart = freeSpace.QuadPart / (bThousand * bThousand);

			cout << endl << "Disk:\t" << var << endl;
			cout << "Total space[Mb]:" << diskSpace.QuadPart << endl;
			cout << "Free space[Mb]:\t" << freeSpace.QuadPart << endl;
			cout << "Busy space[%]:\t" << setprecision(3) << 100.0 - (double)freeSpace.QuadPart / (double)diskSpace.QuadPart * 100 << endl;
			cout << "Driver type:\t" << driveType[GetDriveType(path.c_str())] << endl;

			if (GetDriveType(path.c_str()) == 3) {
				totalDiskSpace.QuadPart += diskSpace.QuadPart;
				totalFreeSpace.QuadPart += freeSpace.QuadPart;
			}
		}
	}

	cout << endl << endl << "ALL DRIVES" << endl;
	cout << "Total space[Mb]:" << totalDiskSpace.QuadPart << endl;
	cout << "Free space[Mb]:\t" << totalFreeSpace.QuadPart << endl;
	cout << "Busy space[%]:\t" << setprecision(3) << 100.0 - (double)totalFreeSpace.QuadPart / (double)totalDiskSpace.QuadPart * 100 << endl;
}

void getDeviceInfo(HANDLE diskHandle, STORAGE_PROPERTY_QUERY storageProtertyQuery) {
	STORAGE_DEVICE_DESCRIPTOR* deviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)calloc(bThousand, 1); //Used to retrieve the storage device descriptor data for a device.
	deviceDescriptor->Size = bThousand;

	//Sends a control code directly to a specified device driver
	if (!DeviceIoControl(diskHandle, IOCTL_STORAGE_QUERY_PROPERTY, &storageProtertyQuery, sizeof(storageProtertyQuery), deviceDescriptor, bThousand, NULL, 0)) {
		printf("%d", GetLastError());
		CloseHandle(diskHandle);
		exit(-1);
	}

	cout << "Manufacturer & ID:\t" << (char*)(deviceDescriptor)+deviceDescriptor->ProductIdOffset << endl;
	cout << "Version\t\t\t" << (char*)(deviceDescriptor)+deviceDescriptor->ProductRevisionOffset << endl;
	cout << "Bus type:\t\t" << busType[deviceDescriptor->BusType] << endl;
	cout << "Serial number:\t\t" << (char*)(deviceDescriptor)+deviceDescriptor->SerialNumberOffset << endl;
}

void getMemoryTransferMode(HANDLE diskHandle) {

	UCHAR identifyDataBuffer[512 + sizeof(ATA_PASS_THROUGH_EX)] = { 0 };

	ATA_PASS_THROUGH_EX &ATA = *(ATA_PASS_THROUGH_EX *)identifyDataBuffer;	//ata	
	ATA.Length = sizeof(ATA);
	ATA.TimeOutValue = 10;
	ATA.DataTransferLength = 512;
	ATA.DataBufferOffset = sizeof(ATA_PASS_THROUGH_EX);
	ATA.AtaFlags = ATA_FLAGS_DATA_IN;
	IDEREGS *ideRegs = (IDEREGS *)ATA.CurrentTaskFile;
	ideRegs->bCommandReg = 0xEC;
	if (!DeviceIoControl(diskHandle,
		IOCTL_ATA_PASS_THROUGH,								//ATA_PASS_THROUGH_EX
		&ATA, sizeof(identifyDataBuffer), &ATA, sizeof(identifyDataBuffer), NULL, NULL)) {
		cout << GetLastError() << std::endl;
		return;
	}

	cout << "Transfer mode:\t\t";
	if (ATA.AtaFlags == ATA_FLAGS_USE_DMA)
	{
		cout << "DMA";
	}
	else
	{
		cout << "PIO";
	}

}