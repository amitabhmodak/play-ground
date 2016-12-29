#pragma once
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <memory>
#include <locale>
#include <codecvt>
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class RestServer
{
	std::unique_ptr<http_listener> m_listener;
	void createRoutes();
public:
	RestServer();
	~RestServer();
	int start(int port);
	bool isTokenValid(std::wstring token);
protected:
	void handleGet(http_request request);
	void handlePost(http_request request);
	void handlePut(http_request request);
	void handleDelete(http_request request);

	int login(http_request request);
	int createAccount(http_request request);
	int getUsers(http_request request);
	int deleteUser(http_request request);

	void handle_request(http_request request, bool checkToken,
		std::function<http::status_code (json::value &, json::value &)> action);

	
	
};

