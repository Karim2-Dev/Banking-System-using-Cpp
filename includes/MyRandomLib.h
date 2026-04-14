#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include "MyInputLib.h"

using namespace std;
enum enCharacters
{
    SmallLetter = 1,
    CapitalLetter,
    SpecialCharacter,
    Digit,
};
enum enIsPrimeOrNot
{
    Prime = 1,
    NotPrime
};

enIsPrimeOrNot enCheckIsPrime(int Num)
{
    if (Num <= 1)
    {
        return NotPrime;
    }
    for (int i = 2; i <= round(Num / 2); i++)
    {
        if (Num % i == 0)
        {
            return NotPrime;
        }
    }
    return Prime;
}

namespace MyRand
{
    int RandomNumber(int From, int To)
    {
        return rand() % (To - From + 1) + From;
    }
    char RandomCharacter(enCharacters CharactersType)
    {
        char RandomChar;
        switch (CharactersType)
        {
        case enCharacters::SmallLetter:
            RandomChar = char(RandomNumber(97, 122));
            break;
        case enCharacters::CapitalLetter:
            RandomChar = char(RandomNumber(65, 90));
            break;
        case enCharacters::SpecialCharacter:
            RandomChar = char(RandomNumber(33, 41));
            break;
        case enCharacters::Digit:
            RandomChar = RandomNumber(48, 57);
            break;

        default:
            break;
        }
        return RandomChar;
    }
    string GenerateWord(enCharacters CharType, short Length)
    {
        string word = "";
        for (int i = 1; i <= Length; i++)
        {
            word += RandomCharacter(CharType);
        }
        return word;
    }

    string GenerateKey()
    {
        string Key = GenerateWord(enCharacters::CapitalLetter, 4);

        for (int i = 1; i <= 3; i++)
        {
            Key = Key + '-' + GenerateWord(enCharacters::CapitalLetter, 4);
        }
        return Key;
    }

    void GenerateKey(short NumberOfKeys)
    {
        for (int i = 1; i <= NumberOfKeys; i++)
        {
            cout << "Key [" << i << "] " << GenerateKey() << endl;
        }
    }
}