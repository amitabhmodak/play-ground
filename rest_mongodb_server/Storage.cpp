#include "Storage.h"
#include <iostream>
#include <sstream>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include "StorageManager.h"

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


Storage::~Storage(){
}

int Storage::createAccount(std::string userName, std::string password, std::string mail, std::string phone) {
	

	std::cout << "creating account with " << userName <<" "<< password << " " << mail << " " << phone << " \n" ;
	if (countNumberOfUsers(userName, password) > 0) {
		return 0;
	}
	bsoncxx::builder::stream::document doc;
	auto docView = doc << "uname" << userName
		<< "password" << password
		<< "email" << mail
		<< "phone" << phone << finalize;

	std::string str = bsoncxx::to_json(docView.view());
	auto collection = (*m_client)[DB][USER];
	auto result = collection.insert_one(docView.view());

	 
	return 1;
}

int Storage::login(std::string userName, std::string password) {
	 
	auto numberOfUsers = countNumberOfUsers(userName, password);
	if (numberOfUsers == 1) {

		return 1;
	}
	return 0;
	
}

std::int64_t Storage::countNumberOfUsers(std::string userName, std::string password) {
	auto collection = (*m_client)[DB][USER];
	return collection.count(document{} << "uname" << userName << "password" << password << finalize);

}

std::string Storage::getUserList() {
	
	auto collection = (*m_client)[DB][USER];
	mongocxx::options::find opts{};
	opts.projection(document{} << "uname" << 1 << "_id" << 0 << finalize);
	auto cursor = collection.find(document{} << finalize, opts);
	std::stringstream stream;
	auto arr = array{};
	for (auto doc : cursor) {
		auto ele = doc["uname"];
		arr << ele.get_utf8().value.to_string();
	}
	auto doc = document{};
	doc << "userlist" << arr;
	stream << bsoncxx::to_json(doc.view());
	return stream.str();
}

 