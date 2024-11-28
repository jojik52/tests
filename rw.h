#ifndef RW_H
#define RW_H

#include <map>
#include <string>

#include "errors.h"

using namespace std;

map<string, string> readUsers(const string &path);
void writeLog(const string &path, const UnknownError &e);

#endif // RW_H
