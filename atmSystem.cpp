
#include "includes/BankSystem.h"

using namespace BankSystem;

// Enums
enum enAtmMainMenu
{
    enQuickWithdraw = 1,
    enNormalWithdraw,
    enDeposit,
    enCheckBalance,
};

// Global Variabels
stClient CurrentClient;
bool IsLogin = false;

bool IsClientLoginValid(stClient &Client)
{

    for (stClient &C : vClients)
    {
        if ((C.AccNum == Client.AccNum) && (Client.PinCode == C.PinCode))
            return true;
    }
    return false;
}

stClient ReadClientLogin()
{
    stClient Client;
    Client.AccNum = MyInputLib::ReadString("Enter Account Number? ");
    Client.PinCode = to_string(MyInputLib::ReadPositiveNumber("Enter PIN Code? "));
    return Client;
}

short ReadQuickWithdrawOption()
{
    short Number = MyInputLib::ReadPositiveNumber("Choose what to withdraw from [1] to [8]");

    short Option = -1;
    switch (Number)
    {
    case 1:
        Option = 20;
        break;
    case 2:
        Option = 50;
        break;
    case 3:
        Option = 100;
        break;
    case 4:
        Option = 200;
        break;
    case 5:
        Option = 400;
        break;
    case 6:
        Option = 600;
        break;
    case 7:
        Option = 800;
        break;
    case 8:
        Option = 1000;
        break;
    default:
        Option;
    }
    return Option;
}

bool CheckAnswerUser()
{
    char Answer;
    cout << "\n\nAre you sure you want perform transaction? y/n ";
    cin >> Answer;

    return tolower(Answer) == 'y';
}

void UpdateBalance(int Balance)
{
    CurrentClient.AccountBalance += Balance;
    for (stClient &C : vClients)
    {
        if (C.AccNum == CurrentClient.AccNum)
        {
            C.AccountBalance += Balance;
            saveClientsDataToFile(FileName, vClients);
        }
    }
    cout << "Done Successfully. New balance is: " << CurrentClient.AccountBalance << endl;
}

void QuickWithDrawScreen()
{
    system("clear");
    cout << "=========================================================\n";
    cout << "\tQuick Withdraw Screen\n";
    cout << "=========================================================\n";
    cout << "\t[1] 20 \t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "=========================================================\n";
    cout << "Your Balance is: " << CurrentClient.AccountBalance << endl;

    short Withdraw = ReadQuickWithdrawOption();

    if (Withdraw != -1)
    {
        while (Withdraw > CurrentClient.AccountBalance)
        {
            cout << "The amount exceeds your balance, make choice.\n";
            Withdraw = ReadQuickWithdrawOption();
        }

        if (CheckAnswerUser())
        {
            UpdateBalance(-Withdraw);
        }
    }

    BackToMainMenu();
}
void NormalWithDrawScreen()
{
    system("clear");
    cout << "=========================================================\n";
    cout << "\tNormal Withdraw Screen\n";
    cout << "=========================================================\n";

    int Withdraw = 0;
    do
    {
        Withdraw = MyInputLib::ReadNumber("Enter an amount multiple of 5's");

    } while (Withdraw % 5 != 0);

    if (CheckAnswerUser())
    {
        UpdateBalance(-Withdraw);
    }
    BackToMainMenu();
}
void DepositScreen()
{
    system("clear");
    cout << "=========================================================\n";
    cout << "\tDeposit Screen\n";
    cout << "=========================================================\n";

    int Deposit = MyInputLib::ReadPositiveNumber("Enter a positve Deposit Amount");

    if (CheckAnswerUser())
    {
        UpdateBalance(Deposit);
    }

    BackToMainMenu();
}

void CheckBalanceScreen()
{
    system("clear");
    cout << "=========================================================\n";
    cout << "\tCheck Balance Screen\n";
    cout << "=========================================================\n";

    cout << "Your Balance is: " << CurrentClient.AccountBalance << endl;
    BackToMainMenu();
}

void GetAtmMenuOption()
{
    enAtmMainMenu Page = (enAtmMainMenu)MyInputLib::ReadPositiveNumber("\nChoose what do you want to do [1,5]");
    switch (Page)
    {
    case enAtmMainMenu::enQuickWithdraw:
        QuickWithDrawScreen();
        break;
    case enAtmMainMenu::enNormalWithdraw:
        NormalWithDrawScreen();
        break;
    case enAtmMainMenu::enDeposit:
        DepositScreen();
        break;
    case enAtmMainMenu::enCheckBalance:
        CheckBalanceScreen();
        break;
    default:
        IsLogin = false;
        break;
    }
}

void AtmMenuScreen()
{

    system("clear");
    cout << "\n=========================================================\n";
    cout << "\tATM Main Menu Screen\n";
    cout << "=========================================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "=========================================================\n";

    GetAtmMenuOption();
}

void AtmLoginScreen()
{
    stClient ClientLogin;
    bool isClientValid = true;

    do
    {
        system("clear");
        PrintHeaderPage("Login Screen");

        if (!isClientValid)
        {
            cout << "Invalid Accout Number/PinCode!\n";
        }

        ClientLogin = ReadClientLogin();
        isClientValid = IsClientLoginValid(ClientLogin);

    } while (!isClientValid);
    FindClient(vClients, ClientLogin.AccNum, CurrentClient);

    IsLogin = true;

    while (IsLogin)
    {
        AtmMenuScreen();
    }
}

int main()
{

    while (true)
    {
        AtmLoginScreen();
    }

    return 0;
}