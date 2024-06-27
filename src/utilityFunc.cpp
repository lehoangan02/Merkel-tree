#include <iostream>
#include <string>

bool printDiffences(std::string s1, std::string s2)
{
    if (s1.length() != s2.length())
        return false;
    int l = s1.length();
    bool isSameString = true;
    for (int i = 0; i < l; ++i)
    {
        if (s1[i] != s2[i])
        {
            std::cout << s1[i] << " --> " << s2[i] << '\n';
            isSameString = false;
        }
    }
    return isSameString;
}