#pragma once

#include <string>

class IOutput
{
  public:
    virtual ~IOutput() = default;
    virtual void write(const std::string&) = 0;
    virtual void writeLine(const std::string&) = 0;
};

class ConsoleOutput : public IOutput
{
  public:
    void write(const std::string&) override;
    void writeLine(const std::string&) override;
};
