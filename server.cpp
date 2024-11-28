#include "server.h"

// Конструктор
Server::Server(
    const string &address,
    uint16_t port,
    const map<string, string> &users)
    : address(address), port(port),
      users(users), socket(-1), client(-1) {}

void Server::startup()
{
    this->socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket == -1)
    {
        ::close(this->socket);
        throw CreateSocketError(__func__, true);
    }
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);
    server_addr.sin_addr.s_addr = inet_addr(this->address.c_str());

    if (bind(this->socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        close(this->socket);
        throw BindSocketError(__func__, true);
    }

    if (listen(this->socket, 5) == -1)
    {
        close(this->socket);
        throw ListenSocketError(__func__, true);
    }

    cout << "Server startup!!!\n Listenig on "
         << this->address << ":" << this->port << "\n";
}

void Server::shutdown()
{
    if (this->socket != -1)
    {
        ::shutdown(this->socket, SHUT_RDWR);
        ::close(this->socket);
        this->socket = -1;
    }

    if (this->client != -1)
    {
        ::shutdown(this->client, SHUT_RDWR);
        ::close(this->client);
        this->client = -1;
    }

    if (this->socket + this->client != -2)
        throw ShutdownSocketError(__func__, true);
}

string &Server::getAddress()
{
    return this->address;
}

uint16_t &Server::getPort()
{
    return this->port;
}

map<string, string> &Server::getUsers()
{
    return this->users;
}

// Метод для ожидания соединений
void Server::connect()
{
    this->client = accept(this->socket, nullptr, nullptr);
    if (this->client == -1)
    {
        ::close(this->client);
        throw AcceptConnectionError(__func__);
    }

    cout << "Accepted connection from client\n";
}

// Метод для аутентификации
void Server::authentication()
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytes_read = recv(this->client, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read <= 0)
    {
        ::close(this->client);
        throw RecvDataError(__func__);
    }

    string auth_data(buffer);
    cout << "Authentication data: " << auth_data << "\n";

    if (auth_data.size() < 57) // user + 16 символов соли + 40 символов хеша
    {
        ::close(this->client);
        throw InvalidAuthDataFormatError(__func__);
    }

    string login = auth_data.substr(0, auth_data.size() - 56);    // извлекаем логин
    string salt = auth_data.substr(auth_data.size() - 56, 16);    // извлекаем соль
    string client_hash = auth_data.substr(auth_data.size() - 40); // извлекаем хеш

    cout << "Login: " << login
         << ", Salt: " << salt
         << ", Hash: " << client_hash << "\n";

    auto it = this->users.find(login);
    if (it == this->users.end())
    {
        string error_message = "ERR";
        send(this->client, error_message.c_str(), error_message.size(), 0);
        ::close(this->client);
        throw InvalidLoginOrPasswordError(__func__);
    }

    string password = it->second;
    string data_to_hash = salt + password;
    string server_hash = SHA1(data_to_hash);
    cout << "Hash: " << server_hash << "\n";

    if (client_hash != server_hash)
    {
        string error_message = "ERR";
        send(this->client, error_message.c_str(), error_message.size(), 0);
        ::close(this->client);
        throw InvalidLoginOrPasswordError(__func__);
    }
    string success_message = "OK";
    send(this->client, success_message.c_str(), success_message.size(), 0);
    cout << "Client authenticated successfully\n";
}

// Метод для вычисления среднего арифметического векторов
void Server::averange()
{
    uint32_t vectors;
    uint32_t values;
    int32_t value;

    // Чтение количества векторов от клиента
    ssize_t bytes_read = recv(this->client, &vectors, sizeof(vectors), 0);
    if (bytes_read <= 0)
    {
        ::close(this->client);
        throw RecvDataError(__func__);
    }

    cout << "Number of vectors: " << vectors << "\n";

    // Обработка каждого вектора
    for (uint32_t i = 0; i < vectors; ++i)
    {
        // Чтение количества значений в векторе от клиента
        bytes_read = recv(this->client, &values, sizeof(values), 0);
        if (bytes_read <= 0)
        {
            ::close(this->client);
            throw RecvDataError(__func__);
        }

        cout << "Number of values for vector " << i + 1
             << ": " << values << "\n";

        int32_t sum = 0;
        for (uint32_t j = 0; j < values; ++j)
        {
            // Чтение значения вектора от клиента
            bytes_read = recv(this->client, &value, sizeof(value), 0);
            if (bytes_read <= 0)
            {
                ::close(this->client);
                throw RecvDataError(__func__);
            }
            cout << "Averange for vector " << i + 1
                 << ", element " << j + 1 << ": " << value << "\n";

            sum += value;
        }

        int32_t averange = static_cast<int32_t>(
            static_cast<double>(sum) / values);

        // Отправка среднего арифметического обратно клиенту
        ssize_t bytes_sent = send(this->client, &averange, sizeof(averange), 0);
        if (bytes_sent <= 0)
        {
            ::close(this->client);
            SendDataError(__func__);
        }
        cout << "Sent average for vector " << i + 1
             << ": " << averange << "\n";
    }

    cout << "Calculated and sent averages for all vectors" << "\n";
}
