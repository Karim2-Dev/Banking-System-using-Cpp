#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class clsString {
 private:
  string _Value;

  //! Private Function
  static char InvertChar(char Character) {
    return (isupper(Character)) ? tolower(Character) : toupper(Character);
  }
  static bool isVowel(char Character) {
    char lowerChar = tolower(Character);
    return ((lowerChar == 'a') || (lowerChar == 'o') || (lowerChar == 'u') ||
            (lowerChar == 'e') || (lowerChar == 'i'));
  }

 public:
  //? Constractor
  clsString() { _Value = ""; }
  clsString(string Value) { _Value = Value; }
  //? Get
  string Value() { return _Value; }
  //? Set
  void setValue(string Value) { _Value = Value; }

  //! String Functions

  //* ToLowerCase
  static string toLowerCaseEachWord(string Line) {
    for (int i = 0; i < Line.length(); i++) { Line[i] = tolower(Line[i]); }

    return Line;
  }
  void toLowerCaseEachWord() { _Value = toLowerCaseEachWord(_Value); }
  //*==== ToUppercase ==== *//

  //* ToLowerCase
  static string toUpperCaseEachWord(string Line) {
    for (int i = 0; i < Line.length(); i++) { Line[i] = toupper(Line[i]); }

    return Line;
  }
  void toUpperCaseEachWord() { _Value = toUpperCaseEachWord(_Value); }
  //*==== ToUppercase ==== *//

  //* Invert All LettersCase
  static string InvertAllLettersCase(string Line) {
    for (int i = 0; i < Line.length(); i++) { Line[i] = InvertChar(Line[i]); }
    return Line;
  }
  void InvertAllLettersCase() { _Value = InvertAllLettersCase(_Value); }
  //* Invert All LettersCase *//

  //* Count Small LettersCase
  static int CountSmallLetters(string Line) {
    int SmallLettersCounter = 0;
    for (int i = 0; i < Line.length(); i++) {
      if (islower(Line[i])) { SmallLettersCounter++; }
    }
    return SmallLettersCounter;
  }
  int CountSmallLetters() { return CountSmallLetters(_Value); }
  //*==== Count Small LettersCase ==== *//

  //* Count CapitalLetters *//
  static int CountCapitalLetters(string Line) {
    int CapitalLettersCounter = 0;
    for (int i = 0; i < Line.length(); i++) {
      if (isupper(Line[i])) { CapitalLettersCounter++; }
    }
    return CapitalLettersCounter;
  }
  int CountCapitalLetters() { return CountCapitalLetters(_Value); }
  //*==== Count CapitalLetters ==== *//

  //* CountLetters *//
  static int CountLetter(string Line, char Char1, bool MatchCase = true) {
    int CounterLetter = 0;

    for (short i = 0; i < Line.length(); i++) {
      if (MatchCase) {
        if (Line[i] == Char1) { CounterLetter++; }
      } else {
        if (tolower(Line[i]) == tolower(Char1)) { CounterLetter++; }
      }
    }
    return CounterLetter;
  }
  int CountLetter(char Char1, bool MatchCase = true) {
    return CountLetter(_Value, Char1, MatchCase);
  }
  //*==== Count Letters ==== *//

  //* Count Vowels *//
  static int countVowels(string Line) {
    int counter = 0;
    for (int i = 0; i < Line.length(); i++) {
      if (isVowel(Line[i])) { counter++; }
    }
    return counter;
  }
  int countVowels() { return countVowels(_Value); }
  //*==== Count Vowels ==== *//

  //* Split *//
  static vector<string> split(string Line, string delim) {
    vector<string> vMySplit;
    short Position;
    string sWord;

    while ((Position = Line.find(delim)) != string::npos) {
      sWord = Line.substr(0, Position);

      if (!sWord.empty()) { vMySplit.push_back(sWord); }

      Line.erase(0, Position + delim.length());
    }
    if (Line != "") { vMySplit.push_back(Line); }

    return vMySplit;
  }  //*==== Split ==== *//

  //* Join *//
  static string JoinString(
    vector<string> vArrString, string seperator = "#//#") {
    string MyString = "";

    for (string& S1 : vArrString) { MyString += S1 + seperator; }

    return MyString.substr(0, MyString.length() - seperator.length());
  }
  //*==== Join ==== *//

  //* Tims *//
  static string trimLeft(string Line) {
    string delim = " ";

    int Position;

    if ((Position = Line.find_first_not_of(delim)) != string::npos) {
      Line.erase(0, Position);
    } else {
      Line.clear();
    }
    return Line;
  }
  string trimLeft() { return trimLeft(_Value); }

  static string trimRight(string Line) {
    string delim = " ";

    int Position;

    if ((Position = Line.find_last_not_of(delim)) != string::npos) {
      Line.erase(Position + 1);
    } else {
      Line.clear();
    }

    return Line;
  }
  string trimRight() { return trimRight(_Value); }

  static string trim(string Line) { return trimRight(trimLeft(Line)); }
  string trim() { return trim(_Value); }
  //*==== Trims ==== *//

  //* Count Words *//
  static short CountWords(string Line) {
    short Counter = 0;
    short Position;
    string delim = " ";
    string sWord;

    while ((Position = Line.find(delim)) != string::npos) {
      sWord = Line.substr(0, Position);

      if (sWord != "") { Counter++; }

      Line.erase(0, Position + delim.length());
    }
    if (Line.length() != 0) { Counter++; }

    return Counter;
  }
  short CountWords() { return CountWords(_Value); }
  //*==== Count Words ==== *//

  //* Reverse Words *//
  static string ReverseWords(string Line) {
    vector<string> vSplitString = split(Line, " ");
    string ReversedString = "";

    vector<string>::iterator iter = vSplitString.end() - 1;

    while (iter >= vSplitString.begin()) {
      ReversedString += (iter > vSplitString.begin()) ? *iter + " " : *iter;
      --iter;
    }
    return ReversedString;
  }
  string ReverseWords() { return ReverseWords(_Value); }
  //*==== Reverse Words ==== *//

  //* replace Words *//
  static string replace(
    string Line, string Word, string ReplaceTo, bool IsSense = true) {
    vector<string> vSplit = split(Line, " ");
    vector<string>::iterator iter = vSplit.begin();

    while (iter < vSplit.end()) {
      if (IsSense) {
        if (*iter == Word) { *iter = ReplaceTo; }
      } else {
        if (toLowerCaseEachWord(*iter) == toLowerCaseEachWord(Word)) {
          *iter = ReplaceTo;
        }
      }

      iter++;
    }
    return JoinString(vSplit, " ");
  }
  string replace(string Word, string ReplaceTo, bool IsSense = true) {
    return replace(_Value, Word, ReplaceTo, IsSense);
  }
  //*==== Replace Words ==== *//
  //* Remove Punctuation Words *//
  static string RemovePunctuationInString(string Line) {
    for (int i = 0; i < Line.length(); i++) {
      if (ispunct(Line[i])) {
        Line.erase(i, 1);
        i--;
      }
    }
    return Line;
  }
  string RemovePunctuationInString() {
    return RemovePunctuationInString(_Value);
  }
  //*==== Remove Punctuation Words ====*//
  //* Encrypt And Dectypt Function *//
  static string EncryptText(string Text, short Key) {
    for (int i = 0; i < Text.length(); i++) {
      Text[i] = char((int)Text[i] + Key);
    }
    return Text;
  }

  string EncryptText(short Key) { return EncryptText(_Value, Key); }
 
  static string DecryptText(string Text, short Key) {
    for (int i = 0; i < Text.length(); i++) {
      Text[i] = char((int)Text[i] - Key);
    }
    return Text;
  }

  string DecryptText(short Key) { return DecryptText(_Value, Key); }
  //*==== Encrypt And Dectypt Function ====*//
};