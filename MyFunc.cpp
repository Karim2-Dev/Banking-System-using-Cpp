#include <iostream>
#include <ctime>
#include "includes/MyRandomLib.h"
#include "includes/MyArrFunctions.h"
#include "includes/MyInputLib.h"
#include "includes/MyNumsFunctions.h"
#include <iomanip>
#include <cmath>
#include <cctype>
#include <vector>
#include <fstream>
using namespace std;
struct stClientData
{
    string AccNum;
    string PinCode;
    string Name;
    string PhoneNumber;
    double AccountBalance;
};

int RowSum(int arr[3][3], short RowNumber)
{
    int Sum = 0;

    for (short j = 0; j < 3; j++)
    {
        Sum += arr[RowNumber][j];
    }
    return Sum;
}
void FillRow(int SumMatrix[3], int RowNumber, int Value)
{
    SumMatrix[RowNumber] = Value;
}

void PrintSumColArr(int MatrixArr[3][3])
{

    for (int i = 0; i < 3; i++)
    {
        int Sum = ColSum(MatrixArr, i);
        cout << "Col " << i + 1 << " Sum = " << Sum << endl;
    }
}
int ColSum(int arr[3][3], short ColNumber)
{
    int Sum = 0;
    for (int i = 0; i < 3; i++)
    {
        Sum += arr[i][ColNumber];
    }
    return Sum;
}

void PrintSumRowArray(int MatrixArr[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        int Sum = RowSum(MatrixArr, i);
        cout << "Row " << i + 1 << " Sum = " << Sum << endl;
    }
}

void SumMatrixColInArray(int arr[3][3], int ArrSum[3])
{
    for (short i = 0; i < 3; i++)
    {
        ArrSum[i] = ColSum(arr, i);
    }
}
void FillMatrixArrWithOrderdNumber(int Array[3][3])
{
    int counter = 0;
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {
            counter++;
            Array[i][j] = counter;
        }
    }
}

void TransposeMatrix(int Array[3][3], int TransposedArr[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            TransposedArr[j][i] = Array[i][j];
        }
    }
}

