#pragma once
#include <iostream>

#include "../../clsInputValidate.h"
#include "../../clsUtil.h"
#include "../clsScreen.h"
#include "clsBankUser.h"
#include "clsUserHelper.h"

class clsUpdateUserScreen : clsScreen {
 public:
  static void PrintUpdateUserScreen() {
    _DrawScreenHeader("Update User Screen");

    clsUser User = clsUserHelper::ReadUserByUsername();

    clsUserHelper::PrintUser(User);

    if (clsUtils::isAccepted(
          "\nAre you sure do you want to Update User [Y/n] ? ")) {


      clsUserHelper::UpdateUserInfo(User);
      
      if (User.save() == clsUser::enSaveResults::svSucceeded) {
        cout << "User Updated Successfully :)\n";
      } else {
        cout << "Updated Opreation Failed Please try Again :(\n";
      }
    }
  };
};