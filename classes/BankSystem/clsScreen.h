#pragma once
#include <iostream>

#include "../clsDate.h"
#include "../clsInputValidate.h"
#include "../clsUtil.h"
#include "Global.h"
#include "clsBankClient.h"

using namespace std;

class clsScreen {
 protected:
  static void _PrintCurrentUser() {
    cout << "User: " << CurrentUser.Username() << endl;
  }
  static void _PrintCurrentDate() {
    cout << "Date: " << clsDate::FormatDate(clsDate::GetCurrentDate()) << endl;
  }

  static void _DrawScreenHeader(string Msg) {
    cout << "------------------------------------------------\n";
    cout << "\t\t  " << Msg << "\n";
    cout << "------------------------------------------------\n\n";
    _PrintCurrentUser();
    _PrintCurrentDate();
    cout << endl;
  }

  static void _PauseScreen() {
    cout << "\n\nPress any key to continue...\n";

#ifdef _WIN32
    system("pause>0");
#else
    system("read -n 1 -s");
#endif
  }
  static void _BackToBackScreen() {
    _PauseScreen();
    clsUtils::ClearScreen();
  }

  static void _PrintComingSoonScreen(string PageName) {
    clsUtils::ClearScreen();
    cout << PageName << " Screen will be here\n";
    cout << "Coming Soon...\n";
  }
  static void ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
  }

  static void PrintAccessDeniedScreen() {
    ClearScreen();

    cout << "------------------------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You dont Have Permission To Do this,\n";
    cout << "Please Concat Your Admin,\n";
    cout << "------------------------------------------------\n";
  };
};