#pragma once
#include <iostream>

#include "../../clsUtil.h"
#include "../clsBankClient.h"
#include "../clsScreen.h"

class clsTransfareLogScreen : protected clsScreen {
  static void _PrintHeader_TransfareLog() {
    clsUtils::PrintLine(150);
    cout << "\n\n";
    cout << "| " << left << setw(30) << "Date/Time";
    cout << "| " << left << setw(15) << "s.Account";
    cout << "| " << left << setw(15) << "d.Account";
    cout << "| " << left << setw(15) << "Amount";
    cout << "| " << left << setw(20) << "s.Balance";
    cout << "| " << left << setw(20) << "d.Balance";
    cout << "| " << left << setw(20) << "User";
    cout << "\n";
    clsUtils::PrintLine(150);
    cout << "\n";
  }

 public:
  static void PrintRegisterDataScreen() {
    vector<clsClient::stTransfareData> vTransfaresData =
      clsClient::GetTransfareList();

    _PrintHeader_TransfareLog();

    for (clsClient::stTransfareData& TransfareData : vTransfaresData) {
      cout << "\n";
      cout << "| " << left << setw(30) << TransfareData.DateAndTime;
      cout << "| " << left << setw(15) << TransfareData.sAccountNumber;
      cout << "| " << left << setw(15) << TransfareData.dAccountNumber;
      cout << "| " << left << setw(15) << TransfareData.Amount;
      cout << "| " << left << setw(20) << TransfareData.sBalance;
      cout << "| " << left << setw(20) << TransfareData.dBalance;
      cout << "| " << left << setw(20) << TransfareData.Username;
    }
    cout << '\n';
    clsUtils::PrintLine(150);
    cout << '\n';
  }
};