#pragma once

#include <string>

class IInput
{
public:
    virtual ~IInput() = default;
    [[nodiscard]] virtual int readInt() = 0;
    [[nodiscard]] virtual int readInt(int low, int high) = 0;
    [[nodiscard]] virtual int readInt(int low, int high, bool allowCancel) = 0;
    [[nodiscard]] virtual std::string readString() = 0;
};

class ConsoleInput : public IInput
{
public:
    [[nodiscard]] int readInt() override;
    [[nodiscard]] int readInt(int low, int high) override;
    [[nodiscard]] int readInt(int low, int high, bool allowCancel) override;
    [[nodiscard]] std::string readString() override;
};
