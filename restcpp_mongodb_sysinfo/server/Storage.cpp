
#include <iostream>
#include <sstream>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include "StorageManager.h"
#include "Storage.h"
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::array;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

Storage::Storage(){
	m_client = std::move(StorageManager::instance().getClient());
}
 
int Storage::publishCpu(std::string cliendId, double cpuUsage) {
	
	std::cout << "Adding Cpu Usage, clientId: " << cliendId << "\t CPU usage: " << cpuUsage<< " \n";
	 
	if (cliendId.empty() == true)
	{
		std::cout << "ClientId empty\n";
		return 0;
	}
		
	
	if (cpuUsage < 0) {
		std::cout << "CPU invalid data\n";
		return 0;
	}
		

	bsoncxx::builder::stream::document doc;
	auto docView = doc  << "clientId" << cliendId
						<< "cpuUsage" << cpuUsage
						<< finalize;

	std::string str = bsoncxx::to_json(docView.view());
	auto collection = (*m_client)[DB][COLLECTION_CPU];
	auto result = collection.insert_one(docView.view());
	return 1;
}

int Storage::publishMemory(std::string cliendId, double memoryUsage) {
	std::cout << "Adding memory Usage cliendId " << cliendId << " " << memoryUsage << " \n";
	 
	if (cliendId.empty() == true)
	{
		std::cout << "ClientId empty\n";
		return 0;
	}
	if (memoryUsage < 0) {
		std::cout << "memory invalid data\n";
		return 0;
	}
	bsoncxx::builder::stream::document doc;
	auto docView = doc << "clientId" << cliendId
		<< "memoryUsage" << memoryUsage
		<< finalize;

	std::string str = bsoncxx::to_json(docView.view());
	auto collection = (*m_client)[DB][COLLECTION_MEMORY];
	auto result = collection.insert_one(docView.view());
	return 1;
}

int Storage::publishProcessList(std::string cliendId, std::vector<std::string> allRunningProcess) {
	std::cout << "Adding running process: cliendId " << cliendId << " Number of processes " << allRunningProcess.size() << " \n";
	if (cliendId.empty() == true)
	{
		std::cout << "ClientId empty\n";
		return 0;
	}

	if (allRunningProcess.size() == 0) {
		std::cout << "no process invalid data\n";
		return 0;
	}

	bsoncxx::builder::stream::document doc;
	auto arr = array{};

	for (auto processName : allRunningProcess) {
		arr << processName;
	}
	auto docView = doc << "clientId" << cliendId
		<< "runningprocess"
		<< arr
		<< finalize;

	std::string str = bsoncxx::to_json(docView.view());
	auto collection = (*m_client)[DB][COLLECTION_PROCESS];
	auto result = collection.insert_one(docView.view());
	return 1;
}

std::string Storage::registerDevice(std::string email, std::string macaddress) {

	if (email.empty() == true)
		return"";

	if (macaddress.empty() == true)
		return"";

	auto uniqueKey = createClientKey(email, macaddress);
	std::cout << "Device Register with " << uniqueKey << " " << email<<" \n";

	if (countNumberOfdevices(uniqueKey) > 0) {
		std::cout << "Client id exisit\n";
		return "";
	}
	 
	
	bsoncxx::builder::stream::document doc;
	auto docView = doc << "email" << email
		<< "clientkey" << uniqueKey
		<<"mac"<<macaddress
		<< finalize;

	std::string str = bsoncxx::to_json(docView.view());
	auto collection = (*m_client)[DB][COLLECTION_ACCOUNT];
	auto result = collection.insert_one(docView.view());
	return uniqueKey;
}

std::string  Storage::createClientKey(std::string mail, std::string key) {
	std::stringstream stream;
	stream << mail << key;
	return stream.str();
}

std::int64_t Storage::countNumberOfdevices(std::string clientkey) {
	if (clientkey.empty() == true)
		return 0;
	auto collection = (*m_client)[DB][COLLECTION_ACCOUNT];
	auto count = collection.count(document{} << "clientkey" << clientkey << finalize);
	return count;

}

std::int64_t Storage::countNumberOfdevicesWithMailid(std::string mailId) {
	auto collection = (*m_client)[DB][COLLECTION_ACCOUNT];
	return collection.count(document{} << "email" << mailId << finalize);
}

std::string Storage::getAuthToken(std::string email, std::string mac) {
	std::string key;
	auto collection = (*m_client)[DB][COLLECTION_ACCOUNT];
	 
	mongocxx::options::find opts{};
	opts.projection(document{} << "clientkey" << 1 << "_id" << 0 << finalize);
	auto cursor = collection.find(document{} << "email" << email <<"mac"<< mac << finalize, opts);
	for (auto doc : cursor) {
		auto ele = doc["clientkey"];
		key =  ele.get_utf8().value.to_string();
		 
	}
	return key;
}

void Storage::deleteAllData() {

	{
		auto db = (*m_client)[DB][COLLECTION_ACCOUNT];
		db.delete_many({});
	}

	{
		auto db = (*m_client)[DB][COLLECTION_CPU];
		db.delete_many({});
	}
	{
		auto db = (*m_client)[DB][COLLECTION_MEMORY];
		db.delete_many({});
	}
	{
		auto db = (*m_client)[DB][COLLECTION_PROCESS];
		db.delete_many({});
	}

}