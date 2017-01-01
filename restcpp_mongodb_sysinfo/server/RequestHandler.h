#pragma once
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <memory>
#include <locale>
#include <codecvt>
#include <unordered_map>
#include <vector>
#include <string>
#include "Storage.h"
#include "Utlity.h"
#include "AlertHandler.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;


class RequestHandler
{
	Storage m_storage;
	AlertHandler m_alert;
public:
	RequestHandler() = default;
	~RequestHandler() = default;

	bool isTokenValid(std::wstring token);
	void registerDevice(http_request request);
	void issueToken(http_request request);
	void postCpu(http_request request);
	void postMemory(http_request request);
	void postProcess(http_request request);
	void handle_request(http_request request, bool checkToken,
		std::function<http::status_code(json::value &, json::value &)> action);
 
};

