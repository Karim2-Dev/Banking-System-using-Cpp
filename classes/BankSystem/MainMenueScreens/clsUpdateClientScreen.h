

#pragma once
#include <iostream>

#include "../../clsUtil.h"
#include "../clsBankClient.h"
#include "../clsClientHelper.h"
#include "../clsScreen.h"

class clsUpdateClientScreen : clsScreen {
 public:
  static void updateClient() {
    clsClient Client = clsClientHelper::ReadClientByAccountNumber();

    cout << "\n\nUpdate Client Info: \n";
    cout << "____________________\n";
    clsClientHelper::ReadClientInfo(Client);

    //* Save Client
    clsClient::enSaveResults SaveReault;
    SaveReault = Client.save();

    switch (SaveReault) {
      case clsClient::enSaveResults::svSucceeded:
        cout << "\nAccount Updated Successfully :)\n";
        clsClientHelper::PrintClient(Client);
        break;

      case clsClient::enSaveResults::svFailedEmptyObject:
        cout << "\nError account was not saved because it's Empty :)\n";
        break;
    }
  }
};