void CalcMatrix1MultiplyMatrix2(int Matrix1[3][3], int Matrix2[3][3], int Matrix[3][3])
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Matrix[i][j] = Matrix1[i][j] * Matrix2[i][j];
        }
    }
};
void PrintMiddleRow(int Array[3][3])
{
    cout << "\nMiddle row Of Matrix is: \n";
    for (int i = 0; i < 3; i++)
    {
        printf(" %0*d    ", 2, Array[1][i]);
    }
    cout << endl;
}
void PrintMiddleCol(int Array[3][3])
{
    cout << "\nMiddle Col Of Matrix is: \n";
    for (int i = 0; i < 3; i++)
    {
        printf(" %0*d    ", 2, Array[i][1]);
    }
    cout << endl;
}
int CalcSumMatrixArray(int arr[3][3])
{
    int Sum = 0;
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {

            Sum += arr[i][j];
        }
    }

    return Sum;
}
bool AreMatricesEqual(int arr[3][3], int arr2[3][3])
{
    return (CalcSumMatrixArray(arr) == CalcSumMatrixArray(arr2)) ? true : false;
}
bool AreMatricesTipical(int Arr1[3][3], int Arr2[3][3])
{
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {
            if (Arr1[i][j] != Arr2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
void PrintAreMatricesEqual(int arr[3][3], int arr2[3][3])
{
    if (AreMatricesEqual(arr, arr2))
    {
        cout << "Yes : matrices are equal.\n";
    }
    else
    {
        cout << "No : matrices are NOT equal.\n";
    }
}
int CalcSumMatrixArray(int arr[3][3])
{
    int Sum = 0;
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {

            Sum += arr[i][j];
        }
    }

    return Sum;
}
bool isMatrixIdentity(int arr[3][3])
{
    for (short i = 0; i < 3; i++)
    {
        // check for diagonals element
        if (arr[i][i] != 1)
            return false;

        for (short j = 0; j < 3; j++)
        {
            // check for rest elements
            if (i == j)
                continue;
            if (arr[i][j] != 0)
                return false;
        }
    }
    return true;
}
bool isMatrixScalar(int arr[3][3])
{
    int DaigonalValue = arr[0][0];
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {
            // check for diagonals element
            if ((i == j) && (arr[i][j] != DaigonalValue))
                return false;
            // check for rest elements
            if ((i != j) && (arr[i][j] != 0))
                return false;
        }
    }
    return true;
}
void FillMatrixWithRandomNums(int Array[3][3])
{
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {
            Array[i][j] = MyRand::RandomNumber(1, 10);
        }
    }
}
void PrintMatrixArr(int arr[3][3])
{
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {
            printf(" %0*d    ", 2, arr[i][j]);
        }
        cout << endl;
    }
}
short countNumberInMatrix(int arr[3][3], int Number)
{
    int counter = 0;

    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
            (Number == arr[i][j]) ? counter++ : counter;
    }
    return counter;
}
bool isSparceMatrix(int arr[3][3], short col, short row)
{
    int ZeroCount = countNumberInMatrix(arr, 0);
    return (ZeroCount >= col * row - ZeroCount);
}
void PrintIntresectedNumbersIn_2Matrices(int arr[3][3], int arr2[3][3], short col, short row)
{
    cout << "Intresected Numbers are: \n";
    for (short i = 0; i < col; i++)
    {
        for (short j = 0; j < row; j++)
        {
            int Number = arr[i][j];
            if (IsNumberInMatrixArr(arr2, col, row, Number))
            {
                cout << Number << "  ";
            }
        }
    }
}
void FillMatrixArrWithOrderdNumber(int Array[3][3])
{
    int counter = 0;
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {
            counter++;
            Array[i][j] = counter;
        }
    }
}
bool IsNumberInMatrixArr(int arr[3][3], short col, short row, int Number)
{

    for (short i = 0; i < col; i++)
    {
        for (short j = 0; j < row; j++)
            if (arr[i][j] == Number)
                return true;
    }
    return false;
}
void PrintMatrixArr(int arr[3][3])
{
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {
            printf(" %0*d    ", 2, arr[i][j]);
        }
        cout << endl;
    }
}

