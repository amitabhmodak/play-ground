#pragma once

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>

#include <condition_variable>
#include "IMessageHandler.h"
#include "DeviceInfo.h"

class Client
{
  	std::unique_ptr<IMessageHandler> m_messageHandler;
	DeviceInfo m_info;
	std::wstring m_mail;
	std::wstring m_key;
	std::condition_variable m_trigger;
	std::mutex m_triggerLock;
	std::atomic <int> m_threadRun;
	std::unique_ptr <std::thread> m_worker;

	bool threadRun();

public:
	Client(std::string mail, std::unique_ptr<IMessageHandler> handler);
	~Client();
	void start();
	void run();
	void stop();
 	bool isDeviceRegistered();
	void regiserDevice();
	void publishCpu(double cpuUsage);
	void publishMemory(double memoryUsage);
	void publishProcessList(std::vector<std::wstring> processList);
};

