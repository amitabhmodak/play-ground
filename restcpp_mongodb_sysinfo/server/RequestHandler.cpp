#include "RequestHandler.h"

bool RequestHandler::isTokenValid(std::wstring token) {
	auto count = m_storage.countNumberOfdevices(Utlity::ws2s(token));
	if (count == 1) {
		return true;
	}
	return false;
}

void RequestHandler::handle_request(http_request request, bool checkToken,
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
			if (!jvalue.is_null()) {
				if (!checkToken) {
					status = action(jvalue, answer);
				}
				else {
					auto token = jvalue[CLIENTKEY];
					if (!token.is_null()) {
						if (this->isTokenValid(token.as_string()))
							status = action(jvalue, answer);
					}
				}
			}
		}
		catch (http_exception const & e) {
			std::wcout << L"Error encountered " << e.what() << std::endl;
			status = status_codes::InternalError;
		}
	})
		.wait();
 	request.reply(status, answer);
}


void RequestHandler::postCpu(http_request request) {
	handle_request(request, true, [this](json::value &jvalue, json::value &answer)->http::status_code {
		auto cpuUsage = jvalue[CPUUSAGE];
		auto clientId = jvalue[CLIENTKEY];
		if (cpuUsage.is_null() || clientId.is_null())
			return status_codes::BadRequest;

		if (!cpuUsage.is_number())
			return status_codes::BadRequest;

		if (!clientId.is_string())
			return status_codes::BadRequest;
		m_alert.handleCpuAlert(cpuUsage.as_double(), Utlity::ws2s(clientId.as_string()));
		auto resut = m_storage.publishCpu(Utlity::ws2s(clientId.as_string()), cpuUsage.as_double());
		answer[STATUS] = json::value(resut);
		if (resut == 1)
			return status_codes::OK;
		return status_codes::BadRequest;
	});
}

void RequestHandler::postMemory(http_request request) {
	handle_request(request, true, [this](json::value &jvalue, json::value &answer)->http::status_code {
		auto memoryUsage = jvalue[MEMORYUSAGE];
		auto clientId = jvalue[CLIENTKEY];
		if (memoryUsage.is_null() || clientId.is_null())
			return status_codes::BadRequest;
		
		if(!memoryUsage.is_number())
			return status_codes::BadRequest;

		if(!clientId.is_string())
			return status_codes::BadRequest;

		m_alert.handleMemoryAlert(memoryUsage.as_double(), Utlity::ws2s(clientId.as_string()));
		auto resut = m_storage.publishMemory(Utlity::ws2s(clientId.as_string()), memoryUsage.as_double());
		answer[STATUS] = json::value(resut);
		if(resut == 1)
			return status_codes::OK;
		return status_codes::BadRequest;
	});
}

void RequestHandler::postProcess(http_request request) {
	handle_request(request, true, [this](json::value &jvalue, json::value &answer)->http::status_code {
		auto processList = jvalue[PROCESSLIST];
		auto clientId = jvalue[CLIENTKEY];
		if (processList.is_null() || clientId.is_null())
			return status_codes::BadRequest;
		
		if (!clientId.is_string())
			return status_codes::BadRequest;

		if(!processList.is_array())
			return status_codes::BadRequest;

		auto runningProcesses = Utlity::parse(processList);
		m_alert.handleProcessAlert(runningProcesses.size(), Utlity::ws2s(clientId.as_string()));

  		auto resut = m_storage.publishProcessList(Utlity::ws2s(clientId.as_string()), runningProcesses);
		answer[STATUS] = json::value(resut);
		if (resut == 1)
			return status_codes::OK;
		return status_codes::BadRequest;
	});
}

void RequestHandler::registerDevice(http_request request) {
	handle_request(request, false, [](json::value &jvalue, json::value &answer)->http::status_code {

		auto email = jvalue[EMAIL];
		auto macaddress = jvalue[MACADDRESS];

		if (email.is_null() || macaddress.is_null()) {
			return status_codes::BadRequest;
		}
		
		if (!email.is_string())
			return status_codes::BadRequest;

		if (!macaddress.is_string())
			return status_codes::BadRequest;


		Storage storage;
		auto result = storage.registerDevice(Utlity::ws2s(email.as_string()), Utlity::ws2s(macaddress.as_string()));

		answer[STATUS] = json::value(Utlity::s2ws(result));
		return status_codes::OK;
	});
}
 
void RequestHandler::issueToken(http_request request) {
	auto http_get_vars = uri::split_query(request.request_uri().query());

	auto token_name = http_get_vars.find(EMAIL);
	auto email = uri::decode(token_name->second);

	auto token_key = http_get_vars.find(MACADDRESS);
	auto mac = uri::decode(token_key->second);

	if (mac.empty() == true) {
		request.reply(status_codes::BadRequest, "Error");
		return;
	}
	if (email.empty() == true) {
		request.reply(status_codes::BadRequest, "Error");
		return;
	}
	auto result = m_storage.getAuthToken(Utlity::ws2s(email), Utlity::ws2s(mac));
	request.reply(status_codes::OK, Utlity::s2ws(result));
	
}