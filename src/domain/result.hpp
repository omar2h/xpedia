#pragma once

#include <optional>
#include <string>

template <typename T>
class Result
{
    std::optional<T> m_value;
    std::string m_error;

    bool m_success{false};

public:
    static Result success(T value)
    {
        Result r;

        r.m_success = true;
        r.m_value = std::move(value);

        return r;
    }

    static Result failure(
        const std::string &error)
    {
        Result r;

        r.m_success = false;
        r.m_error = error;

        return r;
    }

    bool isSuccess() const
    {
        return m_success;
    }

    T &value()
    {
        return *m_value;
    }

    const std::string &error() const
    {
        return m_error;
    }
};