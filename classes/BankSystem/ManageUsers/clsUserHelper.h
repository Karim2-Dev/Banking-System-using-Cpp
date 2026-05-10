

#pragma once
#include <iostream>

#include "../../clsInputValidate.h"
#include "../../clsUtil.h"
#include "clsBankUser.h"

class clsUserHelper {
  static string _ReadUserName() {
    string Username = clsInputValidate::ReadString("Please enter Username? ");

    while (clsUser::isUserExist(Username)) {
      Username = clsInputValidate::ReadString(
        "Username is Already Exist please try Again?");
    }
    return Username;
  }

 public:
  static void ReadUserInfo(clsUser& User) {
    User.setFirstName(
      clsInputValidate::ReadString("\nPlease Enter First Name?"));
    User.setLastName(clsInputValidate::ReadString("\nPlease Enter Last Name?"));

    User.setEmail(clsInputValidate::ReadString("\nPlease Enter Email?"));
    User.setPhone(clsInputValidate::ReadString("\nPlease Enter Phone?"));

    User.setPassword(clsInputValidate::ReadString("\nPlease Enter Password?"));
    User.setPermissions(ReadPermission());
  }

  static clsUser ReadNewUser() {
    clsUser User = clsUser::NewUser();
    User.setUsername(_ReadUserName());
    ReadUserInfo(User);
    return User;
  };

  static clsUser ReadUserByUsername() {
    string Username = clsInputValidate::ReadString("\nPlease Enter Username?");

    while (!clsUser::isUserExist(Username)) {
      Username = clsInputValidate::ReadString(
        "\nUser NOT FOUNT? Please Enter Username?");
    }

    return clsUser::Find(Username);
  }

  static short ReadPermission() {
    char IsUserFullAcces;
    cout << "\nDo you want to give full access? y/n ";
    cin >> IsUserFullAcces;

    if (tolower(IsUserFullAcces) == 'y') { return -1; }

    // Else
    char IsAccess = 'n';
    short flags = 0;
    cout << "\nDo you want to give access to:\n";

    cout << "\nShow Client List? y/n ";
    cin >> IsAccess;

    if (tolower(IsAccess) == 'y') {
      flags |= clsUser::enPermission::enClientListAccess;
    }

    cout << "\nAdd New Client? y/n ";

    cin >> IsAccess;

    if (tolower(IsAccess) == 'y') {
      flags |= clsUser::enPermission::enAddNewClientAccess;
    }

    cout << "\nDelete Client? y/n ";
    cin >> IsAccess;

    if (tolower(IsAccess) == 'y') {
      flags |= clsUser::enPermission::enDeleteClientAccess;
    }

    cout << "\nUpdate Client? y/n ";
    cin >> IsAccess;

    if (tolower(IsAccess) == 'y') {
      flags |= clsUser::enPermission::enUpdateClientAccess;
    }

    cout << "\nFind Client? y/n ";
    cin >> IsAccess;

    if (tolower(IsAccess) == 'y') {
      flags |= clsUser::enPermission::enFindClientAccess;
    }

    cout << "\nTransactions? y/n ";
    cin >> IsAccess;

    if (tolower(IsAccess) == 'y') {
      flags |= clsUser::enPermission::enTransactionsAccess;
    }

    cout << "\nManage Users? y/n ";
    cin >> IsAccess;
    if (tolower(IsAccess) == 'y') {
      flags |= clsUser::enPermission::enManageUsersAccess;
    }

    cout << "\nLogin Register List Screen? y/n ";
    cin >> IsAccess;

    if (tolower(IsAccess) == 'y') {
      flags |= clsUser::enPermission::enLoginRegisterAccess;
    }

    if (flags == 255) { flags = -1; }

    return flags;
  };

  static void PrintUser(clsUser& User) {
    cout << endl;
    clsUtils::PrintLine(30);
    cout << "\nClient Card: \n";
    clsUtils::PrintLine(30);
    cout << endl;
    cout << "Username      : " << User.Username() << endl;
    cout << "First Name    : " << User.FirstName() << endl;
    cout << "Last Name     : " << User.LastName() << endl;
    cout << "Email         : " << User.Email() << endl;
    cout << "Phone         : " << User.Phone() << endl;
    cout << "Password      : " << User.Password() << endl;
    cout << "Permissions   : " << User.Permissions() << endl;
    clsUtils::PrintLine(30);
  }
  static void UpdateUserInfo(clsUser& User) { ReadUserInfo(User); }
};