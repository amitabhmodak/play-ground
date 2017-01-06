#include "RestServer.h"
#include "RequestHandler.h"
#include <vector>
#include <string>
#include "Storage.h"
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

int RestServer::start(int port) {
	std::wstringstream url;
	//url << L"http://*:" << port;
	url << L"http://localhost:" << port;
	m_listener = std::make_unique<http_listener>(url.str()); 
	createRoutes();
	try
	{
		m_listener
			->open()
			.then([&url]() {
					std::wcout<<"Listening "<<url.str();
				})
			.wait();

		while (true);
	}
	catch (std::exception const & e)
	{
		std::wcout << e.what() << std::endl;
	}
	return 1;
}

void RestServer::createRoutes() {
	m_listener->support(methods::GET, [this](http_request request) {this->handleGet(request); });
	m_listener->support(methods::POST, [this](http_request request) {this->handlePost(request); });
	m_listener->support(methods::PUT, [this](http_request request) {this->handlePut(request); });
	m_listener->support(methods::DEL, [this](http_request request) {this->handleDelete(request); });

	m_postRoutes.emplace(RESTCPU, [](http_request request) {
		auto handler = std::make_unique<RequestHandler>();
		handler->postCpu(request); });

	m_postRoutes.emplace(RESTMEMORY, [](http_request request) {
		auto handler = std::make_unique<RequestHandler>();
		handler->postMemory(request); });

	m_postRoutes.emplace(RESTPROCESS, [this](http_request request) {
		auto handler = std::make_unique<RequestHandler>();
		handler->postProcess(request); });

	m_postRoutes.emplace(RESTREGISTER, [this](http_request request) {
		auto handler = std::make_unique<RequestHandler>();
		handler->registerDevice(request); });

	m_getRoutes.emplace(RESTISSUETOKEN, [this](http_request request) {
		auto handler = std::make_unique<RequestHandler>();
		handler->issueToken(request); });
}

void RestServer::handleGet(http_request request)
{
	auto path = request.request_uri().path();
	auto itr = m_getRoutes.find(path);
	if (itr == m_getRoutes.end())
		request.reply(status_codes::BadRequest, "Error");
	else
		(itr->second)(request);
}

void RestServer::handlePost(http_request request) {
	std::wstring str;
	str = request.absolute_uri().to_string();
	auto itr = m_postRoutes.find(str);
	if(itr == m_postRoutes.end())
		request.reply(status_codes::BadRequest, "Error");
	else  
		(itr->second)(request);
}

void RestServer::handlePut(http_request request) {
	request.reply(status_codes::BadRequest, "Error");
}
void RestServer::handleDelete(http_request request) {
	request.reply(status_codes::BadRequest, "Error");
}
 