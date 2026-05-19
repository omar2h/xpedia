#pragma once

#include <stdexcept>
#include <string>

class AppException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class PersistenceException : public AppException
{
public:
    using AppException::AppException;
};

class AuthException : public AppException
{
public:
    using AppException::AppException;
};

class ValidationException : public AppException
{
public:
    using AppException::AppException;
};

class BusinessException : public AppException
{
public:
    using AppException::AppException;
};

class ApiException : public AppException
{
public:
    using AppException::AppException;
};
