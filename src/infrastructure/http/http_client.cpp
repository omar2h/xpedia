#include "http_client.hpp"
#include "cpr_http_client.hpp"

std::unique_ptr<HttpClient> HttpClient::create()
{
    return std::make_unique<CprHttpClient>();
}