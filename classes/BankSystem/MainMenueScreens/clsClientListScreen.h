#pragma once
#include <iostream>

#include "../../clsUtil.h"
#include "../clsBankClient.h"
#include "../clsScreen.h"

class clsClientListScreen : protected clsScreen {
  static void _PrintHeaderDatastClients(vector<clsClient>& stClientsData) {
    cout << clsUtils::Tabs(8) << "Clients List (" << stClientsData.size()
         << ") Client(s)\n";
    clsUtils::PrintLine(150);
    cout << "\n\n";
    cout << "| " << left << setw(22) << "Account Number";
    cout << "| " << left << setw(17) << "Pin Code";
    cout << "| " << left << setw(25) << "Name";
    cout << "| " << left << setw(35) << "Email";
    cout << "| " << left << setw(17) << "Phone";
    cout << "| " << left << setw(20) << "Balance";
    cout << "\n";
    clsUtils::PrintLine(150);
  }

 public:
  static void PrintClientsData() {
    vector<clsClient> clientsData = clsClient::GetClientsList();
    _PrintHeaderDatastClients(clientsData);
    cout << "\n";

    for (clsClient& ClientData : clientsData) {
      cout << "\n";
      cout << "| " << left << setw(22) << ClientData.GetAccountNumber();
      cout << "| " << left << setw(17) << ClientData.GetPinCode();
      cout << "| " << left << setw(25) << ClientData.FullName();
      cout << "| " << left << setw(35) << ClientData.Email();
      cout << "| " << left << setw(17) << ClientData.Phone();
      cout << "| " << left << setw(20) << ClientData.GetBalance();
    }

    cout << '\n';
    clsUtils::PrintLine(150);
  }
};