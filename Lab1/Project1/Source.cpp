#pragma comment (lib, "setupapi.lib")
#include <Windows.h>
#include <SetupAPI.h>
#include <iostream>
#include <string>
using namespace std;

void printfVendor(string temp);
void printfDeviceID(string temp);

int main()
{
	//setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HDEVINFO hDevInfo;		//a handle to a device information set
	SP_DEVINFO_DATA deviceInfoData;		//structure defines a device instance that is a member of a device information set.
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA); //initialization structure field

	//returns a handle to a device information set. 
	//1 - identificator of class. Not important
	//2 - the system component that identifies the PnP device identifier 
	//3 - a handle to the top-level window. Not important
	//4 - Return a list of installed devices for the specified device setup classes or device interface classes.
	if ((hDevInfo = SetupDiGetClassDevs(NULL, "PCI", NULL, DIGCF_ALLCLASSES)) == INVALID_HANDLE_VALUE)
	{
		printf("%d", GetLastError());
		system("pause");
		return 0;
	}

	//returns a SP_DEVINFO_DATA structure that specifies a device information element in a device information set.
	//1 - handle of devices class
	//2 - number in list of devices class
	//3 - return structure with device information
	for (DWORD i = 0; (SetupDiEnumDeviceInfo(hDevInfo, i, &deviceInfoData)); i++)
	{
		DWORD data;
		LPTSTR buffer = NULL;
		DWORD bufferSize = 0;

		//The SetupDiGetDeviceRegistryProperty allows you to get the PnP device properties.
		while (!SetupDiGetDeviceRegistryProperty	(hDevInfo, //handle of devices class
			&deviceInfoData,		//pointer to a structure with device information
			SPDRP_DEVICEDESC,		//return device name
			NULL,					//pointer to the variable in which the type of data returned by the function is placed
			(PBYTE)buffer,
			bufferSize,
			&bufferSize))
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)		//The data area passed to a system call is too small.
			{
				if (buffer)
				{
					LocalFree(buffer);
				}
				buffer = (LPTSTR)LocalAlloc(LPTR, bufferSize * 2);
			}
			else
			{
				break;
			}
		}

		printf("%d. %-80s", i + 1, buffer);

		while (!SetupDiGetDeviceRegistryProperty(hDevInfo,
			&deviceInfoData,
			SPDRP_HARDWAREID,		//return deviceID and vendorID name
			NULL,
			(PBYTE)buffer,
			bufferSize,
			&bufferSize))
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)		//The data area passed to a system call is too small.
			{
				if (buffer)
				{
					LocalFree(buffer);
				}
				buffer = (LPTSTR)LocalAlloc(LPTR, bufferSize * 2);
			}
			else
			{
				break;
			}
		}
		if (buffer)
		{
			printfVendor(string(buffer));
			printfDeviceID(string(buffer));
			printf("\n");
			LocalFree(buffer);
		}
	}
	SetupDiDestroyDeviceInfoList(hDevInfo);
	system("pause");
	return 0;
}

void printfVendor(string temp)
{
	int venPos = temp.find("VEN_");
	printf("\tVendorID = ");
	for (int j = 4; j < 8; j++)
	{
		printf("%c", temp.at(venPos + j));
	}
}

void printfDeviceID(string temp)
{
	int devPos = temp.find("DEV_");
	printf("\tDeviceID = ");
	for (int j = 4; j < 8; j++) //j=4, because 0-3 "DEV_"
	{
		printf("%c", temp.at(devPos + j));
	}
}
