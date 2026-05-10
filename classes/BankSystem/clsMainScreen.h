#pragma once
#include <iostream>

#include "../clsInputValidate.h"
#include "../clsUtil.h"
#include "CurrencyExchange/clsCurrencyExchangeScreen.h"
#include "Global.h"
#include "MainMenueScreens/clsAddClientScreen.h"
#include "MainMenueScreens/clsClientListScreen.h"
#include "MainMenueScreens/clsDeleteClientScreen.h"
#include "MainMenueScreens/clsLoginRegisterListScreen.h"
#include "MainMenueScreens/clsUpdateClientScreen.h"
#include "ManageUsers/clsBankUser.h"
#include "ManageUsers/clsManageUsersScreen.h"
#include "TransactionsMenue/clsTransactionsMenue.h"
#include "clsBankClient.h"
#include "clsClientHelper.h"
#include "clsScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen {
  enum _enMainMenuOptions {
    enClientList = 1,
    enAddClient,
    enDeleteClient,
    enUpdateClient,
    enFindClient,
    enTransactionClient,
    enManageUsers,
    enLoginRegister,
    enCurrencyExchange,
  };

  //* Main Menu Pages UI
  static void _ClientListScreen() {
    ClearScreen();

    if (CurrentUser.IsAccessPage(clsUser::enClientListAccess)) {
      clsClientListScreen::PrintClientsData();
    } else {
      _DrawScreenHeader("Clients List Screen");
      PrintAccessDeniedScreen();
    }

    _BackToBackScreen();
  }

  static void _DeleteClientScreen() {
    clsUtils::ClearScreen();

    _DrawScreenHeader("Delete Client");

    if (CurrentUser.IsAccessPage(clsUser::enDeleteClientAccess)) {
      clsDeleteClientScreen::DeleteClient();
    } else {
      PrintAccessDeniedScreen();
    }

    _BackToBackScreen();
  }

  static void _UpdateClientScreen() {
    clsUtils::ClearScreen();

    _DrawScreenHeader("Update Client Screen");

    if (CurrentUser.IsAccessPage(clsUser::enUpdateClientAccess)) {
      clsUpdateClientScreen::updateClient();
    } else {
      PrintAccessDeniedScreen();
    }

    _BackToBackScreen();
  }

  static void _AddClientScreen() {
    clsUtils::ClearScreen();
    _DrawScreenHeader("Add Client");

    if (CurrentUser.IsAccessPage(clsUser::enAddNewClientAccess)) {
      clsAddClientScreen::AddClient();
    } else {
      PrintAccessDeniedScreen();
    }

    _BackToBackScreen();
  }

  static void _FindClientScreen() {
    clsUtils::ClearScreen();

    _DrawScreenHeader("Find Client");

    if (CurrentUser.IsAccessPage(clsUser::enFindClientAccess)) {
      clsClient Client = clsClientHelper::ReadClientByAccountNumber();
      clsClientHelper::PrintClient(Client);
    } else {
      PrintAccessDeniedScreen();
    }

    _BackToBackScreen();
  }

  static void _TransactionsScreen() {
    clsUtils::ClearScreen();
    if (CurrentUser.IsAccessPage(clsUser::enTransactionsAccess)) {
      clsTransactionsMenue::PrintTransactionClient();
    } else {
      _DrawScreenHeader("Transactions Screen");
      PrintAccessDeniedScreen();
      _BackToBackScreen();
    }
  }

  static void _ManageUsersScreen() {
    clsUtils::ClearScreen();

    if (CurrentUser.IsAccessPage(clsUser::enManageUsersAccess)) {
      clsManageUsersScreen::PrintManageUserScreen();
    } else {
      _DrawScreenHeader("Manage User Screen");
      PrintAccessDeniedScreen();
      _BackToBackScreen();
    }
  }

  static void _LoginRegisterScreen() {
    clsUtils::ClearScreen();
    cout << "\n\n";
    if (CurrentUser.IsAccessPage(clsUser::enLoginRegisterAccess)) {
      clsLoginRegisterListScreen::PrintRegisterDataScreen();
    } else {
      PrintAccessDeniedScreen();
    }
    _BackToBackScreen();
  }

  static void _CurrencyExchangeScreen() {
    clsUtils::ClearScreen();

    if (CurrentUser.IsAccessPage(clsUser::enCurrencyExchangeAccess)) {
      clsCurrencyExchangeScreen::PrintCurrencyExchangeScreen();

    } else {
      _DrawScreenHeader("Currency Exchange");
      PrintAccessDeniedScreen();
      _BackToBackScreen();
    }
  }

  static void _GetMainMenuOption() {
    _enMainMenuOptions Page =
      (_enMainMenuOptions)clsInputValidate::ReadIntNumber(
        "\nChoose what do you want to do [1,8]");

    switch (Page) {
      case _enMainMenuOptions::enClientList: _ClientListScreen(); break;
      case _enMainMenuOptions::enAddClient: _AddClientScreen(); break;
      case _enMainMenuOptions::enDeleteClient: _DeleteClientScreen(); break;
      case _enMainMenuOptions::enUpdateClient: _UpdateClientScreen(); break;
      case _enMainMenuOptions::enFindClient: _FindClientScreen(); break;
      case _enMainMenuOptions::enTransactionClient:
        _TransactionsScreen();
        break;

      case _enMainMenuOptions::enManageUsers: _ManageUsersScreen(); break;
      case _enMainMenuOptions::enLoginRegister: _LoginRegisterScreen(); break;
      case _enMainMenuOptions::enCurrencyExchange:
        _CurrencyExchangeScreen();
        break;

      default: CurrentUser = clsUser::Find("", ""); break;
    };
  }

 public:
  static void ShowMainMenue() {
    while (!CurrentUser.IsEmpty()) {
      clsUtils::ClearScreen();
      cout << "\n=========================================================\n";
      cout << "\t\tMain Menu Screen\n";
      cout << "=========================================================\n";
      cout << "\t[1] Show Client List.\n";
      cout << "\t[2] Add New Client.\n";
      cout << "\t[3] Delete Client.\n";
      cout << "\t[4] Update Client.\n";
      cout << "\t[5] Find Client.\n";
      cout << "\t[6] Transactions Client.\n";
      cout << "\t[7] Manage users.\n";
      cout << "\t[8] Login Register.\n";
      cout << "\t[9] Currency Exchange.\n";
      cout << "\t[10] Logout.\n";
      cout << "=========================================================\n";
      _GetMainMenuOption();
    }
  }
};
