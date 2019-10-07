#pragma comment (lib, "setupapi.lib")
#include <Windows.h>
#include <SetupAPI.h>
#include <iostream>

const unsigned int languge = 1251;

using namespace std;

void setConsoleLanguge() {
	SetConsoleCP(languge);
	SetConsoleOutputCP(languge);
}

HDEVINFO initpciHDevInfo() {
	HDEVINFO pciHDevInfo = SetupDiGetClassDevs(NULL, "PCI", NULL, DIGCF_ALLCLASSES);
	if (pciHDevInfo == INVALID_HANDLE_VALUE) throw runtime_error("Getting handle to a device information set end with code: " + GetLastError());
	return pciHDevInfo;
}

void printIDValue(string source,string ID) {
	int position = source.find(ID) + ID.size();
	char* o = (char*)source.data() + position;
	while (*o && *o != '&') cout << *o;
}
void printVendor(string temp)
{
	int venPos = temp.find("VEN_");
	printf("\tVendorID = ");
	for (int j = 4; j < 8; j++)
	{
		printf("%c", temp.at(venPos + j));
	}
}

void printDeviceID(string temp)
{
	int devPos = temp.find("DEV_");
	printf("\tDeviceID = ");
	for (int j = 4; j < 8; j++) //j=4, because 0-3 "DEV_"
	{
		printf("%c", temp.at(devPos + j));
	}
}


string getDeviceProperty(DWORD property, HDEVINFO pciHDevInfo, PSP_DEVINFO_DATA deviceInfoData, PBYTE buffer, DWORD bufferSize) {
	if (!buffer) {
		bufferSize = 100;
		buffer = new BYTE[bufferSize];
	}
	if (SetupDiGetDeviceRegistryProperty(pciHDevInfo, deviceInfoData, property, NULL, buffer, bufferSize, &bufferSize))
	{
		string str((char*)buffer);
		delete buffer;
		return str;
	}
	else {
		bufferSize *= 2;
		delete buffer;
		buffer = new BYTE[bufferSize];
		return getDeviceProperty(property, pciHDevInfo, deviceInfoData, buffer, bufferSize);
	}
}

void printDeviceDecription(HDEVINFO pciHDevInfo, PSP_DEVINFO_DATA deviceInfoData) {
	string deviceDecription = getDeviceProperty(SPDRP_DEVICEDESC, pciHDevInfo, deviceInfoData, NULL, NULL);
	printf("%-100s", deviceDecription.data());
}

void printDeviceIDs(HDEVINFO pciHDevInfo, PSP_DEVINFO_DATA deviceInfoData) {
	string hardwareIDs = getDeviceProperty(SPDRP_HARDWAREID, pciHDevInfo, deviceInfoData, NULL, NULL);
	printVendor(hardwareIDs);
	printDeviceID(hardwareIDs);
	//printIDValue(hardwareIDs, "VEN_");
}
void printDeviceInfo(HDEVINFO pciHDevInfo, PSP_DEVINFO_DATA deviceInfoData) {
	printDeviceDecription(pciHDevInfo, deviceInfoData);
	printDeviceIDs(pciHDevInfo, deviceInfoData);
}

void printDevicesList(HDEVINFO pciHDevInfo) {
	PSP_DEVINFO_DATA deviceInfoData = new SP_DEVINFO_DATA;
	deviceInfoData->cbSize = sizeof(SP_DEVINFO_DATA);
	unsigned int deviceNumber = 0;
	while (SetupDiEnumDeviceInfo(pciHDevInfo, deviceNumber, deviceInfoData)) {
		cout << endl << deviceNumber + 1 << ". ";
		printDeviceInfo(pciHDevInfo, deviceInfoData);
		deviceNumber++;
	}
	delete deviceInfoData;
}

int main(void)
{
	setConsoleLanguge();
	try{
		HDEVINFO pciHDevInfo = initpciHDevInfo();
		printDevicesList(pciHDevInfo);
		SetupDiDestroyDeviceInfoList(pciHDevInfo);
	} catch (exception ex) {
		cout << ex.what() << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}