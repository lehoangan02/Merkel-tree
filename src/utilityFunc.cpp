#include <iostream>
#include <string>
#include <vector>

void printDifferences(std::string s1, std::string s2)
{
    std::vector<int> res = findDifferences(s1, s2);
    if (res.size() == 0)
    {
        std::cout << "Same\n";
        return;
    }
    for (int i = 0; i < res.size(); ++i)
    {
        std::cout << res[i] << ": ";
        if (res[i] >= s1.length())
            std::cout << "null" << " --> " << s2[res[i]] << '\n';
        else if (res[i] >= s2.length())
            std::cout << s1[res[i]] << " --> " << "null" << '\n';
        else
            std::cout << s1[res[i]] << " --> " << s2[res[i]] << '\n';
    }
}

std::vector<int> findDifferences(std::string s1, std::string s2)
{       
    if (s1.length() > s2.length())
        return findDifferences(s2, s1);
    std::vector<int> res;
    int l = s2.length();
    for (int i = 0; i < l; ++i)
    {
        if (i >= s1.length() || s1[i] != s2[i])
            res.push_back(i);
    }
    return res;
}