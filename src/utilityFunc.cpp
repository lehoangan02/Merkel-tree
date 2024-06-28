#include <iostream>
#include <vector>
#include "Nodes.hpp"

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