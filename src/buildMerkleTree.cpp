#pragma once
#include <vector>
#include <iostream>
#include "Nodes.hpp"
#include "hashFunc.hpp"

std::vector<leafNode*> hashDataToLeaf(std::vector<dataNode*>& dataVec)
{
    std::vector<leafNode*> leafVec;
    if (dataVec.size() == 0) return leafVec;

    // duplicate the last element if size is odd
    if (dataVec.size() % 2)
    {
        dataNode* duplicateLast = new dataNode;
        duplicateLast -> value = dataVec.back() -> value;
        dataVec.push_back(duplicateLast);
    }

    int size = dataVec.size();
    for (int i = 0; i < size; ++i)
    {
        std::string data(1, (dataVec[i]) -> value);
        leafNode* newLeaf = new leafNode;
        newLeaf -> hash = hashSHA256(data);
        newLeaf -> pData = dataVec[i];
        dataVec[i] -> pParent = newLeaf;
        leafVec.push_back(newLeaf);
    }
    return leafVec;
}

std::vector<internalNode*> buildLeaf(std::vector<leafNode*> leafVec)
{
    std::vector<internalNode*> nodeVec;
    if (leafVec.size() == 0) return nodeVec;

    // duplicate the last element if size is odd, the duplicated's pData is the same as the last
    if (leafVec.size() % 2)
    {
        leafNode* duplicateLast = new leafNode;
        duplicateLast -> hash = leafVec.back() -> hash;
        duplicateLast -> pData = leafVec.back() -> pData;
        leafVec.push_back(duplicateLast);
    }

    int size = leafVec.size();
    for (int i = 0; i < size; i += 2)
    {
        internalNode* newNode = new internalNode;
        newNode -> pLeft = leafVec[i]; newNode -> pRight = leafVec[i + 1];
        leafVec[i] -> pParent = newNode; leafVec[i + 1] -> pParent = newNode;
        std::string concatenation = leafVec[i] -> hash + leafVec[i + 1] -> hash;
        newNode -> hash = hashSHA256(concatenation);
        nodeVec.push_back(newNode);
    }
    return nodeVec;
}

internalNode* buildInternal(std::vector<internalNode*>& nodeVecLower)
{
    std::vector<internalNode*> nodeVecUpper;
    if (nodeVecLower.size() == 0) return nullptr;
    if (nodeVecLower.size() == 1)
    {
        return nodeVecLower[0];
    }

    // duplicate the last element if size is odd, the duplicated's pLeaft and pRight is nullptr
    if (nodeVecLower.size() % 2)
    {
        internalNode* duplicateLast = new internalNode;
        duplicateLast -> hash = nodeVecLower.back() -> hash;
        nodeVecLower.push_back(duplicateLast);
    }

    int size = nodeVecLower.size();
    for (int i = 0; i < size; i += 2)
    {
        internalNode* newNode = new internalNode;
        newNode -> pLeft = nodeVecLower[i]; newNode -> pRight = nodeVecLower[i + 1];
        nodeVecLower[i] -> pParent = newNode; nodeVecLower[i + 1] -> pParent = newNode;
        std::string concatenation = nodeVecLower[i] -> hash + nodeVecLower[i + 1] -> hash;
        newNode -> hash = hashSHA256(concatenation);
        nodeVecUpper.push_back(newNode);
    }
    return buildInternal(nodeVecUpper);
}

internalNode* buildMerkleTree(std::string input)
{
    std::vector<dataNode*> dataVec;
    for (int i = 0; i < (int)input.size(); ++i)
    {
        dataNode* newData = new dataNode;
        newData -> value = (unsigned char)input[i];
        dataVec.push_back(newData);
    }
    std::vector<leafNode*> leafVec = hashDataToLeaf(dataVec);
    std::vector<internalNode*> nodeVec = buildLeaf(leafVec);
    internalNode* pRoot = buildInternal(nodeVec);
    return pRoot;
}
