#pragma once
#include<memory>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <string>
#define DB "amimTest"
#define USER "user"
class Storage
{
	 
	std::unique_ptr<mongocxx::client> m_client;
public:
	Storage();
	~Storage();
	 
	int createAccount(std::string userName, std::string password, std::string mail, std::string phone);
	int login(std::string userName, std::string password);
	std::int64_t countNumberOfUsers(std::string userName, std::string password);
	std::string getUserList();
	

};

