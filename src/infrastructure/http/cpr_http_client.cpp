#include "cpr_http_client.hpp"
#include <cpr/cpr.h>
#include <iostream>

CprHttpClient::CprHttpClient() = default;

std::string CprHttpClient::get(const std::string& url, const std::map<std::string, std::string>& headers)
{
    cpr::Header cprHeaders;
    for (const auto& [key, value] : headers)
    {
        cprHeaders[key] = value;
    }

    auto response = cpr::Get(cpr::Url{url}, cpr::Header{cprHeaders});

    if (response.error)
    {
        std::cerr << "HTTP GET error: " << response.error.message << std::endl;
        return "{}";
    }

    return response.text;
}

std::string CprHttpClient::post(const std::string& url, const std::string& body,
                                const std::map<std::string, std::string>& headers)
{
    cpr::Header cprHeaders;
    for (const auto& [key, value] : headers)
    {
        cprHeaders[key] = value;
    }

    auto response = cpr::Post(cpr::Url{url}, cpr::Body{body}, cpr::Header{cprHeaders});

    if (response.error)
    {
        std::cerr << "HTTP POST error: " << response.error.message << std::endl;
        return "{}";
    }

    if (response.status_code >= 400)
    {
        std::cerr << "HTTP POST " << response.status_code << " — returning body anyway" << std::endl;
    }

    return response.text;
}

// ---------------------------------------------------------------------------
// HttpClient::create()  — static factory
// ---------------------------------------------------------------------------
std::unique_ptr<HttpClient> HttpClient::create()
{
    return std::make_unique<CprHttpClient>();
}