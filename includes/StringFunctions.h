#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace MyString
{
    string JoinString(string ArrString[], short Length, string seperator)
    {
        string MyString = "";

        for (int i = 0; i < Length; i++)
            MyString += (i != Length - 1) ? ArrString[i] + seperator : ArrString[i];

        return MyString;
    }
    string JoinString(vector<string> vArrString, string seperator)
    {
        string MyString = "";

        for (string &S1 : vArrString)
            MyString += S1 + seperator;

        return MyString.substr(0, MyString.length() - seperator.length());
    }
    vector<string> MySplit(string Line, string delim)
    {
        vector<string> vMySplit;
        short Position;
        string sWord;

        while ((Position = Line.find(delim)) != string::npos)
        {
            sWord = Line.substr(0, Position);

            if (sWord != " ")
                vMySplit.push_back(sWord);

            Line.erase(0, Position + delim.length());
        }
        if (Line != "")
            vMySplit.push_back(Line);

        return vMySplit;
    }
    string TrimLeft(string Line)
    {
        string delim = " ";

        int Position;

        if ((Position = Line.find_first_not_of(delim)) != string::npos)
            Line.erase(0, Position);
        else
            Line.clear();
        return Line;
    }
    string TrimRight(string Line)
    {
        string delim = " ";

        int Position;

        if ((Position = Line.find_last_not_of(delim)) != string::npos)
            Line.erase(Position + 1);
        else
            Line.clear();

        return Line;
    }
    string MyTrim(string Line)
    {
        return TrimRight(TrimLeft(Line));
    }
}