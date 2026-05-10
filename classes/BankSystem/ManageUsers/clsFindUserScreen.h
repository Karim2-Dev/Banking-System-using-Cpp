#pragma once
#include <iostream>

#include "../../clsInputValidate.h"
#include "../../clsUtil.h"
#include "../clsScreen.h"
#include "clsBankUser.h"
#include "clsUserHelper.h"

class clsFindUserScreen : clsScreen {
 public:
  static void PrintFindUserScreen() {
    _DrawScreenHeader("Find User");

    clsUser User = clsUserHelper::ReadUserByUsername();
    clsUserHelper::PrintUser(User);
  }
};