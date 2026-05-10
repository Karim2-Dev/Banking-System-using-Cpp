#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include "../../clsString.h"
using namespace std;

class clsCurrency {
  enum enMode {
    EmptyMode,
    UpdateMode,
  };
  string _Country;
  string _Code;
  string _Name;
  double _Rate;
  enMode _Mode;

  static string _CurrenciesFile() { return "data/currencies.txt"; }

  static string ConvertCurrencyObjectToLine(
    clsCurrency Currency, string Seperator = "#//#") {
    vector<string> vCurrencies;
    vCurrencies.push_back(Currency.country());
    vCurrencies.push_back(Currency.code());
    vCurrencies.push_back(Currency.name());
    vCurrencies.push_back(to_string(Currency.rate()));
    return clsString::JoinString(vCurrencies, Seperator);
  }

  static clsCurrency ConvertLineToCurrencyObject(
    string Line, string seperator = "#//#") {
    vector<string> vCurrencies = clsString::split(Line, seperator);

    return clsCurrency(UpdateMode, vCurrencies[0], vCurrencies[1],
      vCurrencies[2], stod(vCurrencies[3]));
  }

  static vector<clsCurrency> _LoadCurrenciesData() {
    fstream File;

    vector<clsCurrency> vCurrencies;

    File.open(_CurrenciesFile(), ios::in);

    if (File.is_open()) {
      string Line;
      while (getline(File, Line)) {
        vCurrencies.push_back(ConvertLineToCurrencyObject(Line));
      }

      File.close();
    }
    return vCurrencies;
  }

  void _SaveUpdateResultToFile(vector<clsCurrency>& vCurrencies) {
    fstream File;

    File.open(_CurrenciesFile(), ios::out);

    if (File.is_open()) {
      string Line;

      for (clsCurrency& Currency : vCurrencies) {
        File << ConvertCurrencyObjectToLine(Currency) << endl;
      }
      File.close();
    }
  };
  void _Update() {
    vector<clsCurrency> Currencies = _LoadCurrenciesData();

    for (clsCurrency& Currency : Currencies) {
      if (Currency.code() == _Code) {
        Currency = *this;
        break;
      }
    }

    _SaveUpdateResultToFile(Currencies);
  };

 public:
  //! Constructor
  clsCurrency(
    enMode Mode, string Country, string Code, string Name, double Rate) {
    _Country = Country;
    _Code = Code;
    _Name = Name;
    _Rate = Rate;
    _Mode = Mode;
  }
  //& Get
  string country() { return _Country; }
  string code() { return _Code; }
  string name() { return _Name; }
  double rate() { return _Rate; }

  static vector<clsCurrency> GetCurrenciesData() {
    return _LoadCurrenciesData();
  }

  //& Set
  void setCountry(string Country) { _Country = Country; }
  void setCode(string Code) { _Code = Code; }
  void setName(string Name) { _Name = Name; }
  void setRate(double Rate) { _Rate = Rate; }

  static clsCurrency GetEmptyCurrency() {
    return clsCurrency(EmptyMode, "", "", "", 0);
  }

  bool isEmptyCurrency() { return (_Mode == EmptyMode); }
  bool isCurrencyExist() { return !isEmptyCurrency(); }

  static clsCurrency FindByCode(string Code) {
    vector<clsCurrency> Currencies = _LoadCurrenciesData();

    for (clsCurrency& Currency : Currencies) {
      if (clsString::toLowerCaseEachWord(Code) ==
          clsString::toLowerCaseEachWord(Currency.code())) {
        return Currency;
      }
    }
    return GetEmptyCurrency();
  }

  static clsCurrency FindByCountry(string Country) {
    vector<clsCurrency> Currencies = _LoadCurrenciesData();

    for (clsCurrency& Currency : Currencies) {
      if (clsString::toLowerCaseEachWord(Country) ==
          clsString::toLowerCaseEachWord(Currency.country())) {
        return Currency;
      }
    }
    return GetEmptyCurrency();
  }

  enum enSaveResults {
    svFailedEmptyObject = 0,
    svSucceeded = 1,
    svFailedAlreadyExist = 2,
  };

  enSaveResults save() {
    switch (_Mode) {
      case EmptyMode: return enSaveResults::svFailedEmptyObject; break;

      case UpdateMode:
        _Update();
        return enSaveResults::svSucceeded;
        break;

      default: return enSaveResults::svFailedEmptyObject; break;
    }
  }
  float ConvertToUSD(float Amount) { return Amount / rate(); }

  float ConvertToOtherCurrency(float Amount, clsCurrency CurrencyToExChange) {
    return ConvertToUSD(Amount) * CurrencyToExChange.rate();
  }
};