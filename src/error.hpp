#pragma once

#include <string>

enum class ErrorCode
{
    invalid_choice,
    email_phone_in_use,
    cant_open_file,
    invalid_email_password_empty,
    invalid_email_password,
    no_reservations_to_pay
};

class Error
{
public:
    static void display(ErrorCode);
};