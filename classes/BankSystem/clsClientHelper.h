#pragma once
#include <iostream>

#include "../clsInputValidate.h"
#include "../clsUtil.h"
#include "clsBankClient.h"

using namespace std;

class clsClientHelper {
 public:
  static clsClient ReadClientByAccountNumber(
    string Msg = "\nPlease enter client account Number: ") {
    string AccountNumber = "";
    AccountNumber =
      clsInputValidate::ReadString(Msg);

    // التأكد من وجود العميل
    while (!clsClient::isClientExist(AccountNumber)) {
      AccountNumber = clsInputValidate::ReadString(
        "\nNOT FOUND: Please enter client account Number: ");
    };

    return clsClient::Find(AccountNumber);
  }
  static void ReadClientInfo(clsClient& Client) {
    Client.setFirstName(clsInputValidate::ReadString("\nEnter FirstName: "));
    Client.setLastName(clsInputValidate::ReadString("Enter LastName:"));

    Client.setEmail(clsInputValidate::ReadString("Enter Email:"));
    Client.setPhone(clsInputValidate::ReadString("Enter Phone:"));

    Client.setPinCode(clsInputValidate::ReadString("Enter PinCode:"));
    Client.setAccountBalance(
      clsInputValidate::ReadDblNumber("Enter Account Balance:"));
  }

  static void PrintClient(clsClient Client) {
    cout << endl;
    clsUtils::PrintLine(30);
    cout << "\nClient Card: \n";
    clsUtils::PrintLine(30);
    cout << endl;
    cout << "Account Number  : " << Client.GetAccountNumber() << endl;
    cout << "Name            : " << Client.FullName() << endl;
    cout << "Email           : " << Client.Email() << endl;
    cout << "Phone           : " << Client.Phone() << endl;
    cout << "Pin Code        : " << Client.GetPinCode() << endl;
    cout << "Balanced        : " << Client.GetBalance() << endl;
    clsUtils::PrintLine(30);
  }
};