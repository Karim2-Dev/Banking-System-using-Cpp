#pragma once
#include <iostream>
#include <limits>

#include "./clsDate.h"

using namespace std;

class clsInputValidate {
  static void ClearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

 public:
  //* Read Number *//
  static double ReadDblNumber(string Msg, string errMsg = "Invalid Number") {
    double Number;
    cout << Msg << endl;
    cin >> Number;

    while (cin.fail()) {
      ClearInput();
      cout << errMsg << endl;

      cin >> Number;
    }
    return Number;
  }

  static int ReadIntNumber(string Msg, string errMsg = "Invalid Number") {
    int Number;
    return Number = (int)ReadDblNumber(Msg, errMsg);
  };

  static int ReadNumberBetween(
    string Msg, string errMsg = "Invalid Number", int from = 1, int to = 10) {
    int Number;

    do {
      Number = ReadIntNumber(Msg, errMsg);
      if (!IsNumberBetween(Number, from, to)) { cout << errMsg << endl; };
    } while (!IsNumberBetween(Number, from, to));

    return Number;
  }

  static double ReadDoubleNum(string Msg) {
    double Number;
    cout << Msg << endl;
    cin >> Number;

    while (cin.fail()) {
      ClearInput();
      cout << "Invalid Number, Enter a valid one\n";

      cin >> Number;
    }
    return Number;
  }

  static int ReadPositiveNumber(string Msg) {
    int Number;

    do {
      cout << Msg << " ";
      cin >> Number;
      while (cin.fail()) {
        ClearInput();
        cout << "Invalid Number, Enter a valid one\n";

        cin >> Number;
      }
    } while (Number < 0);

    return Number;
  };

  static string ReadString(string Msg) {
    string Line;

    cout << Msg << endl;
    getline(cin >> ws, Line);

    return Line;
  }

  //*==== Read Number ====*//

  //* Is Number Between *//
  static bool IsNumberBetween(double number, double from, double to) {
    return (number >= from && number <= to);
  }

  static bool IsNumberBetween(int number, int from, int to) {
    return IsNumberBetween((double)number, (double)from, (double)to);
  }
  static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo) {
    return clsDate::IsDate1AfterDate2(Date, DateFrom) &&
           clsDate::IsDate1BeforeDate2(Date, DateTo);
  }
  //*==== Is Number Between ====*//

  //* Validation *//
  static bool IsValidDate(const clsDate& Date) {
    return clsDate::IsDateValid(Date);
  }
  //*==== Validation ====*//
};