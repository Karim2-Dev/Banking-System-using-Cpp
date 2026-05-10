
#include "../../clsUtil.h"
#include "../clsBankClient.h"
#include "../clsScreen.h"

class clsTotalBalancesScreen : clsScreen {
  static void _PrintTotalBalancesHeader(vector<clsClient>& ClientsData) {
    cout << clsUtils::Tabs(8) << "Client List (" << ClientsData.size()
         << ") Clients(s)\n";
    clsUtils::PrintLine(150);
    cout << "\n\n";
    cout << "| " << left << setw(20) << "Account Number";
    cout << "| " << left << setw(40) << "stClient Name";
    cout << "| " << left << setw(40) << "Balance";
    cout << '\n';
    clsUtils::PrintLine(150);
    cout << '\n';
  }

  static int _GetTotalBalances(vector<clsClient>& Clients) {
    int Total = 0;
    for (clsClient& Client : Clients) { Total += Client.GetBalance(); }
    return Total;
  };

 public:
  static void PrintTotalBalances() {
    vector<clsClient> ClientsData = clsClient::GetClientsList();

    _PrintTotalBalancesHeader(ClientsData);
    for (clsClient& ClientData : ClientsData) {
      cout << "\n";
      cout << "| " << left << setw(20) << ClientData.GetAccountNumber();
      cout << "| " << left << setw(40) << ClientData.FullName();
      cout << "| " << left << setw(40) << ClientData.GetBalance();
    }
    cout << "\n";
    clsUtils::PrintLine(150);

    const long double TotalBalance = _GetTotalBalances(ClientsData);

    cout << "Total Balances Of Numbers = " << TotalBalance << endl;
    cout << "Total Balances Of Text = " << clsUtils::NumberToText(TotalBalance)
         << endl;
  }
};