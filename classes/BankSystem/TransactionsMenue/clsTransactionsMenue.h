#pragma once
#include <iostream>

#include "../../clsInputValidate.h"
#include "../../clsUtil.h"
#include "../clsBankClient.h"
#include "../clsClientHelper.h"
#include "../clsScreen.h"
#include "clsDepositScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransfareLogScreen.h"
#include "clsTransfareScreen.h"
#include "clsWithdrawScreen.h"

class clsTransactionsMenue : clsScreen {
  enum enTransacitonOptions {
    Deposit = 1,
    Withdraw,
    TotalBalances,
    Transfare,
    TransfareLog,
  };

  static void DepositScreen() {
    clsUtils::ClearScreen();
    clsDeposit::PrintDeposit();
    _BackToBackScreen();
  }
  static void WithdrawScreen() {
    clsUtils::ClearScreen();
    clsWithdraw::PrintWithdraw();
    _BackToBackScreen();
  }
  static void TotalBalancesScreen() {
    clsUtils::ClearScreen();
    clsTotalBalancesScreen::PrintTotalBalances();
    _BackToBackScreen();
  }

  static void TransfareScreen() {
    clsUtils::ClearScreen();
    _DrawScreenHeader("Transfare Screen");
    clsTransfareScreen::PrintTransfareScreen();
    _BackToBackScreen();
  }
  static void TransfareLogScreen() {
    clsUtils::ClearScreen();
    clsTransfareLogScreen::PrintRegisterDataScreen();
    _BackToBackScreen();
  }

  static void _GetTransactionOption(bool& TransactionMenueActive) {
    enTransacitonOptions Page =
      (enTransacitonOptions)clsInputValidate::ReadIntNumber(
        "\nChoose what do you want to do [1,6]");
    switch (Page) {
      case enTransacitonOptions::Deposit: DepositScreen(); break;
      case enTransacitonOptions::Withdraw: WithdrawScreen(); break;
      case enTransacitonOptions::TotalBalances: TotalBalancesScreen(); break;
      case enTransacitonOptions::Transfare: TransfareScreen(); break;
      case enTransacitonOptions::TransfareLog: TransfareLogScreen(); break;

      default: TransactionMenueActive = false; return;
    }
  }

 public:
  static void PrintTransactionClient() {
    bool TransactionMenueActive = true;

    do {
      clsUtils::ClearScreen();

      cout << "\n=========================================================\n";
      cout << "\tTransactions Menu Screen\n";
      cout << "=========================================================\n";
      cout << "\t[1] Deposit.\n";
      cout << "\t[2] Withdraw.\n";
      cout << "\t[3] Total Balances.\n";
      cout << "\t[4] Transfare.\n";
      cout << "\t[5] Transfare Log.\n";
      cout << "\t[6] Main Menu.\n";
      cout << "=========================================================\n";
      _GetTransactionOption(TransactionMenueActive);
    } while (
      TransactionMenueActive && clsUser::isUserExist(CurrentUser.Username()));
  }
};