int MinNumInMatrix(int arr[3][3], short col, short row)
{
    int CurrentMinNum = arr[0][0];
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {
            if (CurrentMinNum > arr[i][j])
                CurrentMinNum = arr[i][j];
        }
        cout << endl;
    }
    return CurrentMinNum;
}
int MaxNumInMatrix(int arr[3][3], short col, short row)
{
    int CurrentMaxNum = arr[0][0];
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {
            if (CurrentMaxNum < arr[i][j])
                CurrentMaxNum = arr[i][j];
        }
        cout << endl;
    }
    return CurrentMaxNum;
}
bool isMatrixPalindrome(int arr[3][3], short row, short col)
{

    for (short i = 0; i < row; i++)
    {
        for (int j = 0; i < col / 2; j++)
        {
            if (arr[i][j] != arr[i][col - j - 1])
                return false;
        }
    }
    return true;
}
void FillFibonacciArr(int arr[], short length)
{

    for (int i = 2; i < length; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
}
void PrintFibonacciUsingLoop(short Number)
{
    int Prev1 = 0;
    int Prev2 = 1;
    int Feb = 1;

    cout << "FebNumber: \n";
    for (int i = 0; i < Number; i++)
    {
        cout << Feb << " ";

        Feb = Prev1 + Prev2;
        Prev1 = Prev2;
        Prev2 = Feb;
    }
}

void PrintFibonacciUsingRecursion(int Number, int Prev1, int Prev2)
{
    if (Number > 0)
    {
        int FebNum = Prev1 + Prev2;
        Prev2 = Prev1;
        Prev1 = FebNum;
        cout << FebNum << " ";
        PrintFibonacciUsingRecursion(Number - 1, Prev1, Prev2);
    }
}
void PrintFirstLetterOfEachWord(string Line)
{

    for (int i = 0; i < Line.length(); i++)
    {
        if (i == 0 || (Line[i - 1] == ' ' && Line[i] != ' '))
            cout << Line[i] << endl;
    }
}

string ToLowercaseOfEachFirstWord(string Line)
{

    for (int i = 0; i < Line.length(); i++)
    {
        if (i == 0 || (Line[i - 1] == ' ' && Line[i] != ' '))
            Line[i] = tolower(Line[i]);
    }

    return Line;
}

string toUpperCase(string Line)
{

    for (int i = 0; i < Line.length(); i++)
    {
        Line[i] = toupper(Line[i]);
    }

    return Line;
}
char InvertChar(char Character)
{
    return (isupper(Character)) ? toupper(Character) : tolower(Character);
}

string InvertAllLettersCase(string Line)
{
    for (int i = 0; i < Line.length(); i++)
    {
        Line[i] = InvertChar(Line[i]);
    }
    return Line;
}
int CountSmallLetters(string Line)
{
    int SmallLettersCounter = 0;
    for (int i = 0; i < Line.length(); i++)
    {
        if (islower(Line[i]))
        {
            SmallLettersCounter++;
        }
    }
    return SmallLettersCounter;
}
int CountCapitalLetters(string Line)
{
    int CapitalLettersCounter = 0;
    for (int i = 0; i < Line.length(); i++)
    {
        if (isupper(Line[i]))
        {
            CapitalLettersCounter++;
        }
    }
    return CapitalLettersCounter;
}
int CountLetter(string Line, char Char1, bool MatchCase = true)
{
    int CounterLetter = 0;

    for (short i = 0; i < Line.length(); i++)
    {
        if (MatchCase)
        {
            if (Line[i] == Char1)
                CounterLetter++;
        }
        else
        {
            if (tolower(Line[i]) == tolower(Char1))
                CounterLetter++;
        }
    }
    return CounterLetter;
}
char ReadChar(string Msg)
{

    char Character;
    cout << Msg << endl;
    cin >> Character;
    return Character;
}

bool isVowel(char Character)
{
    char lowerChar = tolower(Character);
    return ((lowerChar == 'a') || (lowerChar == 'o') || (lowerChar == 'u') || (lowerChar == 'e') || (lowerChar == 'i'));
}

int countVowel(string Line)
{
    int counter = 0;
    for (int i = 0; i < Line.length(); i++)
    {
        if (isVowel(Line[i]))
            counter++;
    }
    return counter;
}
void PrintVowelsInString(string Line)
{
    cout << "Vowels in String Are: \n";
    for (int i = 0; i < Line.length(); i++)
    {
        if (isVowel(Line[i]))
            cout << Line[i] << " ";
    }
    cout << endl;
}
string ReadString(string Msg)
{
    string UserString;
    cout << Msg << endl;

    getline(cin, UserString);

    return UserString;
}
void PrintEachWordInString(string Line)
{
    string delim = " ";
    cout << "\nYour string words are: \n\n";
    short pos = 0;
    string sWord;

    while ((pos = Line.find(delim)) != string::npos)
    {
        sWord = Line.substr(0, pos);

        if (sWord != "")
        {
            cout << sWord << endl;
        }

        Line.erase(0, pos + delim.length());
    }
    if (Line != "")
    {
        cout << Line << endl;
    }
}

string toLowerCase(string Line)
{

    for (int i = 0; i < Line.length(); i++)
    {
        Line[i] = tolower(Line[i]);
    }

    return Line;
}
vector<string> MySplit(string Line, string delim)
{
    vector<string> vMySplit;
    short Position;
    string sWord;

    while ((Position = Line.find(delim)) != string::npos)
    {
        sWord = Line.substr(0, Position);

        if (sWord != " ")
            vMySplit.push_back(sWord);

        Line.erase(0, Position + delim.length());
    }
    if (Line != "")
        vMySplit.push_back(Line);

    return vMySplit;
}
string TrimLeft(string Line)
{
    string delim = " ";

    int Position;

    if ((Position = Line.find_first_not_of(delim)) != string::npos)
        Line.erase(0, Position);
    else
        Line.clear();
    return Line;
}
string TrimRight(string Line)
{
    string delim = " ";

    int Position;

    if ((Position = Line.find_last_not_of(delim)) != string::npos)
        Line.erase(Position + 1);
    else
        Line.clear();

    return Line;
}
string MyTrim(string Line)
{
    return TrimRight(TrimLeft(Line));
}

string JoinString(string ArrString[], short Length, string seperator)
{
    string MyString = "";

    for (int i = 0; i < Length; i++)
        MyString += (i != Length - 1) ? ArrString[i] + seperator : ArrString[i];

    return MyString;
}
string JoinString(vector<string> vArrString, string seperator)
{
    string MyString = "";

    for (string &S1 : vArrString)
        MyString += S1 + seperator;

    return MyString.substr(0, MyString.length() - seperator.length());
}

short CountEachWordInString(string Line)
{
    short Counter = 0;
    short Position;
    string delim = " ";
    string sWord;

    while ((Position = Line.find(delim)) != string::npos)
    {
        sWord = Line.substr(0, Position);

        if (sWord != "")
            Counter++;

        Line.erase(0, Position + delim.length());
    }
    if (Line.length() != 0)
        Counter++;

    return Counter;
}

string ReverseWords(string Line)
{
    vector<string> vSplitString = MySplit(Line, " ");
    string ReversedString = "";

    vector<string>::iterator iter = vSplitString.end() - 1;

    while (iter >= vSplitString.begin())
    {
        ReversedString += (iter > vSplitString.begin()) ? *iter + " " : *iter;
        --iter;
    }
    return ReversedString;
}

string CostumReplaceWordInString(string Line, string Word, string ReplaceTo, bool IsSense = true)
{
    vector<string> vSplit = MySplit(Line, " ");
    vector<string>::iterator iter = vSplit.begin();

    while (iter < vSplit.end())
    {
        if (IsSense)
        {

            if (*iter == Word)
            {
                *iter = ReplaceTo;
            }
        }
        else
        {
            if (toLowerCase(*iter) == toLowerCase(Word))
                *iter = ReplaceTo;
        }

        iter++;
    }
    return JoinString(vSplit, " ");
}
string ReplaceWordInString(string Line, string Word, string ReplaceTo)
{
    short pos;
    while ((pos = Line.find(Word)) != string::npos)
        Line = Line.replace(pos, Word.length(), ReplaceTo);

    return Line;
}

string RemovePunctuationInString(string Line)
{
    for (int i = 0; i < Line.length(); i++)
    {
        if (ispunct(Line[i]))
            Line.erase(i, 1);
    }
    return Line;
}

string JoinString(vector<string> vArrString, string seperator)
{
    string MyString = "";

    for (string &S1 : vArrString)
        MyString += S1 + seperator;

    return MyString.substr(0, MyString.length() - seperator.length());
}

stClientData NewDataBank()
{
    stClientData AccData;
    AccData.AccNum = MyInputLib::ReadString("Enter Account Number? ");
    AccData.PinCode = MyInputLib::ReadString("Enter PinCode? ");
    cin.ignore(1, '\n');
    AccData.Name = MyInputLib::ReadLine("Enter Name? ");
    AccData.PhoneNumber = MyInputLib::ReadString("Enter Phone? ");
    AccData.AccountBalance = MyInputLib::ReadDoubleNum("Enter Account Balance? ");

    return AccData;
}

vector<string> MySplit(string Line, string delim)
{
    vector<string> vMySplit;
    short Position;
    string sWord;

    while ((Position = Line.find(delim)) != string::npos)
    {
        sWord = Line.substr(0, Position);

        if (sWord != " ")
            vMySplit.push_back(sWord);

        Line.erase(0, Position + delim.length());
    }
    if (Line != "")
        vMySplit.push_back(Line);

    return vMySplit;
}

string ConvertRecordToLine(stClientData stDataAccount)
{

    vector<string> vDataBankArr;
    vDataBankArr.push_back(stDataAccount.AccNum);
    vDataBankArr.push_back(stDataAccount.PinCode);
    vDataBankArr.push_back(stDataAccount.Name);
    vDataBankArr.push_back(stDataAccount.PhoneNumber);
    vDataBankArr.push_back(to_string(stDataAccount.AccountBalance));

    return JoinString(vDataBankArr, "#//#");
}

void ConvertLineToRecord(string Line, stClientData &stDataAccount)
{
    vector<string> SplitLine = MySplit(Line, "#//#");

    stDataAccount.AccNum = SplitLine[0];
    stDataAccount.PinCode = SplitLine[1];
    stDataAccount.Name = SplitLine[2];
    stDataAccount.PhoneNumber = SplitLine[3];
    stDataAccount.AccountBalance = stod(SplitLine[4]); // cast string to Double
}

void PrintClientData(stClientData &stDataAccount)
{
    cout << "Account Number  : " << stDataAccount.AccNum << endl;
    cout << "Pin Code        : " << stDataAccount.PinCode << endl;
    cout << "Name            : " << stDataAccount.Name << endl;
    cout << "Phone           : " << stDataAccount.PhoneNumber << endl;
    cout << "Account Balanced: " << stDataAccount.AccountBalance << endl;
}

void PrintBanckAccountData(vector<string> &vBankDataArr)
{
    cout << "\n\nClinet Record For Saving is:\n";

    string Line = JoinString(vBankDataArr, "#//#");

    cout << Line << endl;
}

vector<stClientData> ReadClientsData(string FileName)
{
    fstream File;
    vector<stClientData> vClientsData;

    File.open(FileName, fstream::in);

    if (File.is_open())
    {
        string Line;
        while (getline(File, Line))
        {
            stClientData stDataClient;
            ConvertLineToRecord(Line, stDataClient);
            vClientsData.push_back(stDataClient);
        }
        File.close();
    }
    return vClientsData;
}

void PrintHeaderDataClients(vector<stClientData> &ClientsData)
{
    cout << setw(75) << "Client List (" << ClientsData.size() << ") Clients(s)";
    cout << "\n______________________________________________________________________________________________________________________________________________________\n";
    cout << '\n';
    cout << "| " << left << setw(22) << "Account Number";
    cout << "| " << left << setw(17) << "Pin Code";
    cout << "| " << left << setw(42) << "Client Name";
    cout << "| " << left << setw(17) << "Phone";
    cout << "| " << left << setw(20) << "Balance";
    cout << "\n______________________________________________________________________________________________________________________________________________________\n";
}

void PrintClientsData(vector<stClientData> &ClientsData)
{

    PrintHeaderDataClients(ClientsData);
    for (stClientData &ClientData : ClientsData)
    {
        cout << "\n";
        cout << "| " << left << setw(22) << ClientData.AccNum;
        cout << "| " << left << setw(17) << ClientData.PinCode;
        cout << "| " << left << setw(42) << ClientData.Name;
        cout << "| " << left << setw(17) << ClientData.PhoneNumber;
        cout << "| " << left << setw(20) << ClientData.AccountBalance;
    }
    cout << "\n______________________________________________________________________________________________________________________________________________________\n";
}

void AddNewClient(string MyFileName)
{
    fstream File;

    stClientData vBankDataArr = NewDataBank();
    string LineData = ConvertRecordToLine(vBankDataArr);

    File.open(MyFileName, fstream::out | fstream::app);

    if (File.is_open())
    {
        File << LineData << endl;
    }
    File.close();
}

void AddClientsInFile(string MyFileName)
{
    char IsAddClient = 'y';
    do
    {
        system("clear");
        cout << "Adding New Client:\n\n";

        AddNewClient(MyFileName);

        cout << "\n\nClient Added Successfully, do you want to add more clients? [y/n]\n";
        cin >> IsAddClient;

    } while (tolower(IsAddClient) == 'y');
}

bool FindClient(vector<stClientData> &ClientsData, string AccNum, stClientData &stClient)
{

    for (stClientData &Client : ClientsData)
    {
        if (Client.AccNum == AccNum)
        {
            stClient = Client;
            cout << "\n\nThe Following are the client details: \n";
            PrintClientData(Client);
            return true;
        }
    }
    return false;
}
string convertNumberToText(long num)
{
    string TextOfNum = "";

    if (num < 0)
    {
        return TextOfNum;
    }

    // 1 to 9
    if (num < 20)
    {
        string TextsNum[] = {
            "",
            "one",
            "two",
            "three",
            "four",
            "five",
            "six",
            "seven",
            "eight",
            "nine",
            "ten",
            "eleven",
            "twelve",
            "thirteen",
            "fourteen",
            "fifteen",
            "sixteen",
            "seventeen",
            "eighteen",
            "nineteen"};
        TextOfNum = TextsNum[num];
        return TextOfNum;
    }
    // Twenty to Ninety
    if (num >= 20 && num < 100)
    {
        string TextsNum[10] = {
            "",
            "",
            "twenty",
            "thirty",
            "forty",
            "fifty",
            "sixty",
            "seventy",
            "eighty",
            "ninety",
        };
        TextOfNum = TextsNum[num / 10] + " " + convertNumberToText(num % 10);
        return TextOfNum;
    }
    // Handred to Thoursands
    if (num >= 100 && num < 1000)
    {
        TextOfNum = convertNumberToText(num / 100) + " handred " + convertNumberToText(num % 100);
        return TextOfNum;
    }
    // Thousands to Million
    if (num >= 1000 && num < 1000000)
    {
        // Number Of Thousands
        TextOfNum = convertNumberToText(num / 1000) + " thousand ";
        // Number Of Handred
        TextOfNum += convertNumberToText(num % 1000);
        return TextOfNum;
    }
    // Million to Billion
    if (num >= 1000000 && num < 1000000000)
    {
        // Number Of Thousands
        TextOfNum = convertNumberToText(num / 1000000) + " Million ";
        // Number Of Handred
        TextOfNum += convertNumberToText(num % 1000000);
        return TextOfNum;
    }
    if (num >= 1000000000 && num < 1000000000000)
    {
        // Number Of Thousands
        TextOfNum = convertNumberToText(num / 1000000000) + " billion ";
        // Number Of Handred
        TextOfNum += convertNumberToText(num % 1000000000);
        return TextOfNum;
    }

    return TextOfNum;
}
bool CheckIsLeapYear(short Year)
{
    return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
}

int NumberOfDays(int Year)
{
    return CheckIsLeapYear(Year) ? 366 : 365;
}

int NumberOfDays(short year, short Month)
{
    if (Month < 1 || Month > 12)
        return 0;

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

    return (Month == 2 && CheckIsLeapYear(year)) ? 29 : NumberOfDays[Month - 1];
}

bool CheckIsLeapYear(int Year)
{
    return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
}
int NumberOfHours(int Year)
{
    return NumberOfDays(Year) * 24;
}
int NumberOfHours(int Year, int Month)
{
    return NumberOfDays(Year, Month) * 24;
}
int NumberOfMinutes(int Year)
{
    return NumberOfHours(Year) * 60;
}
int NumberOfMinutes(int Year, int Month)
{
    return NumberOfHours(Year, Month) * 60;
}
int NumberOfSeconds(int Year)
{
    return NumberOfMinutes(Year) * 60;
}
int NumberOfSeconds(int Year, short Month)
{
    return NumberOfMinutes(Year, Month) * 60;
}
