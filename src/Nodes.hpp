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
    dataNode* pData = nullptr;
};
struct dataNode
{
    leafNode* pParent = nullptr;
    unsigned char value = 0;
};
