#pragma once
#include <string>
#include <iostream>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>
std::string hashSHA256(std::string inputString);