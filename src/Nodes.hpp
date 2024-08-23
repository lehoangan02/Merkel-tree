#pragma once
#include <string>

struct dataNode;
struct internalNode
{
    bool isLeaf = false;
    std::string hash;
    internalNode* pParent = nullptr;
    internalNode* pLeft = nullptr;
    internalNode* pRight = nullptr;
};

struct leafNode : internalNode
{
    leafNode()
    {
        isLeaf = true;
    }
    dataNode* pData;
};

struct dataNode
{
    leafNode* pParent = nullptr;
    unsigned char value = 0;
};


std::vector<leafNode*> hashDataToLeaf(std::vector<dataNode*>& dataVec);
std::vector<internalNode*> buildLeaf(std::vector<leafNode*> leafVec);
internalNode* buildInternal(std::vector<internalNode*>& nodeVecLower);
internalNode* buildMerkleTree(std::string input);
dataNode* findDataNode(internalNode* currentNode, const std::string& targetHash);
std::vector<std::string> generateMerkleProof(leafNode* targetLeaf);
void printMerkleProof(const std::vector<std::string>& proof); //from targetleaf to root
void findDifferences(internalNode* pRoot1, internalNode* pRoot2, std::vector<std::pair<dataNode*, dataNode*>>& res);
void printDifferences(internalNode* pRoot1, internalNode* pRoot2);