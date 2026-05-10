#pragma once
#include <iostream>

#include "../../clsInputValidate.h"
#include "../../clsUtil.h"
#include "../Global.h"
#include "../clsScreen.h"
#include "clsBankUser.h"
#include "clsUserHelper.h"
class clsDeleteUserScreen : clsScreen {
 public:
  static void PrintDeleteUserScreen() {
    _DrawScreenHeader("Delete User Screen");

    clsUser User = clsUserHelper::ReadUserByUsername();

    if (clsUtils::isAccepted(
          "Are you sure do you want to delete User [Y/n] ? ")) {
      if (User.Delete()) {
        cout << "User Deleted Successfully :)\n";
        CurrentUser = clsUser::Find(CurrentUser.Username());
      } else {
        cout << "Delete Opreation Failed Please try Again :(\n";
      }
    }
  };
};