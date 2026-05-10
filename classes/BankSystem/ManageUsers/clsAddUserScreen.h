#pragma once
#include <iostream>

#include "../../clsInputValidate.h"
#include "../../clsUtil.h"
#include "../clsScreen.h"
#include "clsBankUser.h"
#include "clsUserHelper.h"

class clsAddUserScreen : clsScreen {
 public:
  static void PrintAddNewUserScreen() {
    clsUtils::ClearScreen();
    _DrawScreenHeader("Add New User Screen");

    clsUser User = clsUserHelper::ReadNewUser();

    if (User.save()) {
      cout << "User Added Successfully :)" << endl;
    } else {
      cout << "the Opreation failed please try again :(\n";
    }
  }
};