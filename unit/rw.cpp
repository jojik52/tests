#include "rw.h"
#include "errors.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Функция для чтения пользователей из файла
map<string, string> readUsers(const string &path)
{
    map<string, string> users;
    ifstream file(path);

    if (!file.is_open())
        throw ReadWriteError(__func__, true);

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string user, pass;
        if (getline(iss, user, ':') && getline(iss, pass))
            users[user] = pass;
        else
            throw InvalidLineFormat(__func__, true);
    }

    file.close();
    return users;
}

// Функция для записи информации об исключениях в лог-файл
void writeLog(const string &path, const UnknownError &e)
{
    ofstream logFile(path, ios::app);

    if (!logFile.is_open())
        throw ReadWriteError(__func__, true);

    logFile << e.what();
    logFile.close();
}