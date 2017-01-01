#include "RestClient.h"
#include "Utlity.h"

std::wstring RestClient::getResponseBody(http_response& response) {

	auto body = response.body();
	stringstreambuf sbuffer;
	auto size = body.read_to_end(sbuffer).get();
	auto &collection = sbuffer.collection();
	std::wstringstream str;
	str << collection.c_str();
	return str.str();
}

std::wstring RestClient::get(std::wstring url, uri_builder& builder) {
	
	http_client client(url);
	http_request req(methods::GET);
	std::wstring responseText;
	req.set_request_uri(builder.to_string());
	try {
		client.request(req)
			.then([&responseText,this](http_response response) {
				if (response.status_code() == status_codes::OK) {
					responseText = getResponseBody(response);
					return responseText;
				}
				else {
					std::wstring  error = L"";
					std::wcout << "Error " << response.status_code() << "\n";
					concurrency::cancel_current_task();
					return error;
				}
		
		}).wait();
	}
	catch (http_exception const & e) {
		std::wcout << e.what() << std::endl;
		Logger::instance().logText(e.what());
	}
	return responseText;
}

std::wstring RestClient::getAuthToken(std::wstring mail, std::wstring mac) {

	std::wstringstream url;
	url <<m_host <<RESTISSUETOKEN;
	uri_builder builder;
	builder.append_query(EMAIL, mail);
	builder.append_query(MACADDRESS, mac);
	return get(url.str(), builder);
}


pplx::task<void> RestClient:: post(std::wstring url, web::json::value jvalue) {
	return pplx::create_task([this, url, jvalue]() {
			http_client client(m_host);
			return client.request(methods::POST, url, jvalue);
			})
			.then([](http_response response){
				if (response.status_code() == status_codes::OK){
					return response.extract_json();
				}
				else{
					std::stringstream str;
					str <<"Post" << response.status_code();
					Logger::instance().logText(str.str());
				}
				return pplx::task_from_result(web::json::value());
			})
			.then([](pplx::task<web::json::value> jasonTask){
				try{
					auto value = jasonTask.get();
				 
				}
				catch (http_exception const & e){
					std::wcout << e.what() << std::endl;
					Logger::instance().logText(e.what());
				}
			 
			});
}
void RestClient::post_block(std::wstring url, web::json::value jvalue)
{
	pplx::create_task([url,jvalue, this](){
		return post(url, jvalue);
	}).wait();
}

void  RestClient::post_noblock(std::wstring url, web::json::value jvalue)
{
	pplx::create_task([url, jvalue, this]() {
		return post(url, jvalue);
	});
}
void  RestClient::registerDevice(std::wstring mail, std::wstring mac) {
	
 	std::wstringstream url;
	url << m_host << RESTREGISTER;
	web::json::value builder;
	builder[EMAIL] = web::json::value(mail);
	builder[MACADDRESS] = web::json::value(mac);
	post_block(url.str(), builder);

}


void RestClient::publishCpu(double cpuUsage, std::wstring clientKey) {
	
	std::wstringstream url;
	url << m_host << RESTCPU;
	web::json::value builder;
	builder[CLIENTKEY] = web::json::value(clientKey);
	builder[CPUUSAGE]= web::json::value::number(cpuUsage);
	post_noblock(url.str(), builder);
}

void  RestClient::publishMemory(double memoryUsage, std::wstring clientKey) {
	
	std::wstringstream url;
	url << m_host << RESTMEMORY;
	web::json::value builder;
	builder[CLIENTKEY] = web::json::value(clientKey);
	builder[MEMORYUSAGE] = web::json::value::number(memoryUsage);
	post_noblock(url.str(), builder);
}

void  RestClient::publishProcessList(std::vector<std::wstring>  processList, std::wstring clientKey) {

	std::wstringstream url;
	url << m_host << RESTPROCESS;
	web::json::value builder;;
	builder[CLIENTKEY] = web::json::value(clientKey);
	int i = 0;
	builder[PROCESSLIST] = web::json::value::array(processList.size());
	for (auto itr : processList) {
		builder[PROCESSLIST].as_array()[i++] = json::value::string(itr);
	}
	post_noblock(url.str(), builder);
}
