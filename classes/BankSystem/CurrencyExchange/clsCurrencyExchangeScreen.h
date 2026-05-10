#pragma once

#include <iostream>

#include "../../clsInputValidate.h"
#include "../clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsCurrencyCalcScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen {
  enum _CurrencyExchangeMenue {
    ListCurrencies = 1,
    FindCurrecy,
    UpdateRate,
    CurrencyCalculator,
    MainMenue,
  };

  static void _ListCurrenciesScreen() {
    ClearScreen();
    clsCurrenciesListScreen::PrintCurrenciesListScreen();
    _BackToBackScreen();
  };
  static void _FindCurrencyScreen() {
    ClearScreen();
    _DrawScreenHeader("Find Currency Screen");
    clsFindCurrencyScreen::PrintFindCurrencyScreen();
    _BackToBackScreen();
  };
  static void _UpdateRateScreen() {
    ClearScreen();
    _DrawScreenHeader("Update Currency Screen");
    clsUpdateCurrencyScreen::PrintUpdateCurrencyScreen();
    _BackToBackScreen();
  };
  static void _CurrencyCalculatorScreen() {
    ClearScreen();
    _DrawScreenHeader("Currency Calculator Screen");
    clsCurrencyCalcScreen::PrintCurrencyCalcScreen();
    _BackToBackScreen();
  };

  static void _GetCurrencyExchangeOption(bool& isCurrencyExchangeActive) {
    _CurrencyExchangeMenue Page =
      (_CurrencyExchangeMenue)clsInputValidate::ReadIntNumber(
        "\nChoose what do you want to do [1,5]");

    switch (Page) {
      case _CurrencyExchangeMenue::ListCurrencies:
        _ListCurrenciesScreen();
        break;
      case _CurrencyExchangeMenue::FindCurrecy: _FindCurrencyScreen(); break;
      case _CurrencyExchangeMenue::UpdateRate: _UpdateRateScreen(); break;
      case _CurrencyExchangeMenue::CurrencyCalculator:
        _CurrencyCalculatorScreen();
        break;
      default: isCurrencyExchangeActive = false; break;
    };
  }

 public:
  static void PrintCurrencyExchangeScreen() {
    bool isCurrencyExchangeActive = true;
    do {
      cout << "\n=========================================================\n";
      cout << "\tCurrncy Exchange Menu Screen\n";
      cout << "=========================================================\n";
      cout << "\t[1] List Currencies.\n";
      cout << "\t[2] Find Currency.\n";
      cout << "\t[3] Update Currency.\n";
      cout << "\t[4] Currency Calculator.\n";
      cout << "\t[5] Main Menue.\n";
      cout << "=========================================================\n";
      _GetCurrencyExchangeOption(isCurrencyExchangeActive);
    } while (isCurrencyExchangeActive);
  }
};