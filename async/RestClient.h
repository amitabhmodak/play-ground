#pragma once

#define SUB_KEY "INSERT_SUBSCTIPTION_KEY_HERE"
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class RestClient
{
	std::wstring getResponseBody(http_response& response);
public:
	RestClient() = default;
	~RestClient() = default;
 
	pplx::task<std::wstring >getAuthToken();
	pplx::task<std::wstring> translate(std::wstring translateText, std::wstring language);
};

