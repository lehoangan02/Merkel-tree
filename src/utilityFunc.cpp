#include <iostream>
#include <vector>
#include "Nodes.hpp"

dataNode* findDataNode(internalNode* currentNode, const std::string& targetHash) {
    if (currentNode == nullptr) {
        return nullptr; // Base case: reached the end of the tree
    }

    if (currentNode->isLeaf) {
        // Check if the leaf node's hash matches the target hash
        if (currentNode->hash == targetHash) {
            return currentNode->pData;
        }
        else {
            return nullptr; // Leaf node doesn't match
        }
    }

    // Recursively search left and right subtrees
    dataNode* leftResult = findDataNode(currentNode->pLeft, targetHash);
    if (leftResult != nullptr) {
        return leftResult;
    }
    return findDataNode(currentNode->pRight, targetHash);
}

std::vector<std::string> generateMerkleProof(leafNode* targetLeaf) {
    std::vector<std::string> proof;
    internalNode* currentNode = targetLeaf;

    while (currentNode->pParent != nullptr) {
        internalNode* parent = currentNode->pParent;

        if (parent->pLeft == currentNode) {

            if (parent->pRight != nullptr) { // Sibling is the right child
                proof.push_back(parent->pRight->hash);
            }
        }
        else {
            proof.push_back(parent->pLeft->hash);  // Sibling is the left child
        }

        currentNode = parent;
    }

    return proof;
}

void printMerkleProof(const std::vector<std::string>& proof) {
    std::cout << "Merkle Proof:\n";
    for (const std::string& hash : proof) {
        std::cout << hash << std::endl;
    }
}

void findDifferences(internalNode* pRoot1, internalNode* pRoot2, std::vector<std::pair<dataNode*, dataNode*>>& res) //Assuming 2 trees are the same size
{       
    if (!pRoot1 || !pRoot2)
        return;
    if (pRoot1->isLeaf && pRoot2->isLeaf)
    {
        if (pRoot1->hash != pRoot2->hash)
        {
            dataNode* node1 = static_cast<leafNode*>(pRoot1)->pData;
            dataNode* node2 = static_cast<leafNode*>(pRoot2)->pData;
            res.push_back(std::pair<dataNode*, dataNode*>(node1, node2));
        }
    }
    else if (!pRoot1->isLeaf && !pRoot2->isLeaf)
    {
        if (pRoot1->hash == pRoot2->hash)
            return;
        findDifferences(pRoot1->pLeft, pRoot2->pLeft, res);
        findDifferences(pRoot1->pRight, pRoot2->pRight, res);
    } 
}

void printDifferences(internalNode* pRoot1, internalNode* pRoot2)
{
    std::vector<std::pair<dataNode*, dataNode*>> res;
    findDifferences(pRoot1, pRoot2, res);
    if (res.size() == 0)
    {
        std::cout << "Same\n";
        return;
    }
    for (int i = 0; i < res.size(); ++i)
    {
        std::cout << res[i].first->value << " --> " << res[i].second->value << "\n";
    }
}