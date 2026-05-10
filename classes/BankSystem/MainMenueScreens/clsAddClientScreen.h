#pragma once
#include <iostream>

#include "../../clsUtil.h"
#include "../clsBankClient.h"
#include "../clsClientHelper.h"
#include "../clsScreen.h"

class clsAddClientScreen : protected clsScreen {
 public:
  static void AddClient() {
    string AccountNumber =
      clsInputValidate::ReadString("\nPlease enter client account Number: ");

    // ? بشوف هل الكلاينت موجود ولا لا
    while (clsClient::isClientExist(AccountNumber)) {
      AccountNumber = clsInputValidate::ReadString(
        "\nThe Account Number is Already Exist:\n"
        "Please enter client account Number: ");
    };

    cout << "\n\nAdd Client Info: \n";
    cout << "____________________\n";

    clsClient Client = clsClient::AddNewClient(AccountNumber);
    clsClientHelper::ReadClientInfo(Client);

    clsClient::enSaveResults AddResult = Client.save();

    switch (AddResult) {
      case clsClient::enSaveResults::svSucceeded:
        cout << endl;
        clsClientHelper::PrintClient(Client);
        cout << "\nAccount Added Successfully :)\n";
        break;

      case clsClient::enSaveResults::svFailedAccountNumberExists:
        cout << "\nError account was not saved because is Already Exists :(\n";
        break;
    }
  };
};