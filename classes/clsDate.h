#pragma once
#include <ctime>
#include <iomanip>
#include <iostream>

#include "./clsString.h"

using namespace std;

class clsDate {
  int _year = 1900;
  int _month = 1;
  int _day = 1;

  //* Private Functions
 public:
  //! Constructor
  clsDate(int day, int month, int year) {
    _year = year;
    _month = month;
    _day = day;
  }
  clsDate(string Date) { *this = ConvertStringToDate(Date); }
  clsDate(short days, short year) { *this = ConvertDaysToDate(days, year); }

  clsDate() {}

  //* Convert String ToDate
  static clsDate ConvertStringToDate(string StringDate) {
    vector<string> DateSplit = clsString::split(StringDate, "/");

    short year = stoi(DateSplit[0]);
    short month = stoi(DateSplit[1]);
    short day = stoi(DateSplit[2]);

    return clsDate(year, month, day);
  }
  //* ==== Convert String ToDate ==== *//

  //! Get
  int year() { return _year; }
  int month() { return _month; }
  int day() { return _day; }
  //! Set
  void setYear(int Year) { _year = Year; }
  void setMonth(int Month) { _month = Month; }
  void setDay(int Day) { _day = Day; }

  //* Number of days of month
  static int GetNumberOfDaysOfMonth(short Month, short Year) {
    if (Month < 1 || Month > 12) { return 0; }

    short NumberOfDays[12] = {
      31,
      28,
      31,
      30,
      31,
      30,
      31,
      31,
      30,
      31,
      30,
      31,
    };

    return (Month == 2 && CheckIsLeapYear(Year)) ? 29 : NumberOfDays[Month - 1];
  }

  int GetNumberOfDaysOfMonth() { return GetNumberOfDaysOfMonth(_month, _year); }
  //* ==== Number of days of month ==== *//

  //* Number of days of Years
  static int GetTotalDaysOfYears(int year) {
    return year * 365 + year / 4 - year / 100 + year / 400;
  }

  int GetTotalDaysOfYears() { return GetTotalDaysOfYears(_year); }
  //* ==== Number of days of Years ==== *//

  //* Convert Days to Date
  static clsDate ConvertDaysToDate(short TotalDaysOfYear, short Year) {
    short day;
    short month;

    for (int i = 1; i <= 12; i++) {
      int MonthLength = GetNumberOfDaysOfMonth(Year, i);

      if (TotalDaysOfYear <= MonthLength) {
        day = TotalDaysOfYear;
        month = i;
        break;
      } else {
        TotalDaysOfYear -= MonthLength;
      }
    };
    return clsDate(day, month, Year);
  }
  //* Convert Days to Date

  //* Check Is Leap Year
  static bool CheckIsLeapYear(short Year) {
    return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
  }
  bool CheckIsLeepYear() { return CheckIsLeapYear(_year); }
  //* ==== Check Is Leap Year ==== *//

  //* Total Days From Beginning Year
  int TotalDaysFromBeginningYear() {
    short counter = 0;
    for (int i = 1; i < _month; i++) {
      counter += GetNumberOfDaysOfMonth(_month, i);
    }
    counter += _day;
    return counter;
  }
  //* ==== Total Days From Beginning Year ==== *//

