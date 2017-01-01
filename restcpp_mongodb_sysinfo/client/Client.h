#pragma once

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <string>
#include <memory>
#include "IMessageHandler.h"
#include "DeviceInfo.h"

class Client
{
  	std::unique_ptr<IMessageHandler> m_messageHandler;
	DeviceInfo m_info;
	std::wstring m_mail;
	std::wstring m_key;
public:
	Client(std::string mail, std::unique_ptr<IMessageHandler> handler);
	~Client();
	void start();
 	bool isDeviceRegistered();
	void regiserDevice();
	void publishCpu(double cpuUsage);
	void publishMemory(double memoryUsage);
	void publishProcessList(std::vector<std::wstring> processList);
};

