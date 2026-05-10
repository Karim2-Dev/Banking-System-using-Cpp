#pragma once
#include <iostream>

#include "../../clsInputValidate.h"
#include "../../clsUtil.h"
#include "../clsClientHelper.h"
#include "../clsScreen.h"
#include "clsAddUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsUsersListScreen.h"

class clsManageUsersScreen : protected clsScreen {
  enum enManageUsersOptions {
    enShowUsersList = 1,
    enAddNewUser = 2,
    enDeleteUser = 3,
    enUpdateUser = 4,
    enFindUser = 5,
  };

  static void _UsersListScreen() {
    clsUtils::ClearScreen();
    clsUsersListScreen::PrintUserListScreen();
    _BackToBackScreen();
  }
  static void _AddNewUserScreen() {
    clsUtils::ClearScreen();
    clsAddUserScreen::PrintAddNewUserScreen();
    _BackToBackScreen();
  }
  static void _DeleteUserScreen() {
    clsUtils::ClearScreen();
    clsDeleteUserScreen::PrintDeleteUserScreen();
    _BackToBackScreen();
  }
  static void _UpdateUserScreen() {
    clsUtils::ClearScreen();
    clsUpdateUserScreen::PrintUpdateUserScreen();
    _BackToBackScreen();
  }
  static void _FindUserScreen() {
    clsUtils::ClearScreen();
    clsFindUserScreen::PrintFindUserScreen();
    _BackToBackScreen();
  }

  static void _GetManageUsersOption(bool& ShowManageUsersScreen) {
    enManageUsersOptions Page =
      (enManageUsersOptions)clsInputValidate::ReadIntNumber(
        "\nChoose what do you want to do [1,6]");
    switch (Page) {
      case enManageUsersOptions::enShowUsersList: _UsersListScreen(); break;
      case enManageUsersOptions::enAddNewUser: _AddNewUserScreen(); break;
      case enManageUsersOptions::enDeleteUser: _DeleteUserScreen(); break;
      case enManageUsersOptions::enUpdateUser: _UpdateUserScreen(); break;
      case enManageUsersOptions::enFindUser: _FindUserScreen(); break;

      default: ShowManageUsersScreen = false; break;
    }
  }

 public:
  static void PrintManageUserScreen() {
    bool ShowManageUsersScreen = true;

    while (
      ShowManageUsersScreen && clsUser::isUserExist(CurrentUser.Username())) {
      clsUtils::ClearScreen();

      cout << "\n=========================================================\n";
      cout << "\tManage User Menu Screen\n";
      cout << "=========================================================\n";
      cout << "\t[1] List User.\n";
      cout << "\t[2] Add New User.\n";
      cout << "\t[3] Delete User.\n";
      cout << "\t[4] Update User.\n";
      cout << "\t[5] Find User.\n";
      cout << "\t[6] Main Menu.\n";
      cout << "=========================================================\n";
      _GetManageUsersOption(ShowManageUsersScreen);
    }
  }
};