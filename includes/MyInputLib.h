#pragma once

#include <iostream>
#include <limits>

using namespace std;

namespace MyInputLib
{

    int ReadNumber(string Msg)
    {
        int Number;
        cout << Msg << endl;
        cin >> Number;

        while (cin.fail())
        {
            cin.clear();

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one\n";

            cin >> Number;
        }
        return Number;
    }
    double ReadDoubleNum(string Msg)
    {
        double Number;
        cout << Msg << endl;
        cin >> Number;

        while (cin.fail())
        {
            cin.clear();

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one\n";

            cin >> Number;
        }
        return Number;
    }
    int ReadPositiveNumber(string Msg)
    {
        int Number;

        do
        {
            cout << Msg << endl;
            cin >> Number;
            while (cin.fail())
            {
                cin.clear();

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid Number, Enter a valid one\n";

                cin >> Number;
            }
        } while (Number < 0);

        return Number;
    };
    int ReadNumberInRange(string Msg, int From, int To)
    {
        int Number;

        do
        {
            cout << Msg << endl;
            cin >> Number;
            while (cin.fail())
            {
                cin.clear();

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid Number, Enter a valid one\n";

                cin >> Number;
            }
        } while (Number < From || Number > To);

        return Number;
    };
    string ReadString(string Msg)
    {
        string String;
        cout << Msg << endl;
        cin >> String;

        return String;
    }
    string ReadLine(string Msg)
    {
        string Line;
        cout << Msg << endl;
        getline(cin, Line);

        return Line;
    }
}