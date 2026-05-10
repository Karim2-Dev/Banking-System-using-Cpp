#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "clsInputValidate.h"

using namespace std;

class clsUtils {
 public:
  enum enCharacters {
    SmallLetter = 1,
    CapitalLetter,
    SpecialCharacter,
    Digit,
  };

  static void Srand() { srand(time(0)); }

  static int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
  }

  static char RandomCharacter(enCharacters CharactersType) {
    char RandomChar;
    switch (CharactersType) {
      case enCharacters::SmallLetter:
        RandomChar = char(RandomNumber(97, 122));
        break;
      case enCharacters::CapitalLetter:
        RandomChar = char(RandomNumber(65, 90));
        break;
      case enCharacters::SpecialCharacter:
        RandomChar = char(RandomNumber(33, 41));
        break;
      case enCharacters::Digit: RandomChar = RandomNumber(48, 57); break;

      default: break;
    }
    return RandomChar;
  }

  static string GenerateWord(enCharacters CharType, short Length) {
    string word = "";
    for (int i = 1; i <= Length; i++) { word += RandomCharacter(CharType); }
    return word;
  }

  static string GenerateKey(clsUtils::enCharacters charType) {
    string Key = GenerateWord(charType, 4);

    for (int i = 1; i <= 3; i++) {
      Key = Key + '-' + GenerateWord(enCharacters::CapitalLetter, 4);
    }
    return Key;
  }

  static void GenerateKeys(
    short NumberOfKeys, clsUtils::enCharacters charType) {
    for (int i = 1; i <= NumberOfKeys; i++) {
      cout << "Key [" << i << "] " << GenerateKey(charType) << endl;
    }
  }

  template <typename Type>

  static void Swap(Type& variable1, Type& variable2) {
    Type Temp = variable1;

    variable1 = variable2;
    variable2 = Temp;
  }

  static string Tabs(short NumberOfTabs) {
    string t = "";

    for (int i = 1; i < NumberOfTabs; i++) { t += "\t"; }
    return t;
  }

  static void FillArrayWithRandomNums(
    int Arr[], int& Length, int from, int to) {
    Length = clsInputValidate::ReadPositiveNumber(
      "Please Enter How Many Numbers You need To Store In Array [1,100]");

    for (int i = 0; i < Length; i++) { Arr[i] = RandomNumber(from, to); }
  }

  template <typename Type>

  static void ShuffleVector(vector<Type>& v) {
    for (int i = v.size() - 1; i > 0; i--) {
      int j = rand() % (i + 1);
      Swap(v[i], v[j]);
    }
  }

  static void FillArrayWithRandomWords(
    string Arr[], int& Length, short WordLength, enCharacters CharType) {
    Length =
      clsInputValidate::ReadPositiveNumber("Enter number of words [1 - 100]: ");

    for (int i = 0; i < Length; i++) {
      Arr[i] = GenerateWord(CharType, WordLength);
    }
  }

  static void FillArrayWithRandomKeys(
    string Arr[], int& Length, enCharacters CharType) {
    Length =
      clsInputValidate::ReadPositiveNumber("Enter number of keys [1 - 100]: ");

    for (int i = 0; i < Length; i++) { Arr[i] = GenerateKey(CharType); }
  }

  //? نزوّد كل حرف بـ shift معين (مثلاً +2)
  static string EncryptText(string Text, short Key) {
    string EncryptedText = "";

    for (int i = 0; i < Text.length(); i++) {
      EncryptedText += char(int(Text[i]) + Key);
    }

    return EncryptedText;
  }
  //? نرجّع نفس الـ shift بالعكس (-Key)
  static string DecryptText(string Text, short Key) {
    string DecryptedText = "";

    for (int i = 0; i < Text.length(); i++) {
      DecryptedText += char(int(Text[i]) - Key);
    }

    return DecryptedText;
  }

  static string NumberToText(int Number) {
    if (Number == 0) { return ""; }

    if (Number >= 1 && Number <= 19) {
      string arr[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
        "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

      return arr[Number] + " ";
    }

    if (Number >= 20 && Number <= 99) {
      string arr[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty",
        "Seventy", "Eighty", "Ninety"};
      return arr[Number / 10] + " " + NumberToText(Number % 10);
    }

    if (Number >= 100 && Number <= 199) {
      return "One Hundred " + NumberToText(Number % 100);
    }
    if (Number >= 200 && Number <= 999) {
      return NumberToText(Number / 100) + "Hundreds " +
             NumberToText(Number % 100);
    }

    if (Number >= 1000 && Number <= 1999) {
      return "One Thousand " + NumberToText(Number % 1000);
    }

    if (Number >= 2000 && Number <= 999999) {
      return NumberToText(Number / 1000) + "Thousands " +
             NumberToText(Number % 1000);
    }

    if (Number >= 1000000 && Number <= 1999999) {
      return "One Million " + NumberToText(Number % 1000000);
    }

    if (Number >= 2000000 && Number <= 999999999) {
      return NumberToText(Number / 1000000) + "Millions " +
             NumberToText(Number % 1000000);
    }
    if (Number >= 1000000000 && Number <= 1999999999) {
      return "One Billion " + NumberToText(Number % 1000000000);
    } else {
      return NumberToText(Number / 1000000000) + "Billions " +
             NumberToText(Number % 1000000000);
    }
  }

  static void PrintLine(int count) {
    for (int i = 1; i <= count; i++) { cout << '_'; }
  }

  static bool isAccepted(string Question) {
    char Answer;
    cout << Question;
    cin >> Answer;

    return tolower(Answer) == 'y';
  }
  static void ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
  }
};