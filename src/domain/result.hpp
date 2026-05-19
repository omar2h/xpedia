#pragma once

#include <string>
#include <utility>

template<typename T>
class Result
{
    bool m_success;
    T m_value;
    std::string m_error;

    Result(bool success, T value, std::string error)
        : m_success(success)
        , m_value(std::move(value))
        , m_error(std::move(error))
    {
    }

public:
    static Result ok(T value)
    {
        return Result(true, std::move(value), {});
    }

    static Result fail(std::string error)
    {
        return Result(false, T{}, std::move(error));
    }

    [[nodiscard]] bool isSuccess() const { return m_success; }
    [[nodiscard]] bool isError() const { return !m_success; }

    [[nodiscard]] T& value() { return m_value; }
    [[nodiscard]] const T& value() const { return m_value; }

    [[nodiscard]] const std::string& error() const { return m_error; }
};
