#pragma once

#include <string>

class IInput
{
public:
    virtual ~IInput() = default;

    [[nodiscard]] virtual int readInt() = 0;
    [[nodiscard]] virtual double readDouble() = 0;
    [[nodiscard]] virtual std::string readLine() = 0;
};

class ConsoleInput : public IInput
{
public:
    [[nodiscard]] int readInt() override;
    [[nodiscard]] double readDouble() override;
    [[nodiscard]] std::string readLine() override;
};