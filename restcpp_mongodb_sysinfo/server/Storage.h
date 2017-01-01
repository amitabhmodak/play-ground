#pragma once
#include<memory>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <string>
#define DB "crossover"
#define COLLECTION_CPU "cpu"
#define COLLECTION_MEMORY "memory"
#define COLLECTION_PROCESS "process"
#define COLLECTION_ACCOUNT "account"

class Storage
{
	std::unique_ptr<mongocxx::client> m_client;
	
public:
	Storage() ;
	~Storage() = default;
	int publishCpu(std::string cliendId, double cpuUsage);
	int publishMemory(std::string cliendId, double memoryUsage);
	int publishProcessList(std::string cliendId, std::vector<std::string> allRunningProcess);
	std::string registerDevice(std::string email, std::string macaddress);

	std::int64_t countNumberOfdevices(std::string clientkey);
	std::int64_t countNumberOfdevicesWithMailid(std::string mailId);
	std::string getAuthToken(std::string email, std::string mac);
	std::string createClientKey(std::string mail, std::string key);
	void deleteAllData();
};



