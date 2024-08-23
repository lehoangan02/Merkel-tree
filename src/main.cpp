#include <iostream>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "hashFunc.hpp"
#include "Nodes.hpp"

int main() {
    std::string myString = "seminars";
    internalNode* pRoot1 = buildMerkleTree(myString);
    std::cout << pRoot1 -> hash << std::endl;

    //This task is for checking the existance
    std::cout << "\n1) Checking for the existance" << std::endl;
    unsigned char targetValues[] = { 'a', 'b', 'c', 'd' }; 
    for (unsigned char target : targetValues) {
        dataNode* foundNode = findDataNode(pRoot1, target);

        if (foundNode) {
            std::cout << "Found data node with value: " << foundNode->value << std::endl;
        }
        else {
            std::cout << "Data node with value '" << target << "' not found." << std::endl;
        }
    }

    // Test generating a Merkle proof for a specific leaf node
    std::cout << "\n2) Generating Merkle proof path" << std::endl;
    std::vector<dataNode*> dataVec;
    for (int i = 0; i < (int)myString.size(); ++i) {
        dataNode* newData = new dataNode;
        newData->value = (unsigned char)myString[i];
        dataVec.push_back(newData);
    }

    std::vector<leafNode*> leafVec = hashDataToLeaf(dataVec);
    leafNode* targetLeaf = leafVec[0]; // The leaf node corresponding to 's'
    std::vector<std::string> proof = generateMerkleProof(targetLeaf);

    std::cout << "Merkle Proof for 's':" << std::endl;
    for (const std::string& hash : proof) {
        std::cout << hash << std::endl;
    }

    //This task is for checking the difference between two Merkle Trees.
    std::string myString2 = "seninars";
    internalNode* pRoot2 = buildMerkleTree(myString);
    std::cout << pRoot2->hash << std::endl;

    if (pRoot1->hash != pRoot2->hash) {
        std::cout << "=> There might be some difference between two trees." << std::endl;
        std::vector<std::pair<dataNode*, dataNode*>> res;
        findDifferences(pRoot1, pRoot2, res);
        printDifferences(pRoot1, pRoot2);
    }
    else std::cout << "=> No difference !" << std::endl;

    return 0;
}
