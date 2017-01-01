#pragma once
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <memory>
#include <locale>
#include <codecvt>
#include <unordered_map>
#include <vector>
#include <string>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class RestServer
{
	typedef std::function<void(http_request)> Callback;
	std::unique_ptr<http_listener> m_listener;
	void createRoutes();
	std::unordered_map<std::wstring, Callback> m_postRoutes  ;
	std::unordered_map<std::wstring, Callback> m_getRoutes;
	
public:
	RestServer() = default;
	~RestServer() = default;
	int start(int port);
	void handleGet(http_request request);
	void handlePost(http_request request);
	void handlePut(http_request request);
	void handleDelete(http_request request);
};

