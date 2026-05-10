#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include "../clsInputValidate.h"
#include "../clsPerson.h"
#include "../clsString.h"
#include "Global.h"

using namespace std;

class clsClient : public clsPerson {
 public:
  struct stTransfareData {
    string DateAndTime;
    string sAccountNumber;
    string dAccountNumber;

    double Amount;

    double sBalance;
    double dBalance;
    string Username;
  };

 private:
  enum enMode {
    EmptyMode = 0,
    Update = 1,
    AddNewMode = 2,
  };

  enMode _Mode;

  string _AccountNumber;
  string _PinCode;
  double _AccountBalance;

  bool _MarkForDelete = false;

  string User = CurrentUser.Username();

  static const string _FileName() { return "data/clients.txt"; };
  static const string _TransfareLogFile() { return "data/TransfareLog.txt"; };

  static clsClient _ConvertLineToClientObject(
    string Line, string seperator = "#//#") {
    vector<string> vClientData;

    vClientData = clsString::split(Line, seperator);

    return clsClient(enMode::Update, vClientData[0], vClientData[1],
      vClientData[2], vClientData[3], vClientData[4],
      clsString::DecryptText(vClientData[5], Key), stod(vClientData[6]));
  };

  static string _ConvertClientObjectToFile(
    clsClient Client, string seperator = "#//#") {
    vector<string> vClientData;

    vClientData.push_back(Client.GetAccountNumber());
    vClientData.push_back(Client.FirstName());
    vClientData.push_back(Client.LastName());
    vClientData.push_back(Client.Email());
    vClientData.push_back(Client.Phone());
    vClientData.push_back(clsString::EncryptText(Client.GetPinCode(), Key));
    vClientData.push_back(to_string(Client.GetBalance()));

    return clsString::JoinString(vClientData, seperator);
  }

  static clsClient _GetEmptyClientObject() {
    return clsClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
  }

  static vector<clsClient> _LoadClientsDataFromFile() {
    fstream File;

    vector<clsClient> vClients;
    File.open(_FileName(), ios::in);

    if (File.is_open()) {
      string Line;

      //^ load Clients
      while (getline(File, Line)) {
        clsClient Client = _ConvertLineToClientObject(Line);
        vClients.push_back(Client);
      }
      File.close();
    }
    return vClients;
  }

  void _SaveClientsDataToFile(vector<clsClient> vClients) {
    fstream File;

    File.open(_FileName(), ios::out);

    if (File.is_open()) {
      //^ Save Clients
      for (clsClient& C : vClients) {
        if (!C._MarkForDelete) {
          File << _ConvertClientObjectToFile(C) << endl;
        }
      }
      File.close();
    }
  }

  void _AddClientDataToFile(clsClient Client) {
    fstream File;
    File.open(_FileName(), ios::app);

    if (File.is_open()) {
      //^ Save Client
      File << _ConvertClientObjectToFile(Client) << endl;
      File.close();
    } else {
      cout << "Fuck Off" << endl;
    }
  }

  void _Update() {
    vector<clsClient> _vClients;

    _vClients = _LoadClientsDataFromFile();

    for (clsClient& C : _vClients) {
      if (C.GetAccountNumber() == GetAccountNumber()) {
        C = *this;
        break;
      }
    }

    _SaveClientsDataToFile(_vClients);
  }
  void _Add() { _AddClientDataToFile(*this); };

  string _ConvertTransfareDataToLine(
    double Amount, clsClient& DestinationClient, string UserName) {
    vector<string> vTransfareData;

    vTransfareData.push_back(clsDate::DateAndTimetoString());
    vTransfareData.push_back(GetAccountNumber());
    vTransfareData.push_back(DestinationClient.GetAccountNumber());

    vTransfareData.push_back(to_string(Amount));
    vTransfareData.push_back(to_string(GetBalance()));
    vTransfareData.push_back(to_string(DestinationClient.GetBalance()));

    vTransfareData.push_back(UserName);

    return clsString::JoinString(vTransfareData, "#//#");
  };

  static stTransfareData _ConvertLineToTransfareData(
    string Line, string seperator = "#//#") {
    stTransfareData TransfareData;

    vector<string> vTransfareData = clsString::split(Line, seperator);

    TransfareData.DateAndTime = vTransfareData[0];
    TransfareData.sAccountNumber = vTransfareData[1];
    TransfareData.dAccountNumber = vTransfareData[2];

    TransfareData.Amount = stod(vTransfareData[3]);
    TransfareData.sBalance = stod(vTransfareData[4]);
    TransfareData.dBalance = stod(vTransfareData[5]);

    TransfareData.Username = vTransfareData[6];

    return TransfareData;
  }
  static vector<stTransfareData> _LoadTransfareLog() {
    fstream File;

    vector<stTransfareData> vTransfareData;
    File.open(_TransfareLogFile(), ios::in);

    if (File.is_open()) {
      string Line;

      //^ load Clients
      while (getline(File, Line)) {
        stTransfareData TransfareData = _ConvertLineToTransfareData(Line);
        vTransfareData.push_back(TransfareData);
      }
      File.close();
    }
    return vTransfareData;
  }

