#pragma once

#include <string>
#include <map>
#include <functional>

// Simple HTTP client interface
// This can be implemented with different backends (libcurl, cpr, WinHTTP, etc.)

class HttpClient
{
public:
    virtual ~HttpClient() = default;

    virtual std::string get(const std::string &url, const std::map<std::string, std::string> &headers = {}) = 0;
    virtual std::string post(const std::string &url, const std::string &body, const std::map<std::string, std::string> &headers = {}) = 0;

    // Static factory method - returns null if no HTTP backend is available
    static std::unique_ptr<HttpClient> create();
};

// Mock HTTP client for development/testing (returns empty responses)
class MockHttpClient : public HttpClient
{
public:
    std::string get(const std::string &url, const std::map<std::string, std::string> &headers = {}) override
    {
        // Return empty JSON for mock responses
        return "{}";
    }

    std::string post(const std::string &url, const std::string &body, const std::map<std::string, std::string> &headers = {}) override
    {
        return R"({"reservationId": "mock_reservation_123"})";
    }
};