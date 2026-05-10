#pragma once

#include <iostream>

#include "../../clsUtil.h"
#include "../Global.h"
#include "../ManageUsers/clsBankUser.h"
#include "../clsMainScreen.h"
#include "../clsScreen.h"

static bool _Login() {
  bool isLoginFailed = false;
  string Password = "";
  string Username = "";

  short counter = 3;
  do {
    if (isLoginFailed) {
      counter--;
      cout << "\nInvalid Username/Password, please try again:\n";
      cout << "you have " << counter << " Trails to login\n\n";

      if (!counter) {
        cout << "\nYou are Locked after " << counter << " failed trails\n\n";
        return false;
      }
    };

    cout << "Enter Username: ";
    cin >> Username;
    cout << "Enter Password: ";
    cin >> Password;

    CurrentUser = clsUser::Find(Username, Password);

    isLoginFailed = CurrentUser.IsEmpty();

  } while (isLoginFailed);

  return true;
};

class clsLoginScreen : public clsScreen {
 public:
  static bool LoginScreen() {
    ClearScreen();
    _DrawScreenHeader("Login Screen");

    if (_Login()) {
      CurrentUser.saveRegisterData();
      clsMainScreen::ShowMainMenue();
      return true;
    }
    return false;
  }
};