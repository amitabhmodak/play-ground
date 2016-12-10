 /***

Refer 
http://docs.microsofttranslator.com/oauth-token.html
http://docs.microsofttranslator.com/text-translate.html#!/default/get_Translate
***/

#include "RestClient.h"

pplx::task<std::wstring> RestClient::getAuthToken() {
	return pplx::create_task([]	{
		std::wstring str;
		http_client client(U("https://api.cognitive.microsoft.com/sts/v1.0/issueToken"));
		uri_builder builder;
		builder.append_query(U("Subscription-Key"), SUB_KEY);
	 
		return client.request(methods::POST, builder.to_string());
	})
	.then([=](http_response response)	{
		if (response.status_code() == status_codes::OK)		{
			return getResponseBody(response);
		}
		else {
			std::wstring  error = L"Error " ;
			std::wcout << error << response.status_code() <<"\n";
			concurrency::cancel_current_task();
			return error;
		}
	});
}
 

pplx::task<std::wstring> RestClient::translate(std::wstring translateText, std::wstring language) {
	return pplx::create_task([=]{
		return getAuthToken();
	})
	.then([=](std::wstring key) {
		http_client client(U("https://api.microsofttranslator.com/v2/http.svc/Translate"));
		uri_builder builder;
		builder.append_query(U("text"), translateText);
		builder.append_query(U("to"), language);
		std::wstring token = L"Bearer " + key;;
		builder.append_query(U("appid"), token);
		http_request req(methods::GET);
		req.set_request_uri(builder.to_string());
		return client.request(req);
	})
	.then([=](http_response response){
		if (response.status_code() == status_codes::OK) {
			return getResponseBody(response);
		}
		else {
			std::wstring  error = L"Error ";
			std::wcout << error << response.status_code() << "\n";
			concurrency::cancel_current_task();
			return error;
		}
	});
}


std::wstring RestClient::getResponseBody(http_response& response) {
	auto body = response.body();
	stringstreambuf sbuffer;
	auto size = body.read_to_end(sbuffer).get();
	auto &collection = sbuffer.collection();
	std::wstringstream str;
	str << collection.c_str();
	return str.str();
}