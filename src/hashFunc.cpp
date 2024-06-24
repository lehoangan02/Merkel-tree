#include "hashFunc.hpp"
std::string hashSHA256(std::string inputString)
{
    unsigned char hash[EVP_MD_size(EVP_sha256())];
    unsigned int length;
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    std::stringstream hexStream;
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(ctx, inputString.c_str(), inputString.length());
    EVP_DigestFinal(ctx, hash, &length);
    EVP_MD_CTX_free(ctx);
    for (int i = 0; i < 32; ++i)
    {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return hexStream.str();
}