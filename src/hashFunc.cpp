#include "hashFunc.hpp"
std::string hashSHA256(std::string inputString)
{
    unsigned char hash[32];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, inputString.c_str(), inputString.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (int i = 0; i < 32; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}