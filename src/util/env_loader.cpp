#include "env_loader.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

static std::string trimmed(std::string s)
{
    s.erase(0, s.find_first_not_of(" \t\r\n"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1);
    return s;
}

static std::string stripQuotes(const std::string &s)
{
    if (s.size() >= 2 &&
        ((s[0] == '"' && s.back() == '"') ||
         (s[0] == '\'' && s.back() == '\'')))
        return s.substr(1, s.size() - 2);
    return s;
}

static std::string stripInlineComment(const std::string &s)
{
    auto pos = s.find('#');
    if (pos == std::string::npos)
        return s;
    return s.substr(0, pos);
}

bool loadEnvFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "No .env file found at " << path << " — skipping\n";
        return false;
    }

    std::string line;
    int loaded = 0;
    while (std::getline(file, line))
    {
        line = trimmed(line);

        // Skip empty lines and full-line comments
        if (line.empty() || line[0] == '#')
            continue;

        auto eq = line.find('=');
        if (eq == std::string::npos)
            continue;

        std::string key = trimmed(line.substr(0, eq));
        if (key.empty())
            continue;

        std::string value = line.substr(eq + 1);
        value = trimmed(value);
        value = stripInlineComment(value);
        value = trimmed(value);
        value = stripQuotes(value);

#ifdef _WIN32
        // SetEnvironmentVariableA(key.c_str(), value.c_str());
        _putenv_s(key.c_str(), value.c_str());
#else
        setenv(key.c_str(), value.c_str(), 1);
#endif
        ++loaded;
    }

    std::cerr << "Loaded " << loaded << " variables from " << path << "\n";
    return loaded > 0;
}