  //* GetDayOrder *//
  static short GetDayOrder(short Year, short Month, short Day) {
    short a = (14 - Month) / 12;
    short y = Year - a;
    short m = Month + (12 * a) - 2;

    short d = (5 + Day + y + (y / 4) + (31 * m / 12)) % 7;

    d = (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;

    return d;
  }

  short GetDayOrder() { return GetDayOrder(_year, _month, _day); }
  //* ==== GetDayOrder ==== *//

  //* GetDayOrder *//
  static string GetDayName(short orderDay) {
    string DaysShort[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    return DaysShort[orderDay];
  }
  string GetDayName() { return GetDayName(GetDayOrder()); }
  //* ==== GetDayOrder ==== *//

  //* Get Day Order *//
  static string GetMonthDay(short Month) {
    string Months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
      "Sep", "Oct", "Nov", "Dec"};

    return Months[Month - 1];
  }
  string GetMonthDay() { return GetMonthDay(_month); }
  //* ==== Get Day Order ==== *//

  //* is Last/First Days Of Month *//
  static bool isLastDayInMonth(clsDate& Date) {
    return (GetNumberOfDaysOfMonth(Date.month(), Date.year()) > Date.day())
             ? false
             : true;
  }
  static bool isFirstDayInMonth(int Day) { return Day == 1; }

  bool isLastDayInMonth() { return isLastDayInMonth(*this); };
  bool isFirstDayInMonth() { return isFirstDayInMonth(this->_day); };
  //* ==== is Last/First Days Of Month ==== *//

  //* is Last Month In Year *//
  static bool isLastMonthInYear(int Month) { return (Month == 12); }
  static bool isFirstMonthInYear(int Month) { return (Month == 1); }

  bool isLastMonthInYear() { return isLastMonthInYear(this->_month); };
  bool isFirstMonthInYear() { return isFirstMonthInYear(this->_month); };
  //* ==== is Last Month In Year ==== *//

  //* DiffOfDays *//
  static int DiffOfDays(
    clsDate Date1, clsDate Date2, bool IsIncludeLastDay = false) {
    int Counter = 0;
    short swapVlag = 1;
    if (!IsDate1BeforeDate2(Date1, Date2)) {
      swap(Date1, Date2);
      swapVlag = -1;
    }
    while (IsDate1BeforeDate2(Date1, Date2)) {
      AddDays(Date1, 1);
      Counter++;
    }

    return (IsIncludeLastDay) ? ++Counter * swapVlag : Counter * swapVlag;
  }
  int DiffOfDays(clsDate Date2, bool IsIncludeLastDay = false) {
    return DiffOfDays(*this, Date2, IsIncludeLastDay);
  }
  //* ==== DiffOfDays ==== *//

  //* GetDayOrder *//

  //* ==== GetDayOrder ==== *//

  //* Add Days To Date *//
  static clsDate AddDays(clsDate Date, int DaysCount) {
    if (DaysCount < 0) { return Date; }

    DaysCount += Date.day();

    while (DaysCount) {
      int MonthLength = GetNumberOfDaysOfMonth(Date.month(), Date.year());

      if (DaysCount <= MonthLength) {
        Date.setDay(DaysCount);
        break;

      } else {
        if (Date.month() < 12) {
          Date.setMonth(Date.month() + 1);
        } else {
          Date.setMonth(1);
          Date.setYear(Date.year() + 1);
        }

        DaysCount -= MonthLength;
      }
    }
    return Date;
  }
  void AddDaysToDate(int DaysCount) { *this = AddDays(*this, DaysCount); }
  //* ==== Add Days To Date ==== *//

  //* Print  *//
  //* ==== GetDayOrder ==== *//

  //! Prints

  //* Fromat Date *//
  static string FormatDate(clsDate Date) {
    return to_string(Date.day()) + "/" + to_string(Date.month()) + "/" +
           to_string(Date.year());
  };
  string FormatDate() { return FormatDate(*this); }
  //* ==== Format Date ==== *//

  //* Print Date *//
  static void print(clsDate Date) { cout << FormatDate(Date) << endl; }
  static void print(string sDate) { print(ConvertStringToDate(sDate)); }
  void print() { print(*this); }
  //* ==== Print Date ==== *//

  //* Print Date *//
  static void printMonthCalendar(short Year, short Month) {
    // Month's Day Lenght
    short NumberOfDays = GetNumberOfDaysOfMonth(Year, Month);
    // Month Start In Day:
    short DayOrder = GetDayOrder(Year, Month, 1);

    short DayCounter = 1;
    short CounterLine = DayOrder + 1;

    cout << "\n";

    cout << "  _______________" << GetMonthDay(Month)
         << "_______________  \n\n";
    // Print Days Name
    for (int i = 0; i < 7; i++) { printf("  %s", GetDayName(i).c_str()); }
    cout << "\n  ";

    // بتدي مسافات لحد ميوصل لليوم الي هبدا فيه الشهر
    for (int i = 0; i < DayOrder; i++) { cout << "     "; }

    // Print Days

    while (DayCounter <= NumberOfDays) {
      cout << setw(3) << DayCounter << "  ";

      if (CounterLine == 7) {
        cout << "\n  ";
        CounterLine = 0;
      }

      DayCounter++;
      CounterLine++;
    }
    cout << "\n  _________________________________\n";
  }
  void printMonthCalendar() { printMonthCalendar(this->_year, this->_month); }
  //* ==== Print Date ==== *//

  //* Print Date *//
  static void printYearCalendar(short Year) {
    printf("\n  _________________________________");
    printf("\n          calendar - %d        ", Year);
    printf("\n  _________________________________\n");

    for (int i = 1; i <= 12; i++) { printMonthCalendar(Year, i); }
  }
  void printYearCalendar() { printYearCalendar(this->_year); }
  //* ==== Print Date ==== *//

  //* Print Date *//

  //* ==== Print Date ==== *//

  //! Booleans
  //* is Date1 Equal Date2 *//
  static bool isDate1EqualDate2(clsDate Date1, clsDate Date2) {
    return (Date1.year() == Date2.year()
              ? (Date1.month() == Date2.month() ? (Date1.day() == Date2.day())
                                                : false)
              : false);
  }
  bool isDate1EqualDate2(clsDate& Date) {
    return isDate1EqualDate2(*this, Date);
  }
  //* ==== is Date1 Equal Date2 ==== *//

  //* Is Date1 Before Date2 *//
  static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {
    return (Date1.year() < Date2.year())
             ? true
             : (Date1.year() == Date2.year()
                   ? (Date1.month() < Date2.month()
                         ? true
                         : (Date1.month() == Date2.month()
                               ? Date1.day() < Date2.day()
                               : false))
                   : false);
  }
  bool IsDate1BeforeDate2(clsDate& Date) {
    return IsDate1BeforeDate2(*this, Date);
  }
  //* ==== Is Date1 Before Date2 ==== *//

  //* Print Date *//
  static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {
    return !IsDate1BeforeDate2(Date1, Date2) &&
           !isDate1EqualDate2(Date1, Date2);
  }
  bool IsDate1AfterDate2(clsDate& Date2) {
    return IsDate1AfterDate2(*this, Date2);
  }
  //* ==== Print Date ==== *//

  //* Is Date Valid *//
  static bool IsDateValid(clsDate Date) {
    if (Date.month() < 1 || Date.month() > 12) { return false; }

    if (Date.day() < 1 ||
        Date.day() > GetNumberOfDaysOfMonth(Date.year(), Date.month())) {
      return false;
    }

    return true;
  }
  bool IsDateValid() { return IsDateValid(*this); }
  //* ==== Is Date Valid==== *//

  static clsDate GetCurrentDate() {
    time_t now = time(0);             // الوقت الحالي
    tm* LocalTime = localtime(&now);  // تحويله لوقت محلي

    int Day = LocalTime->tm_mday;
    int Month = LocalTime->tm_mon + 1;
    int year = 1900 + LocalTime->tm_year;
    return clsDate(Day, Month, year);
  }
  static string GetCurrentTime() {
    time_t now = time(0);
    tm* LocalTime = localtime(&now);

    string Hour = to_string(LocalTime->tm_hour);
    string Minute = to_string(LocalTime->tm_min);
    string Second = to_string(LocalTime->tm_sec);

    return Hour + ":" + Minute + ":" + Second;
  }
  static string DateAndTimetoString() {
    return FormatDate(GetCurrentDate()) + " - " + GetCurrentTime();
  }
};