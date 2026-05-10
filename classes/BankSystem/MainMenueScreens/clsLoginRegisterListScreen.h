#pragma once
#include <iostream>

#include "../../clsUtil.h"
#include "../ManageUsers/clsBankUser.h"
#include "../clsScreen.h"

class clsLoginRegisterListScreen : protected clsScreen {
  static void _PrintHeader_LoginRegisterList() {
    clsUtils::PrintLine(150);
    cout << "\n\n";
    cout << "| " << left << setw(45) << "Date/Time";
    cout << "| " << left << setw(30) << "UserName";
    cout << "| " << left << setw(30) << "Password";
    cout << "| " << left << setw(30) << "Permissions";
    cout << "\n";
    clsUtils::PrintLine(150);
    cout << "\n";
  }

 public:
  static void PrintRegisterDataScreen() {
    vector<vector<string>> clsRegisers = clsUser::GetRegiserList();

    _PrintHeader_LoginRegisterList();

    for (vector<string>& Register : clsRegisers) {
      cout << "\n";
      cout << "| " << left << setw(45) << Register[0];
      cout << "| " << left << setw(30) << Register[1];
      cout << "| " << left << setw(30) << Register[2];
      cout << "| " << left << setw(30) << Register[3];
    }
    cout << '\n';
    clsUtils::PrintLine(150);
    cout << '\n';
  }
};