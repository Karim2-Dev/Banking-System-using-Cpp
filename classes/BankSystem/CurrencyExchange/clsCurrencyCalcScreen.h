

#pragma once

#include <iostream>

#include "../../clsInputValidate.h"
#include "../clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsCurrencyHelper.h"
#include "clsFindCurrencyScreen.h"

class clsCurrencyCalcScreen : clsScreen {
 public:
  static void PrintCurrencyCalcScreen() {
    clsCurrency CurrencyFromExchange =
      clsCurrencyHelper::GetCurrencyByCode("Please Enter Currency 1 Code");
    clsCurrency CurrencyToExchange =
      clsCurrencyHelper::GetCurrencyByCode("Please Enter Currency 2 Code");

    float ExchangeAmount =
      clsInputValidate::ReadDblNumber("Enter Amount To Exchange");
    clsCurrencyHelper::PrintCurrencyCard(CurrencyFromExchange);

    cout << ExchangeAmount << " " << CurrencyFromExchange.code() << " = "
         << CurrencyFromExchange.ConvertToOtherCurrency(
              ExchangeAmount, CurrencyToExchange)
         << CurrencyToExchange.code();
  };
};