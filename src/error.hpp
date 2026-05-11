#pragma once

#include <string>

enum class ErrorCode
{
    invalidChoice,
    emailPhoneInUse,
    cantOpenFile,
    invalidEmailPasswordEmpty,
    invalidEmailPassword,
    noReservationsToPay
};

class Error
{
public:
    static void display(ErrorCode);
};