#pragma once

#include <iostream>

#include "../../clsInputValidate.h"
#include "../clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrenciesListScreen : protected clsScreen {
  static void _PrintHeader_Currencies() {
    clsUtils::PrintLine(150);
    cout << "\n\n";
    cout << "| " << left << setw(50) << "Country";
    cout << "| " << left << setw(10) << "Code";
    cout << "| " << left << setw(60) << "Name";
    cout << "| " << left << setw(15) << "Rate(1$)";
    cout << "\n";
    clsUtils::PrintLine(150);
    cout << "\n";
  }

 public:
  static void PrintCurrenciesListScreen() {
    vector<clsCurrency> Currencies = clsCurrency::GetCurrenciesData();

    _PrintHeader_Currencies();

    for (clsCurrency& Currency : Currencies) {
      cout << "\n";
      cout << "| " << left << setw(50) << Currency.country();
      cout << "| " << left << setw(10) << Currency.code();
      cout << "| " << left << setw(60) << Currency.name();
      cout << "| " << left << setw(15) << Currency.rate();
    }
    cout << '\n';
    clsUtils::PrintLine(150);
    cout << '\n';
  }
};