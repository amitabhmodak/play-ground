#pragma once
#include<string>
#include<vector>
#include "TCHAR.h"
#include "pdh.h"
#include <psapi.h>
#include<sstream>
#include<TlHelp32.h>

class DeviceInfo
{
	  PDH_HQUERY cpuQuery;
	  PDH_HCOUNTER cpuTotal;
 
public:
	DeviceInfo();
	~DeviceInfo() = default;
	double getCpuUsage();
	double getMemoryUsage();
	std::vector<std::wstring> getRunningProcesses();
	std::string getMacAddress();
};

