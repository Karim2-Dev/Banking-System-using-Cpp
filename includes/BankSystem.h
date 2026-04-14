#pragma once
#include <iostream>
#include "MyInputLib.h"
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdio>
#include "MyPrintFunctions.h"

namespace BankSystem
{
    //? ================= 1. ENUMS =================
    enum enClientData
    {
        AccNum = 1,
        PinCode,
        Name,
        PhoneNumber,
        AccountBalance,
    };

    enum enMainMenuOptions
    {
        enClientList = 1,
        enAddClient,
        enDeleteClient,
        enUpdateClient,
        enFindClient,
        enTransactionClient,
        enManageUsers,
    };
    enum enTransacitonOptions
    {
        Deposit = 1,
        Withdraw,
        TotalBalances,
    };
    enum enManageUsersOptions
    {
        enShowUsersList = 1,
        enAddNewUser = 2,
        enDeleteUser = 3,
        enUpdateUser = 4,
        enFindUser = 5,
    };
    enum enPermission
    {
        enClientListAccess = 1,
        enAddNewClientAccess = 2,
        enDeleteClientAccess = 4,
        enUpdateClientAccess = 8,
        enFindClientAccess = 16,
        enTransactionsAccess = 32,
        enManageUsersAccess = 64,
    };
    //? ================= 2. STRUCT =================
    struct stClient
    {
        string AccNum;
        string PinCode;
        string Name;
        string PhoneNumber;
        double AccountBalance;
        bool MarkForDelete = false;
    };
    struct stUser
    {
        short Permission;
        string UserName;
        string Password;
    };

    //? ================= Global Variables =================
    const string FileName = "ClientsData.txt";
    const string UserFile = "UsersData.txt";
    stUser CurrentUser;

    //? ================= 3. STRING UTILITIES =================
    string JoinString(vector<string> &vArrString, string seperator)
    {
        string MyString = "";
        for (string &S1 : vArrString)
            MyString += S1 + seperator;
        return MyString.substr(0, MyString.length() - seperator.length());
    }

    vector<string> MySplit(string Line, string delim)
    {
        vector<string> vMySplit;
        short Position;
        string sWord;
        while ((Position = Line.find(delim)) != string::npos)
        {
            sWord = Line.substr(0, Position);
            if (sWord != "")
                vMySplit.push_back(sWord);
            Line.erase(0, Position + delim.length());
        }
        if (Line != "")
            vMySplit.push_back(Line);
        return vMySplit;
    }

    //? ================= 4. DATA TRANSFORMATION (RECORD/LINE) =================
    string ConvertRecordToLine(stClient &stDataAccount)
    {
        vector<string> vDataBankArr;
        vDataBankArr.push_back(stDataAccount.AccNum);
        vDataBankArr.push_back(stDataAccount.PinCode);
        vDataBankArr.push_back(stDataAccount.Name);
        vDataBankArr.push_back(stDataAccount.PhoneNumber);
        vDataBankArr.push_back(to_string(stDataAccount.AccountBalance));
        return JoinString(vDataBankArr, "#//#");
    }
    string ConvertRecordToLine(stUser &User)
    {
        vector<string> vUserData;
        vUserData.push_back(User.UserName);
        vUserData.push_back(User.Password);
        vUserData.push_back(to_string(User.Permission));
        return JoinString(vUserData, "#//#");
    }

    void ConvertLineToRecord(string Line, stUser &User)
    {
        vector<string> SplitLine = MySplit(Line, "#//#");
        User.UserName = SplitLine[0];
        User.Password = SplitLine[1];
        User.Permission = stoi(SplitLine[2]);
    }
    void ConvertLineToRecord(string Line, stClient &stDataAccount)
    {
        vector<string> SplitLine = MySplit(Line, "#//#");
        stDataAccount.AccNum = SplitLine[0];
        stDataAccount.PinCode = SplitLine[1];
        stDataAccount.Name = SplitLine[2];
        stDataAccount.PhoneNumber = SplitLine[3];
        stDataAccount.AccountBalance = stod(SplitLine[4]);
    }

