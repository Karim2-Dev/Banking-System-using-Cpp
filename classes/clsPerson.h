#pragma once
#include <iostream>

#include "InterfaceCommuincation.h"
#include "clsString.h"

using namespace std;

class clsPerson : public InterfaceCommuincation {
  string _FirstName;
  string _LastName;
  string _Email;
  string _Phone;

 public:
  // Contstractor;
  clsPerson(string FirstName, string LastName, string Email, string Phone) {
    _FirstName = FirstName;
    _LastName = LastName;
    _Email = Email;
    _Phone = Phone;
  };

  //? Get:
  string FirstName() { return _FirstName; }
  string LastName() { return _LastName; }
  string FullName() { return _FirstName + " " + _LastName; }
  string Email() { return _Email; }
  string Phone() { return _Phone; }

  //! Set:
  void setFirstName(string FirstName) { _FirstName = FirstName; }
  void setLastName(string LastName) { _LastName = LastName; }
  void setEmail(string Email) { _Email = Email; }
  void setPhone(string Phone) { _Phone = Phone; }

  void SendEmail(string Title, string Body) {}

  void SendSMS(string Title, string Body) {}
  void SendFax(string Title, string Body) {}

  vector<string> splitFullName(string FullName) {
    return clsString::split(FullName, " ");
  };
};