  void _RegisterTransfareLog(
    double Amount, clsClient& DestinationClient, string UserName) {
    fstream File;
    File.open(_TransfareLogFile(), ios::app);

    if (File.is_open()) {
      //^ Save Client
      File << _ConvertTransfareDataToLine(Amount, DestinationClient, UserName)
           << endl;
      File.close();
    } else {
      cout << "Fuck Off" << endl;
    }
  };

 public:
  //* Constructor
  clsClient(enMode Mode, string AccountNumber, string FirstName,
    string LastName, string Email, string Phone, string PinCode,
    float AccountBalance)
    : clsPerson(FirstName, LastName, Email, Phone) {
    _Mode = Mode;
    _AccountNumber = AccountNumber;
    _PinCode = PinCode;
    _AccountBalance = AccountBalance;
  };

  //& Account
  string GetAccountNumber() { return _AccountNumber; }

  //& PinCode *//
  void setPinCode(string PinCode) { _PinCode = PinCode; }
  string GetPinCode() { return _PinCode; }

  //& Account Balance *//
  void setAccountBalance(double AccountBalance) {
    _AccountBalance = AccountBalance;
  }
  double GetBalance() { return _AccountBalance; }
  //& Find
  static clsClient Find(string AccountNumber) {
    fstream File;
    File.open(_FileName(), ios::in);

    if (File.is_open()) {
      string Line;
      while (getline(File, Line)) {
        clsClient Client = _ConvertLineToClientObject(Line);

        if (Client.GetAccountNumber() == AccountNumber) {
          File.close();
          return Client;
        }
      }
      File.close();
    }
    return _GetEmptyClientObject();
  }

  static clsClient Find(string AccountNumber, string PinCode) {
    clsClient Client = Find(AccountNumber);
    return (Client._PinCode == PinCode) ? Client : _GetEmptyClientObject();
  };

  //? Validations
  static bool isClientExist(string AccountNumber) {
    return !(clsClient::Find(AccountNumber).IsEmpty());
  };
  bool isClientExist() { return isClientExist(this->_AccountNumber); };

  bool IsEmpty() { return (_Mode == enMode::EmptyMode); }

  //& Save
  enum enSaveResults {
    svFailedEmptyObject = 0,
    svSucceeded = 1,
    svFailedAccountNumberExists = 2,
  };

  enSaveResults save() {
    switch (_Mode) {
      case enMode::EmptyMode:
        if (IsEmpty()) { return enSaveResults::svFailedEmptyObject; }
        break;

        // * Update
      case enMode::Update:
        _Update();
        return enSaveResults::svSucceeded;
        break;

        // * Add
      case enMode::AddNewMode:
        if (clsClient::isClientExist(_AccountNumber)) {
          return enSaveResults::svFailedAccountNumberExists;
        }
        _Add();
        return enSaveResults::svSucceeded;
        break;
        return enSaveResults::svSucceeded;
        break;
    }
    return enSaveResults::svFailedEmptyObject;
  }

  bool Delete() {
    vector<clsClient> vClients = _LoadClientsDataFromFile();

    bool IsFound = false;
    for (clsClient& C : vClients) {
      if (C.GetAccountNumber() == _AccountNumber) {
        C._MarkForDelete = true;
        IsFound = true;
        break;
      }
    }
    _SaveClientsDataToFile(vClients);

    *this = _GetEmptyClientObject();

    return IsFound;
  }

  static clsClient AddNewClient(string AccountNumber) {
    return clsClient(enMode::AddNewMode, AccountNumber, "", "", "", "", "", 0);
  }

  static vector<clsClient> GetClientsList() {
    return _LoadClientsDataFromFile();
  }

  static vector<stTransfareData> GetTransfareList() {
    return _LoadTransfareLog();
  };

  bool Deposit(double Amount) {
    _AccountBalance += Amount;

    if (save() == svSucceeded) { return true; };

    return false;
  }
  bool Withdraw(double Amount) {
    if (Amount > _AccountBalance && Amount < 0) { return false; }

    _AccountBalance -= Amount;
    if (save() == svSucceeded) { return true; };

    return false;
  }
  bool Transfare(double Amount, clsClient& DestinationClient, string UserName) {
    if (Amount > _AccountBalance) { return false; }

    if (Withdraw(Amount)) {
      if (DestinationClient.Deposit(Amount)) {
        _RegisterTransfareLog(Amount, DestinationClient, UserName);
        return true;
      }
    }

    return false;
  }
};