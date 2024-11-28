#include "sha1.h"

string SHA1(const string &data)
{
    CryptoPP::SHA1 sha1;
    string hash;
    CryptoPP::StringSource(
        data, true, new CryptoPP::HashFilter(
            sha1, new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(hash), true)));
    return hash;
}
