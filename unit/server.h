#ifndef SERVER_H
#define SERVER_H

#include "sha1.h"
#include "errors.h"

#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <cstdint>
#include <iostream>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

class Server
{
public:
    Server(
        const string &address,
        uint16_t port,
        const map<string, string> &users);

    string &getAddress();
    uint16_t &getPort();
    map<string, string> &getUsers();
    void startup();
    void shutdown();
    void connect();
    void authentication();
    void averange();

private:
    string address;            ///< Адрес сервера.
    uint16_t port;             ///< Порт сервера.
    map<string, string> users; ///< логины и пароли пользователей.
    int socket;                ///< Сокет сервера.
    int client;                ///< Сокет клиента.
};

#endif // SERVER_H
