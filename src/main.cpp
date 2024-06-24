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
    std::vector<dataNode*> dataVec;
    for (int i = 0; i < (int)myString.size(); ++i)
    {
        dataNode* newData = new dataNode;
        newData -> value = (unsigned char)myString[i];
        dataVec.push_back(newData);
    }
    std::vector<leafNode*> leafVec = hashDataToLeaf(dataVec);
    std::vector<internalNode*> nodeVec = buildLeaf(leafVec);
    internalNode* root = buildInternal(nodeVec);

    std::cout << root -> hash << std::endl;
    return 0;
}
