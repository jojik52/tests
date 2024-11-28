#include "arguments.h"
#include "rw.h"
#include "server.h"
#include "sha1.h"
#include <UnitTest++/UnitTest++.h>
#include <fstream>

using namespace std;

// Тесты для Parser
SUITE(ParserTests) {
    TEST(DefaultConstructor) {
        Parser parser;
        CHECK_EQUAL("/etc/vcalc.conf", parser.getPathToUsers());
        CHECK_EQUAL("/var/log/vcalc.log", parser.getPathToLog());
        CHECK_EQUAL("127.0.0.1", parser.getAddress());
        CHECK_EQUAL(33333, parser.getPort());
    }

    TEST(ParseArguments) {
        Parser parser;
        const char *argv[] = {"program", "--users", "/path/to/users", "--log", "/path/to/log", "--address", "192.168.0.1", "--port", "231"};
        int argc = sizeof(argv) / sizeof(argv[0]);
        parser.parse(argc, const_cast<char**>(argv));

        CHECK_EQUAL("/path/to/users", parser.getPathToUsers());
        CHECK_EQUAL("/path/to/log", parser.getPathToLog());
        CHECK_EQUAL("192.168.0.1", parser.getAddress());
        CHECK_EQUAL(231, parser.getPort());
    }

    TEST(HelpMethod) {
        Parser parser;
        stringstream buffer;
        streambuf *old = cout.rdbuf(buffer.rdbuf());
        parser.help();
        string output = buffer.str();
        cout.rdbuf(old);
        CHECK(!output.empty());
    }
}

// Тесты для RW
SUITE(RWTests) {
    TEST(ReadUsers) {
        ofstream testFile("test_users.txt");
        testFile << "user1:pass1\n";
        testFile << "user2:pass2\n";
        testFile.close();

        map<string, string> users = readUsers("test_users.txt");
        CHECK_EQUAL("pass1", users["user1"]);
        CHECK_EQUAL("pass2", users["user2"]);

        remove("test_users.txt");
    }

    TEST(WriteLog) {
        UnknownError error("testFunc", true);
        error.what(); // Инициализация сообщения об ошибке

        writeLog("test_log.txt", error);

        ifstream testFile("test_log.txt");
        stringstream buffer;
        buffer << testFile.rdbuf();
        testFile.close();

        CHECK(!buffer.str().empty());
        remove("test_log.txt");
    }
}

// Тесты для Server
SUITE(ServerTests) {
    TEST(Constructor) {
        map<string, string> users = {{"user", "pass"}};
        Server server("127.0.0.1", 33333, users);
        CHECK_EQUAL("127.0.0.1", server.getAddress());
        CHECK_EQUAL(33333, server.getPort());
        CHECK_EQUAL("pass", server.getUsers()["user"]);
    }

    TEST(StartupShutdown) {
        map<string, string> users = {{"user", "pass"}};
        Server server("127.0.0.1", 33333, users);
        server.startup();
        server.shutdown();
    }

    TEST(ConnectAuthentication) {
        map<string, string> users = {{"user", "P@ssW0rd"}};
        Server server("127.0.0.1", 33333, users);
        server.startup();
        server.connect();
        server.authentication();
        server.shutdown();
    }
}

// Тесты для SHA1
SUITE(SHA1Tests) {
    TEST(HashEmptyString) {
        string hash = SHA1("");
        CHECK_EQUAL("DA39A3EE5E6B4B0D3255BFEF95601890AFD80709", hash);
    }

    TEST(HashHelloWorld) {
        string hash = SHA1("Hello, world!");
        CHECK_EQUAL("943A702D06F34599AEE1F8DA8EF9F7296031D699", hash);
    }

    TEST(HashLoremIpsum) {
        string hash = SHA1("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
        CHECK_EQUAL("E7505BEB754BED863E3885F73E3BB6866BDD7F8C", hash);
    }
}

// Основная функция для запуска всех тестов
int main(int argc, char **argv) {
    return UnitTest::RunAllTests();
}
