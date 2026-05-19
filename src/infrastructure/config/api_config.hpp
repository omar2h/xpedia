#pragma once

#include <cstdlib>
#include <string>
#include <map>

// API Configuration
// This file contains configuration for real API endpoints
// In production, these should be loaded from environment variables or a config file

struct ApiConfig
{
    // Flight APIs
    static inline const std::string BRITISH_AIRWAYS_API_URL = "https://api.britishairways.com";
    static inline const std::string BRITISH_AIRWAYS_API_KEY = ""; // Set via environment variable

    static inline const std::string AIR_FRANCE_API_URL = "https://api.airfrance.com";
    static inline const std::string AIR_FRANCE_API_KEY = ""; // Set via environment variable

    // Hotel APIs
    static inline const std::string HILTON_API_URL = "https://api.hilton.com";
    static inline const std::string HILTON_API_KEY = ""; // Set via environment variable

    static inline const std::string MARRIOTT_API_URL = "https://api.marriott.com";
    static inline const std::string MARRIOTT_API_KEY = ""; // Set via environment variable

    // Payment APIs
    static inline const std::string STRIPE_API_URL = "https://api.stripe.com";
    static inline const std::string STRIPE_API_KEY = ""; // Set via environment variable

    static inline const std::string PAYPAL_API_URL = "https://api.paypal.com";
    static inline const std::string PAYPAL_API_KEY = ""; // Set via environment variable

    // Helper to get API key from environment
    static std::string getEnvVar(const std::string &name)
    {
        if (const char *value = std::getenv(name.c_str()))
        {
            return std::string(value);
        }
        return "";
    }

    // Load all API keys from environment
    static void loadFromEnvironment()
    {
        // This would typically be called at application startup
        // The actual API key values would be set in the environment
    }
};