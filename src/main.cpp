#include <iostream>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "hashFunc.hpp"
#include "Nodes.hpp"
#include "buildMerkleTree.hpp"
int main() {
    std::string myString = "seminars";
    internalNode* pRoot = buildMerkleTree(myString);
    std::cout << pRoot -> hash << std::endl;
    return 0;
}
