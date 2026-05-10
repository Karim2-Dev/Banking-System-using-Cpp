#pragma once
#include <iostream>

#include "../../clsInputValidate.h"
#include "../../clsUtil.h"
#include "../clsClientHelper.h"
#include "../clsScreen.h"
#include "clsBankUser.h"

class clsUsersListScreen : clsScreen {
  static void _PrintUsersHeaderList(vector<clsUser> UsersData) {
    cout << clsUtils::Tabs(9) << "UsersList (" << UsersData.size()
         << ") stUser(s)\n";
    clsUtils::PrintLine(150);
    cout << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(30) << "Name";
    cout << "| " << left << setw(35) << "Email";
    cout << "| " << left << setw(20) << "Phone";
    cout << "| " << left << setw(20) << "Password";
    cout << "| " << left << setw(10) << "Permissions";
    cout << '\n';
    clsUtils::PrintLine(150);
    cout << endl;
  }

  static void _PrintUserListScreen() {
    vector<clsUser> Users = clsUser::GetUsersList();
    _PrintUsersHeaderList(Users);
    for (clsUser& User : Users) {
      cout << "| " << left << setw(15) << User.Username();
      cout << "| " << left << setw(30) << User.FullName();
      cout << "| " << left << setw(35) << User.Email();
      cout << "| " << left << setw(20) << User.Phone();
      cout << "| " << left << setw(20) << User.Password();
      cout << "| " << left << setw(10) << User.Permissions() << endl;
    }
    clsUtils::PrintLine(150);
    cout << endl;
  }

 public:
  static void PrintUserListScreen() { _PrintUserListScreen(); }
};