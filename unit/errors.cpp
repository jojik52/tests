#include "errors.h"

UnknownError::UnknownError(const string &func, bool is_critical)
    : func(func), is_critical(is_critical)
{
    this->time = std::time(nullptr);
}

const char *UnknownError::what() const noexcept
{   
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&time));
    this->message = "[" + string(buffer) + "]\t";
    this->message += this->is_critical ? "[Critical: True]\t" : "[Critical: False]\t";
    this->message += "[" + this->name + " in " + this->func + "]\n";
    return this->message.c_str();
}

string UnknownError::getName() const
{
    return this->name;
}

string UnknownError::getFunc() const
{
    return this->func;
}

string UnknownError::getMessage() const
{
    return this->message;
}

time_t UnknownError::getTime() const
{
    return this->time;
}

bool UnknownError::isCritical() const
{
    return this->is_critical;
}

// Конструкторы производных классов с указанием имени
InvalidArgumentError::InvalidArgumentError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "InvalidArgumentError";
}

// Ошибки чтения-записи
InvalidLineFormat::InvalidLineFormat(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "InvalidLineFormat";
}

ReadWriteError::ReadWriteError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "ReadWriteError";
}

// Ошибки сокета
CreateSocketError::CreateSocketError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "CreateSocketError";
}

BindSocketError::BindSocketError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "BindSocketError";
}

ListenSocketError::ListenSocketError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "ListenSocketError";
}

ShutdownSocketError::ShutdownSocketError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "ShutdownSocketError";
}

AcceptConnectionError::AcceptConnectionError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "AcceptConnectionError";
}

RecvDataError::RecvDataError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "RecvDataError";
}

SendDataError::SendDataError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "SendDataError";
}

// Ошибки аутентификации
InvalidAuthDataFormatError::InvalidAuthDataFormatError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "InvalidAuthDataFormatError";
}

InvalidLoginOrPasswordError::InvalidLoginOrPasswordError(const string &func, bool is_critical)
    : UnknownError(func, is_critical)
{
    this->name = "InvalidLoginOrPasswordError";
}
