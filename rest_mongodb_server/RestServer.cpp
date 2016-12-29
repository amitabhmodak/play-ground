#include "RestServer.h"

#include<string>
#include "Storage.h"
#include "Base64.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
#define TRACE(msg)            std::wcout << msg
#define TRACE_ACTION(a, k, v) std::wcout << a << L" (" << k << L", " << v << L")\n"

namespace converter {
	std::wstring s2ws(const std::string& str)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
	}

	std::string ws2s(const std::wstring& wstr)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}
}
//std::map<utility::string_t, utility::string_t> dictionary;
//
//void handle_get(http_request request)
//{
//	TRACE(L"\nhandle GET\n");
//
//	json::value obj;
//	for (auto const & p : dictionary)
//	{
//		obj[p.first] = json::value::string(p.second);
//	}
//
//	// this is just for debugging
//	utility::stringstream_t stream;
//	obj.serialize(stream);
//	std::wcout << stream.str();
//
//	request.reply(status_codes::OK, obj);
//}

//void display_field_map_json(json::value & jvalue)
//{
//	if (!jvalue.is_null())
//	{
//		auto obj = jvalue.as_object();
//		obj.find(L"username");
//		for (auto const & e : obj)
//		{
//			if (e.second.is_string())
//				std::wcout << e.first << L" : " << e.second.as_string() << std::endl;
//			if (e.second.is_integer())
//				std::wcout << e.first << L" : " << e.second.as_integer() << std::endl;
//		}
//	}
//}

RestServer::RestServer()
{
}


RestServer::~RestServer()
{
}


int RestServer::start(int port) {
	 
	std::wstringstream url;
	url << L"http://localhost:" << port;
	m_listener = std::make_unique<http_listener>(url.str()); 
	createRoutes();
	try
	{
		m_listener
			->open()
			.then([]() {TRACE(L"\nstarting to listen\n"); })
			.wait();

		while (true);
	}
	catch (std::exception const & e)
	{
		std::wcout << e.what() << std::endl;
	}
	return 1;
}

void RestServer:: createRoutes() {

	m_listener->support(methods::GET, [this](http_request request) {this->handleGet(request); });
	m_listener->support(methods::POST, [this](http_request request) {this->handlePost(request); });
	m_listener->support(methods::PUT, [this](http_request request) {this->handlePut(request); });
	m_listener->support(methods::DEL, [this](http_request request) {this->handleDelete(request); });


}

void RestServer::handleGet(http_request request)
{
	TRACE(L"\nhandle GET\n");
	std::wstring str  ;
 
	auto http_get_vars = uri::split_query(request.request_uri().query());
	

	auto token_name = http_get_vars.find(U("token"));
	if (token_name == end(http_get_vars)) {
		request.reply(status_codes::BadRequest, "Error");
		return;
	}
	auto token = token_name->second;
	if (isTokenValid(token)) {
		auto path = request.request_uri().path();
		if (path.compare(L"/users") == 0) {
			getUsers(request);
		}
	}
	else {
		request.reply(status_codes::BadRequest, "Error");
	}
	  
}
bool RestServer::isTokenValid(std::wstring token) {

	Storage storage;
	Base64 base;
	auto userList = storage.getUserList();
	auto str = converter::ws2s(token);
	auto decoded = base.base64_decode(str);
	std::string decodedStr;
	for (auto ch : decoded) {
		decodedStr += ch;
	}
	if (userList.find(decodedStr) != std::string::npos)  
		return true;
	return false;
}
void RestServer::handlePost(http_request request) {

	std::wstring str;
	str = request.absolute_uri().to_string();
	if (str.compare(L"/login")== 0) {
		if (!login(request)) {
			request.reply(status_codes::BadRequest, "Error");
		}
	}
	else if (str.compare(L"/createAccount") == 0) {
		if (!createAccount(request)) {
			request.reply(status_codes::BadRequest, "Error");
		}
	}
	else {
		request.reply(status_codes::BadRequest, "Error");
	}
	
}
void RestServer::handlePut(http_request request) {

}
void RestServer::handleDelete(http_request request) {

}


void getValue(web::json::object& obj, std::wstring key) {
	auto val = obj.at(key);
	
}
int RestServer::login(http_request request) {

	handle_request(request,false, [](json::value &jvalue,json::value &answer)->http::status_code {
		
		auto userName = jvalue[L"username"];
		auto password = jvalue[L"password"];
		if (userName.is_null() || password.is_null()) {
			return status_codes::BadRequest;
		}
		auto serUser = userName.serialize();
		Storage storage;
		auto result = storage.login(converter::ws2s(userName.as_string()), converter::ws2s(password.as_string()));
		if (result == 1) {
			auto str = converter::ws2s(userName.as_string());
			Base64 base;
			Base64::BYTE* byte = (Base64::BYTE*) str.data();
			auto encoded = base.base64_encode(byte, str.length());
			answer[L"status"] = json::value(converter::s2ws(encoded));
		}
		else {
			answer[L"status"] = json::value(result);
		}
				
		return status_codes::OK;
	});
	 
	return status_codes::InternalError;
}
int RestServer::createAccount(http_request request) {

	handle_request(request,false, [](json::value &jvalue, json::value &answer)->http::status_code {

		auto userName = jvalue[L"username"];
		auto password = jvalue[L"password"];
		auto mail = jvalue[L"email"];
		auto phone = jvalue[L"phone"];

		if (userName.is_null() || password.is_null()
			|| mail.is_null() || phone.is_null()) {
			return status_codes::BadRequest;
		}
	 
		Storage storage;
		auto resut = storage.createAccount(converter::ws2s(userName.as_string()), converter::ws2s(password.as_string()),
			converter::ws2s(mail.as_string()), converter::ws2s(phone.as_string()));

		answer[L"status"] = json::value(resut);
		return status_codes::OK;
	});

	return status_codes::InternalError;
}
int RestServer::getUsers(http_request request) {
	 
	Storage storage;
	auto str = converter::s2ws(storage.getUserList());
	auto answer = json::value(str);
	request.reply(status_codes::OK, answer.as_string());
	return status_codes::OK;
}

int RestServer::deleteUser(http_request request) {
	return status_codes::InternalError;
}

void RestServer::handle_request(http_request request, bool checkToken,
	std::function<http::status_code(json::value &, json::value &)> action)
{
	json::value answer;
	http::status_code status = status_codes::BadRequest;
	 
	request
		.extract_json()
		.then([&answer, &action, &status, checkToken, this](pplx::task<json::value> task) {
		try
		{
			auto & jvalue = task.get();

			if (!jvalue.is_null())
			{
				if (!checkToken) {
					status = action(jvalue, answer);
				}
				else {
					auto token = jvalue[L"token"];
					if (!token.is_null()) {
						if(this->isTokenValid(token.as_string()))
							status = action(jvalue, answer);
					}
				}
				
				
			}
		}
		catch (http_exception const & e)
		{
			std::wcout<<L"Error encountered " << e.what() << std::endl;
			status = status_codes::InternalError;
		}
	})
		.wait();

	request.reply(status, json::value(answer));
}