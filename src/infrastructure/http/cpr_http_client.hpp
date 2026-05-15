#pragma once

#include "http_client.hpp"
#include <string>
#include <map>

// CPR-based HTTP client implementation
// Requires cpr library (https://github.com/libcpr/cpr)

class CprHttpClient : public HttpClient
{
public:
    CprHttpClient();
    ~CprHttpClient() override = default;

    std::string get(const std::string &url, const std::map<std::string, std::string> &headers = {}) override;
    std::string post(const std::string &url, const std::string &body, const std::map<std::string, std::string> &headers = {}) override;
};