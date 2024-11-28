#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cstring>
#include <iostream>

#include "errors.h"

using namespace std;

class Parser
{
public:
    Parser();

    void parse(int argc, char *argv[]);
    void help() const;

    std::string &getPathToUsers();
    std::string &getPathToLog();
    std::string &getAddress();
    int getPort() const;

private:
    std::string pathToUsers; ///< Путь к файлу с пользователями.
    std::string pathToLog;   ///< Путь к файлу логов.
    std::string address;     ///< Адрес.
    int port;                ///< Порт.
};

#endif // PARSER_H
