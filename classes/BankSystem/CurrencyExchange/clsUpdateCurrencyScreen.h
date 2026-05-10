#pragma once

#include <iostream>

#include "../../clsInputValidate.h"
#include "../clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsCurrencyHelper.h"
#include "clsFindCurrencyScreen.h"

class clsUpdateCurrencyScreen : clsScreen {
 public:
  static void PrintUpdateCurrencyScreen() {
    string Code = clsInputValidate::ReadString("Please Enter Currency Code: ");
    clsCurrency Currency = clsCurrency::FindByCode(Code);
    if (Currency.isCurrencyExist()) {
      cout << '\n';
      clsCurrencyHelper::PrintCurrencyCard(Currency);

      if (clsUtils::isAccepted(
            "Are you sure you wnat to update the rate of this Currency Y/n ")) {
        cout << "\n\nUpdate Currency Rate:\n";
        clsUtils::PrintLine(50);
        Currency.setRate(clsInputValidate::ReadDoubleNum("\nEnter New Rate: "));

        if (Currency.save() == clsCurrency::enSaveResults::svSucceeded) {
          cout << "\nCurrency Rate Updated Successfully :)\n";
          clsCurrencyHelper::PrintCurrencyCard(Currency);
        } else {
          cout << "\nCurrency Rate Update Failed :(\n";
        };
      };

    } else {
      cout << "Currency NOT FOUND: Please try again :(\n";
    }
  }
};