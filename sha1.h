#ifndef SHA1_H
#define SHA1_H

#include <string>

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>

using namespace std;

string SHA1(const string &data);

#endif // SHA1_H
