#pragma once

#include<memory>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>

class StorageManager
{
	std::unique_ptr<mongocxx::instance> m_dbInst;
	StorageManager() {
		m_dbInst = std::make_unique<mongocxx::instance>();
	}
	~StorageManager() = default;
	
public:
	
	StorageManager(StorageManager const&) = delete;              
	StorageManager(StorageManager&&) = delete;                   
	StorageManager& operator=(StorageManager const&) = delete;   
	StorageManager& operator=(StorageManager &&) = delete;       


	std::unique_ptr<mongocxx::client> getClient() {
		mongocxx::uri uri("mongodb://localhost:27017");
		return std::make_unique<mongocxx::client>(uri);
	}
	static StorageManager&  instance() {
		static StorageManager storageInstance;
		return storageInstance;
	}
	
};

