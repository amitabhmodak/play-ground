#include "DeviceInfo.h"

#include <iostream>
#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib,"Pdh.lib")
DeviceInfo::DeviceInfo()
{
	PdhOpenQuery(NULL, NULL, &cpuQuery);
	PdhAddCounter(cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
	PdhCollectQueryData(cpuQuery);
}

double DeviceInfo::getCpuUsage() {

	PDH_FMT_COUNTERVALUE counterVal;
	PdhCollectQueryData(cpuQuery);
	PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
	return counterVal.doubleValue;
}

double DeviceInfo::getMemoryUsage() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
	DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
	double usage = ((double)physMemUsed / (double)totalPhysMem) * 100;
	return usage;
}

 
std::vector<std::wstring> DeviceInfo::getRunningProcesses() {
	std::vector<std::wstring> processName;
	std::wstringstream stream;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot) {
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hSnapshot, &pe32)) {
			do {
				stream << pe32.szExeFile;
				 
				processName.push_back(stream.str());
			} while (Process32Next(hSnapshot, &pe32));
		}
		CloseHandle(hSnapshot);
	}
	return processName;
}
std::string DeviceInfo::getMacAddress() {
	std::stringstream stream;
	IP_ADAPTER_INFO AdapterInfo[16];			 
	DWORD dwBufLen = sizeof(AdapterInfo);		 
												 
	DWORD dwStatus = GetAdaptersInfo(			 
		AdapterInfo,							 
		&dwBufLen);								 
	assert(dwStatus == ERROR_SUCCESS);			 

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; 
	do {
		if (pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET) {
			char buff[100];
			snprintf(buff, sizeof(buff), "%02X-%02X-%02X-%02X-%02X-%02X",
				pAdapterInfo->Address[0], pAdapterInfo->Address[1],
				pAdapterInfo->Address[2], pAdapterInfo->Address[3],
				pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
			stream << buff;
 		}
 		pAdapterInfo = pAdapterInfo->Next;		 
	} while (pAdapterInfo);
 	 
	return stream.str();
}