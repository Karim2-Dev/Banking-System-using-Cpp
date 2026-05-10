#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include "../../clsDate.h"
#include "../../clsPerson.h"
#include "../Global.h"

using namespace std;

class clsUser : public clsPerson {
  enum enMode {
    EmptyMode,
    Update,
    Add,
  };

  short _Permissions;
  string _Password;
  enMode _Mode;
  string _Username;

  bool _isMarkForDelete = false;

  //! Files
  static string _UserFile() { return "data/users.txt"; };
  static string _RegistersData() { return "data/Registers.txt"; }

  static clsUser _GetEmptyUserObject() {
    return clsUser(EmptyMode, "", "", "", "", "", "", 0);
  }

  static clsUser _ConvertLineToUserObject(
    string Line, string seperator = "#//#") {
    vector<string> vClientData;

    vClientData = clsString::split(Line, seperator);

    return clsUser(enMode::Update, vClientData[0], vClientData[1],
      vClientData[2], vClientData[3], vClientData[4],
      clsString::DecryptText(vClientData[5], 2), stoi(vClientData[6]));
  };

  static string _ConvertUserObjectToFile(
    clsUser User, string seperator = "#//#") {
    vector<string> vUsersData;

    vUsersData.push_back(User.FirstName());
    vUsersData.push_back(User.LastName());
    vUsersData.push_back(User.Username());
    vUsersData.push_back(User.Email());
    vUsersData.push_back(User.Phone());
    vUsersData.push_back(clsString::EncryptText(User.Password(), 2));
    vUsersData.push_back(to_string(User.Permissions()));

    return clsString::JoinString(vUsersData, seperator);
  }

  string _ConvertRegisterDataToFile(string seperator = "#//#") {
    vector<string> RegisterData;

    RegisterData.push_back(clsDate::DateAndTimetoString());
    RegisterData.push_back(_Username);
    RegisterData.push_back(clsString::EncryptText(_Password, 2));
    RegisterData.push_back(to_string(_Permissions));

    return clsString::JoinString(RegisterData, seperator);
  }
  static vector<string> _ConverLineToRegisterData(
    string Line, string seperator = "#//#") {
    vector<string> SplitData = clsString::split(Line, seperator);

    SplitData[2] = clsString::DecryptText(SplitData[2],2);

    return SplitData;
  }

  static vector<clsUser> _LoadUsersDataFromFile() {
    vector<clsUser> vUsers;

    fstream File;

    File.open(_UserFile(), ios::in);  //& READ MODE

    if (File.is_open()) {
      string Line;
      while (getline(File, Line)) {
        vUsers.push_back(_ConvertLineToUserObject(Line));
      }

      File.close();
    }
    return vUsers;
  }

  static vector<vector<string>> _LoadRegisterDataFromFile() {
    fstream File;
    vector<vector<string>> RegisterData;

    File.open(_RegistersData(), ios::in);

    if (File.is_open()) {
      string Line;
      while (getline(File, Line)) {
        RegisterData.push_back(_ConverLineToRegisterData(Line));
      }

      File.close();
    }
    return RegisterData;
  };

  void _SaveUsersDataToFile(vector<clsUser> vUsers) {
    fstream File;

    File.open(_UserFile(), ios::out);

    if (File.is_open()) {
      //^ Save Clients
      for (clsUser& user : vUsers) {
        if (!user._isMarkForDelete) {
          File << _ConvertUserObjectToFile(user) << endl;
        }
      }
      File.close();
    }
  }

  void _AddUserDataToFile() {
    fstream File;

    File.open(_UserFile(), ios::app);

    if (File.is_open()) {
      //^ Save Client
      File << _ConvertUserObjectToFile(*this) << endl;
      File.close();
    }
  }

  void _Update() {
    vector<clsUser> vUsers = _LoadUsersDataFromFile();

    for (clsUser& User : vUsers) {
      if (User.Username() == _Username) {
        User = *this;
        break;
      }
    }

    _SaveUsersDataToFile(vUsers);
  }

  void _Add() {
    vector<clsUser> vUsers = _LoadUsersDataFromFile();
    vUsers.push_back(*this);
    _AddUserDataToFile();
  }

 public:
  //! Constructor
  clsUser(enMode Mode, string FirstName, string LastName, string Username,
    string Email, string Phone, string Password, short Permissions)
    : clsPerson(FirstName, LastName, Email, Phone) {
    _Username = Username;
    _Permissions = Permissions;
    _Password = Password;
    _Mode = Mode;
  };

  void setPermissions(short Permissions) { _Permissions = Permissions; }
  void setPassword(string Password) { _Password = Password; }
  void setUsername(string userName) { _Username = userName; }

  short Permissions() { return _Permissions; }
  string Password() { return _Password; }
  string Username() { return _Username; }

  //& Save
  enum enSaveResults {
    svFailedEmptyObject = 0,
    svSucceeded = 1,
    svFailedAlreadyExist = 2,
  };

  enSaveResults save() {
    switch (_Mode) {
      case EmptyMode: return enSaveResults::svFailedEmptyObject; break;

      case Update:
        _Update();
        return enSaveResults::svSucceeded;
        break;

      case Add:
        if (isUserExist(_Username)) {
          return enSaveResults::svFailedAlreadyExist;
        } else {
          _Add();
          return enSaveResults::svSucceeded;
        }

      default: return enSaveResults::svFailedEmptyObject; break;
    }
  }

  static clsUser Find(string Username) {
    fstream File;
    File.open(_UserFile(), ios::in);

    if (File.is_open()) {
      string Line;
      while (getline(File, Line)) {
        clsUser User = _ConvertLineToUserObject(Line);
        if (User.Username() == Username) {
          File.close();
          return User;
        }
      }
      File.close();
    }
    return _GetEmptyUserObject();
  }
  bool IsEmpty() { return (_Mode == enMode::EmptyMode); }

  static clsUser Find(string Username, string Password) {
    clsUser User = Find(Username);
    return (User.Password() == Password) ? User : _GetEmptyUserObject();
  }

  static clsUser NewUser() {
    return clsUser(enMode::Add, "", "", "", "", "", "", 0);
  }

  static bool isUserExist(string Username) {
    return !(Find(Username).IsEmpty());
  }

  bool Delete() {
    bool IsFound = false;

    vector<clsUser> vUsers = _LoadUsersDataFromFile();

    for (clsUser& User : vUsers) {
      if (User.Username() == _Username) {
        _isMarkForDelete = true;
        IsFound = true;
        break;
      }
    }
    save();

    return IsFound;
  }
  enum enPermission {
    enClientListAccess = 1,
    enAddNewClientAccess = 2,
    enDeleteClientAccess = 4,
    enUpdateClientAccess = 8,
    enFindClientAccess = 16,
    enTransactionsAccess = 32,
    enManageUsersAccess = 64,
    enLoginRegisterAccess = 128,
    enCurrencyExchangeAccess = 256,
  };
  static vector<clsUser> GetUsersList() { return _LoadUsersDataFromFile(); }

  bool IsAccessPage(enPermission Page) {
    return Permissions() == -1 || Permissions() & Page;
  }
  void saveRegisterData() {
    fstream File;

    File.open(_RegistersData(), ios::app);

    if (File.is_open()) {
      //^ Save Clients
      File << _ConvertRegisterDataToFile() << endl;

      File.close();
    }
  }
  static vector<vector<string>> GetRegiserList() {
    return _LoadRegisterDataFromFile();
  }
};