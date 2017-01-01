#pragma once
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "IMessageHandler.h"
#include "Utlity.h"
using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
#define STATUS L"status"
#define CLIENTKEY L"clientkey"
#define EMAIL L"email"
#define MACADDRESS L"macaddress"
#define PROCESSLIST L"processlist"
#define MEMORYUSAGE L"memoryusage"
#define CPUUSAGE L"cpuusage"

class RestClient: public IMessageHandler
{
	std::wstring getResponseBody(http_response& response);
	std::wstring m_host;
	 

public:
	RestClient(std::string host) :m_host(Utlity::s2ws(host)){};
	~RestClient() = default;
	RestClient() = delete;
	std::wstring get(std::wstring url, uri_builder& builder); 
	pplx::task<void>  post(std::wstring url, web::json::value jvalue);
	void  post_block(std::wstring url, web::json::value jvalue);
	void  post_noblock(std::wstring url, web::json::value jvalue);

	void  publishCpu(double cpuUsage, std::wstring clientKey);
	void  publishMemory(double memoryUsage, std::wstring clientKey);
	void  publishProcessList(std::vector<std::wstring>  processList, std::wstring clientKey);
	void  registerDevice(std::wstring mail, std::wstring mac);
	std::wstring getAuthToken(std::wstring mail, std::wstring mac);

};

