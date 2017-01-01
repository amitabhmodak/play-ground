#pragma once
#include <string>
#include <codecvt>
#include <vector>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/filestream.h>
#include <mutex>
 
using namespace web;
using namespace web::http;
using namespace concurrency::streams;

#define STATUS L"status"
#define CLIENTKEY L"clientkey"
#define EMAIL L"email"
#define MACADDRESS L"macaddress"
#define PROCESSLIST L"processlist"
#define MEMORYUSAGE L"memoryusage"
#define CPUUSAGE L"cpuusage"

#define RESTCPU L"/postCpu"
#define RESTMEMORY L"/postMemory"
#define RESTPROCESS L"/postProcess"
#define RESTREGISTER L"/registerDevice"
#define RESTISSUETOKEN L"/issueToken"

#define SERVERINI "serverconfig.ini"
#define CLIENTINI "clientconfig.ini"

class Utlity
{
public:
	Utlity() = default;
	~Utlity() = default;

	 
	static std::wstring s2ws(const std::string& str)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
	}

	static std::string ws2s(const std::wstring& wstr)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}

	static std::vector<std::string> parse(web::json::value list) {
		std::vector<std::string> listValue;

		auto arr = list.as_array();
		for (auto itr : arr) {
			auto string = ws2s(itr.as_string());
			listValue.push_back(string);
		}
		return listValue;
	}
	static std::string Utlity::getValue(std::string text, std::string configFile);
};


class Logger
{
 	Logger() {
 	}
	~Logger() {
		std::lock_guard<std::mutex> guard(m_lock);
		if (m_fileStream.is_open()) {
 			m_fileStream.close();
		}
	};
	ostream m_fileStream;
	std::mutex m_lock;
	void init() {
		if (m_fileStream.is_open())
			return;
			pplx::task<void> requestTask = fstream::open_ostream(U("client.log"))
				.then([this](ostream outFile)
			{
				m_fileStream = outFile;
			});
		}
public:
	Logger(Logger const&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(Logger const&) = delete;
	Logger& operator=(Logger &&) = delete;
	 
	static Logger&  instance() {
		static Logger logInstance;
		logInstance.init();
		return logInstance;
	}

	void logText(std::string text) {
		pplx::create_task([this, text] {
			if (m_fileStream.is_open()) {
				std::lock_guard<std::mutex> guard(m_lock);
				m_fileStream.print(text);
				m_fileStream.print("\n");
			}
		});
	}
	void logText(std::wstring text) {
		logText(Utlity::ws2s(text));
	}
};