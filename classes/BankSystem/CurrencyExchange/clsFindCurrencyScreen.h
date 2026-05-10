#pragma once

#include <iostream>

#include "../../clsInputValidate.h"
#include "../clsScreen.h"
#include "clsCurrency.h"
#include "clsCurrencyHelper.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen {
  enum _FindMode {
    Code = 1,
    Country,
  };

 public:
  static void PrintFindCurrencyScreen() {
    int Mode = clsInputValidate::ReadNumberBetween(
      "Find By: [1] Code or [2] Country? ", "Invalid Number", 1, 2);

    clsCurrency Currency = clsCurrency::GetEmptyCurrency();

    if (Mode == Code) {
      string Code =
        clsInputValidate::ReadString("Please Enter Currency Code? ");

      Currency = clsCurrencyHelper::GetCurrencyByCode();
    } else {
      Currency = clsCurrencyHelper::GetCurrencyByCountry();
    }

    if (Currency.isCurrencyExist()) {
      clsCurrencyHelper::PrintCurrencyCard(Currency);
    } else {
      cout << "Currency Not Found  try Again :( \n";
    }
  }
};