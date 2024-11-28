#ifndef ERRORS_H
#define ERRORS_H

#include <string>
#include <ctime>
#include <typeinfo>
#include <exception>

using namespace std;

class UnknownError : public exception
{
public:
    UnknownError(const string &func, bool is_critical = false);

    string getName() const;
    string getFunc() const;
    string getMessage() const;
    time_t getTime() const;
    bool isCritical() const;

    const char *what() const noexcept override;

protected:
    string name = "UnknownError";

private:
    string func;            ///< Имя функции, в которой возникло исключение.
    time_t time;            ///< Время возникновения исключения.
    bool is_critical;       ///< Флаг критичности исключения.
    mutable string message; ///< Сообщение об ошибке.
};

// Ошибки парсера
class InvalidArgumentError : public UnknownError
{
public:
    InvalidArgumentError(const string &func, bool is_critical = false);
};

// Ошибки чтения/записи
class ReadWriteError : public UnknownError
{
public:
    ReadWriteError(const string &func, bool is_critical = false);
};

class InvalidLineFormat : public UnknownError
{
public:
    InvalidLineFormat(const string &func, bool is_critical = false);
};

// Ошибки сокета
class CreateSocketError : public UnknownError
{
public:
    CreateSocketError(const string &func, bool is_critical = false);
};

class BindSocketError : public UnknownError
{
public:
    BindSocketError(const string &func, bool is_critical = false);
};
class ListenSocketError : public UnknownError
{
public:
    ListenSocketError(const string &func, bool is_critical = false);
};

class ShutdownSocketError : public UnknownError
{
public:
    ShutdownSocketError(const string &func, bool is_critical = false);
};

class AcceptConnectionError : public UnknownError
{
public:
    AcceptConnectionError(const string &func, bool is_critical = false);
};

class RecvDataError : public UnknownError
{
public:
    RecvDataError(const string &func, bool is_critical = false);
};

class SendDataError : public UnknownError
{
public:
    SendDataError(const string &func, bool is_critical = false);
};

// Ошибки аутентификации
class InvalidAuthDataFormatError : public UnknownError
{
public:
    InvalidAuthDataFormatError(const string &func, bool is_critical = false);
};

class InvalidLoginOrPasswordError : public UnknownError
{
public:
    InvalidLoginOrPasswordError(const string &func, bool is_critical = false);
};

#endif // ERRORS_H
