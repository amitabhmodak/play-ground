#pragma once
#include<string>
#include <vector>

class IMessageHandler {
public:
	IMessageHandler() = default;
	virtual ~IMessageHandler() = default;
	virtual void  publishCpu(double cpuUsage, std::wstring clientKey) = 0;
	virtual void  publishMemory(double memoryUsage, std::wstring clientKey) = 0;
	virtual void  publishProcessList(std::vector<std::wstring>  processList, std::wstring clientKey) = 0;
	virtual void  registerDevice(std::wstring mail, std::wstring mac) = 0;
	virtual std::wstring getAuthToken(std::wstring mail, std::wstring mac) = 0;
	
};