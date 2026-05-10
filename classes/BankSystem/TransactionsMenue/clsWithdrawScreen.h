
#include "../../clsUtil.h"
#include "../clsBankClient.h"
#include "../clsClientHelper.h"
#include "../clsScreen.h"

class clsWithdraw : clsScreen {
 public:
  static void PrintWithdraw() {
    _DrawScreenHeader("Withdraw Screen");

    clsClient Client = clsClientHelper::ReadClientByAccountNumber();
    clsClientHelper::PrintClient(Client);

    double Amount = clsInputValidate::ReadDblNumber(
      "\nPlease Enter Withdraw amount Transaction");

    if (clsUtils::isAccepted(
          "\n\nAre you sure you want perform this transaction? y/n ?")) {
      if (Client.Withdraw(Amount)) {
        cout << "\nAmount Withdrawed Successfully.\n";
        cout << "\nNew Balance Is: " << Client.GetBalance();
      } else {
        cout << "\nCannot withdraw Insuffecient Balance!\n";
        cout << "Amount to withdraw is: " << Amount << '\n';
        cout << "Your Balance is: " << Client.GetBalance() << endl;
      }

    } else {
      cout << "\nOperation was canceled\n";
    }
  }
};