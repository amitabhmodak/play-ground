#include "Client.h"
#include "DeviceInfo.h"
#include "Utlity.h"
#include "RestClient.h"

Client::Client(std::string mail, std::unique_ptr<IMessageHandler> handler){
	m_mail = Utlity::s2ws(mail);
	m_messageHandler = std::move(handler);
}


Client::~Client(){
}

void Client::start() {
	
 	if (isDeviceRegistered()) {
		Logger::instance().logText("Device is registered\n");
	}
	else {
		Logger::instance().logText("Device is not registered\n");
		regiserDevice();
		isDeviceRegistered();
	}

	std::wcout <<"Key "<< m_key;
	 
    while (true) 
	{
		auto cpuUsage = m_info.getCpuUsage();
		auto memoryUsage = m_info.getMemoryUsage();
		auto processList = m_info.getRunningProcesses();
		publishCpu(cpuUsage);
		publishMemory(memoryUsage);
		publishProcessList(processList); 
	 	Sleep(50000);
	}
}

bool  Client::isDeviceRegistered(){

 	if (m_key.empty()) {
		auto key = Utlity::getValue("Device.clientkey", "clientconfig.ini");
		if (key.empty())
			key = m_info.getMacAddress();
		m_key = m_messageHandler->getAuthToken(m_mail,Utlity::s2ws(key));
 	}
	return !m_key.empty();
}

void  Client::regiserDevice() {
	Logger::instance().logText("Registering device\n");
	auto key = Utlity::getValue("Device.clientkey", "clientconfig.ini");
	if(key.empty())
		key = m_info.getMacAddress();

	m_messageHandler->registerDevice(m_mail, Utlity::s2ws(key));
}

void Client::publishCpu(double cpuUsage) {
	m_messageHandler->publishCpu(cpuUsage, m_key);
}

void Client::publishMemory(double memoryUsage) {
	m_messageHandler->publishMemory(memoryUsage, m_key);
}
void Client::publishProcessList(std::vector<std::wstring> processList) {
	m_messageHandler->publishProcessList(processList, m_key);
}