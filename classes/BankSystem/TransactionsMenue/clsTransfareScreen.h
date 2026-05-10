
#include "../../clsUtil.h"
#include "../clsBankClient.h"
#include "../clsClientHelper.h"
#include "../clsScreen.h"

class clsTransfareScreen : clsScreen {
  static void _PrintClientDetails(clsClient& Client) {
    cout << endl;
    clsUtils::PrintLine(30);
    cout << "\nClient Card: \n";
    clsUtils::PrintLine(30);
    cout << endl;
    cout << "Name            : " << Client.FullName() << endl;
    cout << "Account Number  : " << Client.GetAccountNumber() << endl;
    cout << "Balanced        : " << Client.GetBalance() << endl;
    clsUtils::PrintLine(30);
    ;
  }

 public:
  static void PrintTransfareScreen() {
    clsClient SourceClient = clsClientHelper::ReadClientByAccountNumber(
      "Please Enter Account Number to transfare From: ");
    _PrintClientDetails(SourceClient);

    clsClient DestinationClient = clsClientHelper::ReadClientByAccountNumber(
      "\nPlease Enter Account Number to transfare To: ");

    while (
      DestinationClient.GetAccountNumber() == SourceClient.GetAccountNumber()) {
      DestinationClient = clsClientHelper::ReadClientByAccountNumber(
        "\nThis Client is Already choosed to transfare from try Again: ");
    }

    _PrintClientDetails(DestinationClient);
    double Amount;
    cout << "\n\nEnter Transfare Amount? ";
    cin >> Amount;

    while (Amount > SourceClient.GetBalance()) {
      cout
        << "\n\nAmount Exceeds the available Balance, Enter Another Amount? ";
      cin >> Amount;
    }

    if (clsUtils::isAccepted(
          "Are you sure you want to perform this operation Y/n? ")) {

      if (SourceClient.Transfare(Amount, DestinationClient,CurrentUser.Username())) {
        cout << "Transfer done successfully :)\n\n";

      } else {
        cout << "Transfer Failed :(\n\n";
      }

      _PrintClientDetails(SourceClient);
      cout << endl;
      _PrintClientDetails(DestinationClient);
      cout << endl;
    }
  }
};