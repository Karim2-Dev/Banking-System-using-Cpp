#pragma once
#include <iostream>
using namespace std;

namespace MyPrint
{
    string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t += "\t";
        }
        return t;
    }
} 
