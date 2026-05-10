#pragma once
#include <iostream>

#include "../../clsUtil.h"
#include "../clsBankClient.h"
#include "../clsClientHelper.h"
#include "../clsScreen.h"

class clsDeleteClientScreen : clsScreen {
 public:
  static void DeleteClient() {
    clsClient Client = clsClientHelper::ReadClientByAccountNumber();
    clsClientHelper::PrintClient(Client);

    if (clsUtils::isAccepted("\nDo you want to delete Client? [Y/n] ")) {
      if (Client.Delete()) {
        cout << "\nAccount Delete Successfully :)\n";
      } else {
        cout << "\nFailed to Delete Client :(\n";
      }
      
    }
  };
};