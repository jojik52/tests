#include "arguments.h"

// Метод для парсинга аргументов командной строки
Parser::Parser()
    : pathToUsers("/etc/vcalc.conf"),
      pathToLog("/var/log/vcalc.log"),
      address("127.0.0.1"), port(33333) {}

void Parser::parse(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            this->help();
        }
        else if ((strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--users") == 0) && (i + 1 < argc))
        {
            this->pathToUsers = argv[i + 1];
            ++i; // Пропустить значение параметра
        }
        else if ((strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--log") == 0) && (i + 1 < argc))
        {
            this->pathToLog = argv[i + 1];
            ++i; // Пропустить значение параметра
        }
        else if ((strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) && (i + 1 < argc))
        {
            this->port = std::stoi(argv[i + 1]);
            ++i; // Пропустить значение параметра
        }
        else if ((strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--address") == 0) && (i + 1 < argc))
        {
            this->address = argv[i + 1];
            ++i; // Пропустить значение параметра
        }
        else
        {
            throw InvalidArgumentError(__func__, true);
        }
    }

    std::cout << "Arguments: --users " << this->pathToUsers
              << " --log " << this->pathToLog
              << " --address " << this->address
              << " --port " << this->port << std::endl;
}

std::string &Parser::getPathToUsers()
{
    return this->pathToUsers;
}

std::string &Parser::getPathToLog()
{
    return this->pathToLog;
}

std::string &Parser::getAddress()
{
    return this->address;
}

int Parser::getPort() const
{
    return this->port;
}

// Метод для вывода справки
void Parser::help() const
{
    std::cout << "  -h, --help                 Show this help message and exit\n"
              << "  -u, --users                Path to the database file\n"
              << "  -l, --log                  Path to the log file\n"
              << "  -p, --port                 Port number (default: 33333)\n"
              << "  -a, --address              Address (default: 127.0.0.1)\n";
}
