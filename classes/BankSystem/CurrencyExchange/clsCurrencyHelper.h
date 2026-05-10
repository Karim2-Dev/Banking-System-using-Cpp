#pragma once

#include <iostream>

#include "../../clsInputValidate.h"
#include "../../clsUtil.h"
#include "../clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrencyHelper {
 public:
  static void PrintCurrencyCard(clsCurrency& Currency) {
    cout << '\n';
    clsUtils::PrintLine(50);
    cout << '\n';

    cout << "Currency Card\n";
    clsUtils::PrintLine(50);

    cout << "\n\nCountry : " << Currency.country() << "\n";
    cout << "Code    : " << Currency.code() << "\n";
    cout << "Name    : " << Currency.name() << "\n";
    cout << "Rate(1$): " << Currency.rate() << "\n";

    clsUtils::PrintLine(50);
    cout << endl;
  }

  static clsCurrency GetCurrencyByCode(
    string Msg = "Please Enter Currency Code?",
    string errMsg = "NOT FOUND: Please Enter Currency Code") {
    string Code = clsInputValidate::ReadString(Msg);
    clsCurrency Currency = clsCurrency::FindByCode(Code);

    while (Currency.isEmptyCurrency()) {
      string errMsg = "NOT FOUND: " + Msg;
      Code = clsInputValidate::ReadString(errMsg);
      Currency.FindByCode(Code);
    }

    return Currency;
  }
  static clsCurrency GetCurrencyByCountry(
    string Msg = "Please Enter Country Name? ",
    string errMsg = "NOT FOUND: Please Enter Country Name ") {
    string Country = clsInputValidate::ReadString(Msg);
    clsCurrency Currency = clsCurrency::FindByCode(Country);

    while (Currency.isEmptyCurrency()) {
      Country =
        clsInputValidate::ReadString(errMsg);
      Currency.FindByCountry(Country);
    }
    cout << "Currency Found  :) \n";

    return Currency;
  }
};