    //? ================= 5. FILE OPERATIONS =================
    vector<stClient> LoadClientsDataFromFile(string FileName)
    {
        vector<stClient> vClients;
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open())
        {
            string Line;
            stClient Client;
            while (getline(MyFile, Line))
            {
                ConvertLineToRecord(Line, Client);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }

    vector<stClient> vClients = LoadClientsDataFromFile(FileName);
    vector<stUser> ReadUsers();
    vector<stUser> vUsers = ReadUsers();

    vector<stClient> saveClientsDataToFile(string FileName, vector<stClient> &vClients)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out);
        string Line;
        if (MyFile.is_open())
        {
            for (stClient &Client : vClients)
            {
                if (Client.MarkForDelete == false)
                {
                    Line = ConvertRecordToLine(Client);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
        return vClients;
    }

    void SaveClientInFile(string FileName, stClient &Client)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out | ios::app);
        string Line;
        if (MyFile.is_open())
        {

            Line = ConvertRecordToLine(Client);
            MyFile << Line << endl;

            MyFile.close();
        }
        vClients.push_back(Client);
    }

    //! Users File
    vector<stUser> ReadUsers()
    {
        vector<stUser> Users;
        fstream MyFile;

        MyFile.open(UserFile, ios::in);

        if (MyFile.is_open())
        {
            string Line;
            stUser UserInFile;
            while (getline(MyFile, Line))
            {
                ConvertLineToRecord(Line, UserInFile);
                Users.push_back(UserInFile);
            };
        }
        return Users;
    }

    //? ================= 6. CORE LOGIC & SEARCH =================
    // Global Vector Initialization

    bool FindClient(vector<stClient> &vClients, string AccNum)
    {
        for (stClient &stClient : vClients)
        {
            if (stClient.AccNum == AccNum)
                return true;
        }
        return false;
    }

    bool FindClient(vector<stClient> &vClients, string AccNum, stClient &Client)
    {
        for (stClient &C : vClients)
        {
            if (C.AccNum == AccNum)
            {
                Client = C;
                return true;
            }
        }
        return false;
    }

    //! Users
    bool IsValidUser(stUser User)
    {
        for (stUser U : vUsers)
        {
            if (U.UserName == User.UserName && U.Password == User.Password)
                return true;
        }
        return false;
    }
    bool isFindUser(string &UserName, vector<stUser> Users)
    {
        for (stUser &U : Users)
        {
            if (U.UserName == UserName)
            {
                return true;
            }
        }
        return false;
    }
    bool FindUser(string &UserName, vector<stUser> &Users, stUser &User)
    {
        for (stUser &U : Users)
        {
            if (U.UserName == UserName)
            {
                User = U;
                return true;
            }
        }
        return false;
    }

    bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient> &Clients)
    {
        for (stClient &Client : Clients)
        {
            if (Client.AccNum == AccountNumber)
            {
                Client.MarkForDelete = true;
                return true;
            }
        }
        return false;
    }
    bool IsAccess(short flag, enPermission Permission)
    {
        return (flag & Permission) || flag == -1;
    }

    //? ================= 7. INPUT & PRINT UTILS =================
    void PrintClientCard(stClient &Client)
    {
        cout << "Account Number  : " << Client.AccNum << endl;
        cout << "Pin Code        : " << Client.PinCode << endl;
        cout << "Name            : " << Client.Name << endl;
        cout << "Phone           : " << Client.PhoneNumber << endl;
        cout << "Account Balanced: " << Client.AccountBalance << endl;
    }
    void PrintUserCard(stUser &User)
    {
        cout << "\nThe following are the client details:\n";
        cout << "------------------------------------------------------\n";
        cout << "User Name             : " << User.UserName << endl;
        cout << "Password              : " << User.Password << endl;
        cout << "Permission            : " << User.Permission << endl;
        cout << "------------------------------------------------------\n";
    }

    stClient ReadNewClient(vector<stClient> &Clients)
    {
        stClient AccData;
        AccData.AccNum = MyInputLib::ReadString("Enter Account Number? ");
        while (FindClient(Clients, AccData.AccNum))
        {
            printf("Client with [%s] already exists, Enter another Account Number? ", AccData.AccNum.c_str());
            cin >> AccData.AccNum;
        }
        AccData.PinCode = MyInputLib::ReadString("Enter PinCode? ");
        cin.ignore(1, '\n');
        AccData.Name = MyInputLib::ReadLine("Enter Name? ");
        AccData.PhoneNumber = MyInputLib::ReadString("Enter Phone? ");
        AccData.AccountBalance = MyInputLib::ReadDoubleNum("Enter Account Balance? ");
        return AccData;
    }

    stClient AddNewClient(vector<stClient> &Clients)
    {
        return ReadNewClient(Clients);
    }

    void PrintHeaderDatastClients(vector<stClient> &stClientsData)
    {
        cout << setw(75) << "stClient List (" << stClientsData.size() << ") stClients(s)";
        cout << "\n______________________________________________________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(22) << "Account Number";
        cout << "| " << left << setw(17) << "Pin Code";
        cout << "| " << left << setw(42) << "stClient Name";
        cout << "| " << left << setw(17) << "Phone";
        cout << "| " << left << setw(20) << "Balance";
        cout << "\n______________________________________________________________________________________________________________________________________________________\n";
    }

    void PrintClientsData(vector<stClient> &stClientsData)
    {
        PrintHeaderDatastClients(stClientsData);
        for (stClient &stClientData : stClientsData)
        {
            cout << "\n";
            cout << "| " << left << setw(22) << stClientData.AccNum;
            cout << "| " << left << setw(17) << stClientData.PinCode;
            cout << "| " << left << setw(42) << stClientData.Name;
            cout << "| " << left << setw(17) << stClientData.PhoneNumber;
            cout << "| " << left << setw(20) << stClientData.AccountBalance;
        }
        cout << "\n______________________________________________________________________________________________________________________________________________________\n";
    }
    void PrintTotalBalancesHeader(vector<stClient> &stClientsData)
    {
        cout << setw(75) << "stClient List (" << stClientsData.size() << ") stClients(s)";
        cout << "\n______________________________________________________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(20) << "Account Number";
        cout << "| " << left << setw(40) << "stClient Name";
        cout << "| " << left << setw(40) << "Balance";
        cout << "\n______________________________________________________________________________________________________________________________________________________\n";
    }

    int GetTotalBalances(vector<stClient> &Clients)
    {
        int Total = 0;
        for (stClient &Client : Clients)
        {
            Total += Client.AccountBalance;
        }
        return Total;
    };
    void PrintTotalBalances(vector<stClient> &stClientsData, int TotalBalances)
    {
        PrintTotalBalancesHeader(stClientsData);
        for (stClient &stClientData : stClientsData)
        {
            cout << "\n";
            cout << "| " << left << setw(20) << stClientData.AccNum;
            cout << "| " << left << setw(40) << stClientData.Name;
            cout << "| " << left << setw(40) << stClientData.AccountBalance;
        }
        cout << "\n______________________________________________________________________________________________________________________________________________________\n\n";

        cout << MyPrint::Tabs(8) << "Total Balances = " << TotalBalances << endl;
    }

    string ReadClientAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }
    //! Users
    stUser ReadUser()
    {
        stUser User;
        cout << "Enter UserName? ";
        cin >> User.UserName;
        cout << "Enter Password? ";
        cin >> User.Password;
        return User;
    }

    short ReadPermission()
    {

        char IsUserFullAcces;
        cout << "\nDo you want to give full access? y/n ";
        cin >> IsUserFullAcces;

        if (tolower(IsUserFullAcces) == 'y')
            return -1;

        // Else
        char IsAccess = 'n';
        unsigned short flags = 0;
        cout << "\nDo you want to give access to:\n";

        cout << "\nShow Client List? y/n ";
        cin >> IsAccess;

        if (tolower(IsAccess) == 'y')
        {
            flags |= enPermission::enClientListAccess;
        }

        cout << "\nAdd New Client? y/n ";

        cin >> IsAccess;

        if (tolower(IsAccess) == 'y')
        {
            flags |= enPermission::enAddNewClientAccess;
        }

        cout << "\nDelete Client? y/n ";
        cin >> IsAccess;

        if (tolower(IsAccess) == 'y')
        {
            flags |= enPermission::enDeleteClientAccess;
        }

        cout << "\nUpdate Client? y/n ";
        cin >> IsAccess;

        if (tolower(IsAccess) == 'y')
        {
            flags |= enPermission::enUpdateClientAccess;
        }

        cout << "\nFind Client? y/n ";
        cin >> IsAccess;

        if (tolower(IsAccess) == 'y')
        {
            flags |= enPermission::enFindClientAccess;
        }

        cout << "\nTransactions? y/n ";
        cin >> IsAccess;

        if (tolower(IsAccess) == 'y')
        {
            flags |= enPermission::enTransactionsAccess;
        }

        cout << "\nManage Users? y/n ";
        cin >> IsAccess;
        if (tolower(IsAccess) == 'y')
        {
            flags |= enPermission::enManageUsersAccess;
        }

        if (flags == 127)
            flags = -1;

        return flags;
    };

    stUser ReadNewUser()
    {
        stUser User;
        cout << "Enter Username? ";
        cin >> User.UserName;

        while (isFindUser(User.UserName, vUsers))
        {
            printf("User with [%s] already exists, Enter another Username? ", User.UserName.c_str());
            cin >> User.UserName;
        }

        cout << "Enter Password? ";
        cin >> User.Password;

        User.Permission = ReadPermission();

        return User;
    }

    void AddNewUser(stUser User)
    {
        fstream MyFile;

        MyFile.open(UserFile, ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << ConvertRecordToLine(User) << endl;
            vUsers.push_back(User);
        }
        MyFile.close();
    }

    void DeleteUser(string UserName)
    {
        fstream MyFile;

        MyFile.open(UserFile, ios::out);

        if (MyFile.is_open())
        {
            string Line;

            for (stUser &User : vUsers)
            {
                if (User.UserName != UserName)
                    MyFile << ConvertRecordToLine(User) << endl;
            }
        }
        MyFile.close();
    }
    void UpdateUser(string UserName)
    {

        fstream MyFile;

        MyFile.open(UserFile, ios::out);

        if (MyFile.is_open())
        {
            string Line;

            for (stUser &User : vUsers)
            {
                if (User.UserName == UserName)
                {
                    cout << "Enter Password? ";
                    cin >> User.Password;

                    User.Permission = ReadPermission();

                    if (User.UserName == CurrentUser.UserName)
                    {
                        CurrentUser = User;
                    }
                }
                MyFile << ConvertRecordToLine(User) << endl;
            }
        }
        MyFile.close();
    }

    //? ================= 8. ACTIONS / FEATURES =================
    bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient> &vClients, string FileName)
    {
        stClient Client;
        char Answer = 'n';
        if (FindClient(vClients, AccountNumber, Client))
        {
            PrintClientCard(Client);
            cout << "\n\nAre you sure you want delete this client? y/n ?";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
                saveClientsDataToFile(FileName, vClients);
                vClients = LoadClientsDataFromFile(FileName);
                cout << "\n\nClient Deleted Successfully. !!\n";
                return true;
            }
        }
        else
        {
            printf("\nClient with Account Number (%s) is Not Found!\n", AccountNumber.c_str());
        }
        return false;
    }

    bool EditClientByAccountNumber(string AccountNumber, vector<stClient> &vClients, string FileName)
    {
        stClient Client;
        char Answer = 'N';
        if (FindClient(vClients, AccountNumber, Client))
        {
            PrintClientCard(Client);
            cout << "\n\nAre you sure you want Edit this client? y/n ?";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                for (stClient &C : vClients)
                {
                    if (C.AccNum == AccountNumber)
                    {
                        C = ReadNewClient(vClients);
                        break;
                    }
                }
                saveClientsDataToFile(FileName, vClients);
                vClients = LoadClientsDataFromFile(FileName);
                cout << "\n\nClient Edit Successfully!\n";
            }
            return true;
        }
        printf("\nClient with Account Number (%s) is Not Found!\n", AccountNumber.c_str());
        return false;
    };
    bool DepositClient(vector<stClient> &vClients, string FileName)
    {

        string AccountNumber;
        stClient Client;

        bool isFindClient;

        do
        {
            AccountNumber = ReadClientAccountNumber();
            isFindClient = FindClient(vClients, AccountNumber, Client);

            if (isFindClient)
            {
                PrintClientCard(Client);

                int DepositAmount = MyInputLib::ReadNumber("\nPlease enter deposit amount? ");

                char Answer = 'N';
                cout << "\n\nAre you sure you want perform this transaction? y/n ?";
                cin >> Answer;
                if (toupper(Answer) == 'Y')
                {
                    for (stClient &C : vClients)
                    {
                        if (C.AccNum == AccountNumber)
                        {
                            C.AccountBalance += DepositAmount;
                        }
                    }
                    saveClientsDataToFile(FileName, vClients);
                }
            }
            else
                printf("\nClient with Account Number (%s) is Not Found!\n", AccountNumber.c_str());

        } while (!isFindClient);

        return false;
    }
    bool WithdrawClient(vector<stClient> &vClients, string FileName)
    {

        string AccountNumber;
        stClient Client;

        bool isFindClient;

        do
        {
            AccountNumber = ReadClientAccountNumber();
            isFindClient = FindClient(vClients, AccountNumber, Client);

            if (isFindClient)
            {
                PrintClientCard(Client);

                int WithdrawAmount = MyInputLib::ReadNumber("\nPlease enter withdraw amount? ");

                while (WithdrawAmount > Client.AccountBalance)
                {
                    printf("\nAmount Exceeds the balance, you can withdraw up to: %.*f", 3, Client.AccountBalance);
                    cin >> WithdrawAmount;
                }

                char Answer = 'N';
                cout << "\n\nAre you sure you want perform this transaction? y/n ?";
                cin >> Answer;
                if (toupper(Answer) == 'Y')
                {
                    for (stClient &C : vClients)
                    {
                        if (C.AccNum == AccountNumber)
                        {
                            C.AccountBalance -= WithdrawAmount;
                        }
                    }
                    saveClientsDataToFile(FileName, vClients);
                }
            }
            else
                printf("\nClient with Account Number (%s) is Not Found!\n", AccountNumber.c_str());

        } while (!isFindClient);

        return false;
    }

    //? ================= 9. UI PAGES & NAVIGATION =================
    //! Main Menu Options
    void PrintHeaderPage(string Msg)
    {
        cout << "------------------------------------------------\n";
        cout << "\t\t  " << Msg << "\n";
        cout << "------------------------------------------------\n";
    }
    void PrintAccessDeniedScreen()
    {
        system("clear");

        cout << "------------------------------------------------\n";
        cout << "Access Denied,\n";
        cout << "You dont Have Permission To Do this,\n";
        cout << "Please Concat Your Admin,\n";
        cout << "------------------------------------------------\n";

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore();
        cin.get();
    };

    //? Client List Page
    void PrintClientListPage()
    {
        system("clear");
        PrintClientsData(vClients);

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore();
        cin.get();
    }
    //? Add Page
    void PrintAddMenuScreen()
    {
        system("clear");

        PrintHeaderPage("Add New Clients Screen");
        cout << "Adding New Client: \n\n";
        stClient Client = AddNewClient(vClients);
        SaveClientInFile(FileName, Client);

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
    //? Delete Page
    void PrintDeleteClientScreen()
    {
        system("clear");

        PrintHeaderPage("Delete Screen");
        string AccountNumber = ReadClientAccountNumber();
        DeleteClientByAccountNumber(AccountNumber, vClients, FileName);

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
    //? Edit Page
    void PrintEditClientScreen()
    {
        system("clear");

        PrintHeaderPage("Edit Screen");
        string AccountNumber = ReadClientAccountNumber();
        EditClientByAccountNumber(AccountNumber, vClients, FileName);

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
    //? Find Page
    void PrintFindClientScreen()
    {
        system("clear");

        PrintHeaderPage("Find Client Screen");
        stClient Client;
        string AccountNumber = ReadClientAccountNumber();
        if (FindClient(vClients, AccountNumber, Client))
            PrintClientCard(Client);
        else
            printf("\nClient with Account Number (%s) is Not Found!\n", AccountNumber.c_str());

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    //! Transaction Menu Options
    void DepositPage()
    {
        system("clear");
        PrintHeaderPage("Deposit Screen");

        DepositClient(vClients, FileName);

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    };
    void WithdrawPage()
    {
        system("clear");
        PrintHeaderPage("Withdraw Screen");

        WithdrawClient(vClients, FileName);

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    };

    void TotalBlancesPage()
    {
        system("clear");

        PrintTotalBalances(vClients, GetTotalBalances(vClients));

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
    //! Users Menu UI

    void PrintUsersHeaderList(vector<stUser> UsersData)
    {
        cout << setw(75) << "UsersList (" << UsersData.size() << ") stUser(s)";
        cout << "\n______________________________________________________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(22) << "User Name";
        cout << "| " << left << setw(17) << "Password";
        cout << "| " << left << setw(42) << "Permissions";
        cout << "\n______________________________________________________________________________________________________________________________________________________\n";
    }

    void PrintUserListScreen(vector<stUser> &stUsers)
    {
        PrintUsersHeaderList(stUsers);
        for (stUser &stUser : stUsers)
        {
            cout << "\n";
            cout << "| " << left << setw(22) << stUser.UserName;
            cout << "| " << left << setw(17) << stUser.Password;
            cout << "| " << left << setw(42) << stUser.Permission;
        }
        cout << "\n______________________________________________________________________________________________________________________________________________________\n";
    }

    void UsersListScreen()
    {

        system("clear");

        vector<stUser> Users = ReadUsers();
        PrintUserListScreen(Users);

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore();
        cin.get();
    }

    void AddNewUserScreen()
    {
        system("clear");
        PrintHeaderPage("Add New User Screen");
        char Answer = 'y';
        do
        {
            cout << "Adding New User\n";

            stUser NewUser = ReadNewUser();

            AddNewUser(NewUser);
            cout << "User Added Successfuly, do you want to add more Users? Y/N? \n";
            cin >> Answer;
        } while (tolower(Answer) == 'y');

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore();
        cin.get();
    }
    void DeleteUserScreen()
    {
        system("clear");
        PrintHeaderPage("Delete User Screen");

        string UserName;

        cout << "Please Enter Username? ";
        cin >> UserName;

        stUser User;

        if (FindUser(UserName, vUsers, User))
        {
            PrintUserCard(User);

            char Answer;

            cout << "\n\nAre you sure you want delete this User? \n";
            cin >> Answer;

            if (tolower(Answer) == 'y')
            {
                DeleteUser(UserName);
                vUsers = ReadUsers();
                cout << "\n\nUser Deleted Successfully.\n";
            }
        }
        else
        {
            printf("Client with Account Number (%s) is Not Found! ", UserName.c_str());
        }

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore();
        cin.get();
    }

    void UpdateUserScreen()
    {
        system("clear");
        PrintHeaderPage("Update User Screen");

        string UserName = MyInputLib::ReadString("Please enter username? ");

        stUser User;

        if (FindUser(UserName, vUsers, User))
        {
            PrintUserCard(User);

            char Answer;

            cout << "\n\nAre you sure you want delete this User? \n";
            cin >> Answer;

            if (tolower(Answer) == 'y')
            {
                UpdateUser(UserName);
                vUsers = ReadUsers();
                cout << "\n\nUser Updated Successfully.\n";
            }
            else
            {
                printf("Client with Account Number (%s) is Not Found! ", UserName.c_str());
            }

            cout << "\n\nPress any key to go back to Main Menu...\n";
            cin.ignore();
            cin.get();
        }
    }
    void FindUserScreen()
    {
        system("clear");
        PrintHeaderPage("Update User Screen");

        string UserName = MyInputLib::ReadString("Please enter username? ");
        stUser User;

        if (FindUser(UserName, vUsers, User))
            PrintUserCard(User);

        else
            printf("Client with Account Number (%s) is Not Found! ", UserName.c_str());

        cout << "\n\nPress any key to go back to Main Menu...\n";
        cin.ignore();
        cin.get();
    }

    void PrintMainMenuScreeen();   // Forward declaration for GetPageChoose
    void PrintTransactionClient(); // Forward declaration for GetTransactionOptions
    void PrintManageUsersScreen();
    void GetMainMenuOption(bool &IsLogIn)
    {
        enMainMenuOptions Page = (enMainMenuOptions)MyInputLib::ReadNumber("\nChoose what do you want to do [1,6]");
        switch (Page)
        {
        case enMainMenuOptions::enClientList:
            if (IsAccess(CurrentUser.Permission, enPermission::enClientListAccess))
                PrintClientListPage();
            else
                PrintAccessDeniedScreen();
            break;
        case enMainMenuOptions::enAddClient:
            if (IsAccess(CurrentUser.Permission, enPermission::enClientListAccess))
                PrintAddMenuScreen();
            else
                PrintAccessDeniedScreen();
            break;

        case enMainMenuOptions::enDeleteClient:

            if (IsAccess(CurrentUser.Permission, enPermission::enDeleteClientAccess))
                PrintDeleteClientScreen();
            else
                PrintAccessDeniedScreen();
            break;
        case enMainMenuOptions::enUpdateClient:

            if (IsAccess(CurrentUser.Permission, enPermission::enUpdateClientAccess))
                PrintEditClientScreen();
            else
                PrintAccessDeniedScreen();

            break;
        case enMainMenuOptions::enFindClient:

            if (IsAccess(CurrentUser.Permission, enPermission::enFindClientAccess))
                PrintFindClientScreen();
            else
                PrintAccessDeniedScreen();
            break;
        case enMainMenuOptions::enTransactionClient:

            if (IsAccess(CurrentUser.Permission, enPermission::enTransactionsAccess))
                PrintTransactionClient();
            else
                PrintAccessDeniedScreen();
            break;

        case enMainMenuOptions::enManageUsers:
            if (IsAccess(CurrentUser.Permission, enPermission::enManageUsersAccess))
                PrintManageUsersScreen();
            else
                PrintAccessDeniedScreen();

            break;
        default:
            IsLogIn = false;
            break;
        }
    }
    void GetTransactionOption()
    {
        enTransacitonOptions Page = (enTransacitonOptions)MyInputLib::ReadNumber("\nChoose what do you want to do [1,6]");
        switch (Page)
        {
        case enTransacitonOptions::Deposit:
            DepositPage();
            break;
        case enTransacitonOptions::Withdraw:
            WithdrawPage();
            break;
        case enTransacitonOptions::TotalBalances:
            TotalBlancesPage();
            break;

        default:
            return;
        }
    }
    void GetManageUsersOption()
    {
        enManageUsersOptions Page = (enManageUsersOptions)MyInputLib::ReadNumber("\nChoose what do you want to do [1,6]");
        switch (Page)
        {
        case enManageUsersOptions::enShowUsersList:
            UsersListScreen();
            break;
        case enManageUsersOptions::enAddNewUser:
            AddNewUserScreen();
            break;
        case enManageUsersOptions::enDeleteUser:
            DeleteUserScreen();
            break;
        case enManageUsersOptions::enUpdateUser:
            UpdateUserScreen();
            break;
        case enManageUsersOptions::enFindUser:
            FindUserScreen();
            break;

        default:
            break;
        }
    }

    void PrintMainMenuScreeen(bool &IsLogIn)
    {
        system("clear");
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
        cout << "\t[8] Logout.\n";
        cout << "=========================================================\n";
        GetMainMenuOption(IsLogIn);
    }
    void PrintTransactionClient()
    {
        system("clear");
        cout << "\n=========================================================\n";
        cout << "\tTransactions Menu Screen\n";
        cout << "=========================================================\n";
        cout << "\t[1] Deposit.\n";
        cout << "\t[2] Withdraw.\n";
        cout << "\t[3] Total Balances.\n";
        cout << "\t[4] Main Menu.\n";
        cout << "=========================================================\n";
        GetTransactionOption();
    }
    void PrintManageUsersScreen()
    {
        system("clear");
        cout << "\n=========================================================\n";
        cout << "\tManage User Menu Screen\n";
        cout << "=========================================================\n";
        cout << "\t[1] List User.\n";
        cout << "\t[2] Add New User.\n";
        cout << "\t[3] Delete User.\n";
        cout << "\t[4] Update User.\n";
        cout << "\t[5] Find User.\n";
        cout << "\t[6] Main Menu.\n";
        cout << "=========================================================\n";
        GetManageUsersOption();
    }
    void LoginScreen()
    {
        system("clear");
        PrintHeaderPage("Login Screen");

        stUser User = ReadUser();

        while (!IsValidUser(User))
        {
            system("clear");
            PrintHeaderPage("Login Screen");
            cout << "Invalid Username/Password!\n";
            User = ReadUser();
        }

        FindUser(User.UserName, vUsers, CurrentUser);
        bool IsLogIn = true;
        while (IsLogIn)
        {
            PrintMainMenuScreeen(IsLogIn);
        }
    }
}