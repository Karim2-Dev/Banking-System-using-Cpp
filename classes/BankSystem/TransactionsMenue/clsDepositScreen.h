
#include "../../clsUtil.h"
#include "../clsBankClient.h"
#include "../clsClientHelper.h"
#include "../clsScreen.h"

class clsDeposit : clsScreen {
 public:
  static void PrintDeposit() {
    _DrawScreenHeader("Deposit Screen");

    clsClient Client = clsClientHelper::ReadClientByAccountNumber();
    clsClientHelper::PrintClient(Client);

    double Amount = clsInputValidate::ReadDblNumber(
      "\nPlease Enter Deposit amount Transaction");

    if (clsUtils::isAccepted(
          "\n\nAre you sure you want perform this transaction? y/n ?")) {
      Client.Deposit(Amount);
      cout << "\nAmount Deposited Successfully.\n";
      cout << "\nNew Balance Is: " << Client.GetBalance();
    } else {
      cout << "\nOperation was canceled\n";
    }
  }
};