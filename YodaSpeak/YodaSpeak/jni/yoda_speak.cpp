
#include <cpprest/http_client.h>

#include <yoda_speak.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

namespace yoda_utilities
{

pplx::task<utility::string_t> convert_to_yoda(const utility::string_t &text)
{
	// Full details about the API at http://www.mashape.com/ismaelc/yoda-speak
	http_client client(U("https://yoda.p.mashape.com/yoda"));

	// Create HTTP an request.
	http_request yodaRequest(methods::GET);

	// Setup headers.
#error Go to http://www.mashape.com/ and get your own key and enter below.
	yodaRequest.headers().add(U("X-Mashape-Key"), U("Your Key"));

	// Setup and encode query parameters.
	uri_builder uriBuilder;
	uriBuilder.append_query(U("sentence"), text);
	yodaRequest.set_request_uri(uriBuilder.to_string());

	// Initiate request
	pplx::task<http_response> requestTask = client.request(yodaRequest);

	// Extract and return the HTTP response body as a string.
	return requestTask.then([](http_response response)
	{
		if(response.status_code() != status_codes::OK)
		{
			// Handle non-success status code by returning a string with error message.
			std::stringstream errorMsg;
			errorMsg << "Unexpected HTTP status code from Yoda speak server: " << response.status_code();
			pplx::task_from_result(errorMsg.str());
		}

		return response.extract_string();
	});
}

pplx::task<utility::string_t> check_grammar(const utility::string_t &text)
{
	// Full details about the API at https://textalytics.com/core/stilus-info#doc
	http_client client(U("http://textalytics.com/core/stilus-1.2"));

	// Create HTTP request.
	http_request grammarRequest(methods::POST);

	// Setup and encode query parameters.
	uri_builder uriBuilder;
#error Go to https://textalytics.com/register to get key
	uriBuilder.append_query(U("key"), U("Your key"));
	uriBuilder.append_query(U("lang"), U("en"));
	uriBuilder.append_query(U("txt"), text);
	grammarRequest.set_request_uri(uriBuilder.to_uri());

	// Initiate request
	pplx::task<http_response> requestTask = client.request(grammarRequest);

	// Extract and the HTTP response body as a JSON object.
	return requestTask.then([](http_response response)
	{
		if(response.status_code() != status_codes::OK)
		{
			// Handle non-success status code by returning a string with error message.
			std::stringstream errorMsg;
			errorMsg << "Unexpected HTTP status code from the textalytics server: " << response.status_code();
			pplx::task_from_result(errorMsg.str());
		}

		return response.extract_json();
	}).then([](const json::value &value)
	{
		utility::stringstream_t errors;

		// Service returns all sorts of information.
		// We only care to look at the array of error result objects.
		const json::array &resultList = value.at(U("result_list")).as_array();
		for(const auto & result : resultList)
		{
			errors << U("Error:") << std::endl
				   << U("    ") << result.at(U("msg")).as_string() << std::endl
				   << U("    ") << result.at(U("text")).as_string() << std::endl;
		}

		if(resultList.size() == 0)
		{
			errors << U("No errors detected!");
		}
		return errors.str();
	});
}

}
