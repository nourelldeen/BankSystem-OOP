#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include <fstream>
#include <vector>
#include <iomanip>
#include "clsUtil.h"


using namespace std;

class clsBankClient : public clsPerson
{
private:
    enum enMode { enEmptyMode = 0, enUpdateMode = 1, enAddNew = 2, enDelete = 3 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _IsDeleted = false;


    void _MarkAccountToDelete(vector <clsBankClient>& vClientInfo, string AccountNum)
    {
        for (clsBankClient& Client : vClientInfo)
        {
            if (Client.GetAccountNumber() == AccountNum)
                Client._IsDeleted = true;
        }
    }


    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> _vClientData;
        _vClientData = clsString::Split(Line, Seperator);
        if (_vClientData.size() >= 7)
        {
            return clsBankClient(
                enMode::enUpdateMode,
                _vClientData[0],                 // FirstName
                _vClientData[1],                 // LastName
                _vClientData[2],                 // Email  
                _vClientData[3],                 // Phone  
                _vClientData[4],                 // AccountNumber
                _vClientData[5],                 // PinCode
                stof(_vClientData[6])            // AccountBalance as float
            );
        }
        else
            cout << "Error in Data File\n";

        return _GetEmptyClientObject();

    }

    static string _ConvertObjectToLine(clsBankClient ClientInfo, string Seperator = "#//#")
    {
        string LineInfo;

        LineInfo =
            ClientInfo.FirstName + Seperator
            + ClientInfo.LastName + Seperator
            + ClientInfo.Email + Seperator
            + ClientInfo.Phone + Seperator
            + ClientInfo.GetAccountNumber() + Seperator
            + ClientInfo.PinCode + Seperator
            + to_string(ClientInfo.AccountBalance);
        return LineInfo;
    }

    static vector <clsBankClient> _GetDataFromFileToVector()
    {
        vector <clsBankClient> vFileData;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (!Line.empty())
                    vFileData.push_back(_ConvertLinetoClientObject(Line));
            }
            MyFile.close();
        }
        else
            cout << "The file can't open!\n";

        return vFileData;
    }

    static void _UploadDataToFile(vector <clsBankClient>& vFileData)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);

        if (MyFile.is_open())
        {
            string Line;
            for (clsBankClient& ClientInfo : vFileData)
            {
                if (ClientInfo._IsDeleted == false)
                {
                    MyFile << _ConvertObjectToLine(ClientInfo) << endl;
                }
            }
            MyFile.close();
        }
        else
            cout << "The file can't open!\n";
    }

    static void _GetInfoFromUser(clsBankClient& Client)
    {

        cout << "Please enter First Name: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "Please enter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "Please enter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "Please enter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "Please enter Pin Code: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Please enter Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();

    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _GetDataFromFileToVector();

        for (clsBankClient& Client : _vClients)
        {
            if (Client.GetAccountNumber() == GetAccountNumber())
            {
                Client = *this;
                break;
            }
        }
        _UploadDataToFile(_vClients);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertObjectToLine(*this));
    }
    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
        else
            cout << "The File Can't Open!\n";

    }
   
    bool _Delete()
    {
        vector <clsBankClient> vFileData = _GetDataFromFileToVector();

        for (clsBankClient& Client : vFileData)
        {
            if (Client.GetAccountNumber() == _AccountNumber)
            {
                Client._IsDeleted = true;
                break;
            }
        }
        _UploadDataToFile(vFileData);

        *this = _GetEmptyClientObject();

        return true;
    }

    static clsBankClient _GetEmptyClientObject()
        {
            return clsBankClient(enMode::enEmptyMode, "", "", "", "", "", "", 0);
        }
   
    static  clsBankClient _GetAddNewClient(string AccountNumber) {
        return clsBankClient(enMode::enAddNew, "", "", "", "", AccountNumber, "", 0);
    }


public:
    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    string GetAccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        return (!Client1.IsEmpty());
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::enEmptyMode);
    }

    enum enSaveResults { svFaildEmptyObject = 0,
                         svSucceeded = 1,
                         svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::enEmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
        }

        case enMode::enUpdateMode:
        {
            _Update();

            return enSaveResults::svSucceeded;

            break;
        }
        case enMode::enAddNew:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::enUpdateMode;
                return enSaveResults::svSucceeded;
            }
        }


        }

    }

  static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.GetAccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();

        }

        return _GetEmptyClientObject();
    }
  static clsBankClient Find(string AccountNumber, string PinCode)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client =  _ConvertLinetoClientObject(Line);
                if (Client.GetAccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

  static void UpdateClientData()
  {
      string AccountNumber = "";

      cout << "Please Enter The Account Number?\n";
      AccountNumber = clsInputValidate::ReadString();

      while (!clsBankClient::IsClientExist(AccountNumber))
      {
          cout << "The Client Is NOT Exist! Please try again?\n";
          AccountNumber = clsInputValidate::ReadString();
      }

      clsBankClient Client = clsBankClient::Find(AccountNumber);
      Client.Print();

      char Sure = 'N';

      cout << "\nAre you sure you want to update this account?  Y/N: ";
      cin >> Sure;
   
          cout << "\n\nUpdate Client Info:";
          cout << "\n____________________\n";
          _GetInfoFromUser(Client);
   
          enSaveResults SaveResult;
          SaveResult = Client.Save();

          switch (SaveResult)
          {
          case  clsBankClient::enSaveResults::svSucceeded:
          {
              cout << "\nAccount Updated Successfully :-)\n";
              Client.Print();
              break;
          }
          case clsBankClient::enSaveResults::svFaildEmptyObject:
          {
              cout << "\nError account was not saved because it's Empty";
              break;

          }

          }

  }

  static void AddNewClient()
  {

      string AccountNumber;
      cout << "Please enter the AccountNumber?\n";
      AccountNumber = clsInputValidate::ReadString();

      while (clsBankClient::IsClientExist(AccountNumber))
      {
          cout << "The Client Is Already Exist! Please Choose another PinCode:";
          AccountNumber = clsInputValidate::ReadString();
      }

      clsBankClient NewClient = _GetAddNewClient(AccountNumber);
      _GetInfoFromUser(NewClient);

      clsBankClient::enSaveResults SaveResult;
      SaveResult = NewClient.Save();

      switch (SaveResult)
      {
      case  clsBankClient::enSaveResults::svSucceeded:
      {
          cout << "\nAccount Addeded Successfully :-)\n";
          NewClient.Print();
          break;
      }
      case clsBankClient::enSaveResults::svFaildEmptyObject:
      {
          cout << "\nError account was not saved because it's Empty";
          break;

      }
      case clsBankClient::enSaveResults::svFaildAccountNumberExists:
      {
          cout << "\nError account was not saved because account number is used!\n";
          break;

      }
      }

  }

  static void DeleteClient()
  {
      string AccountNumber;
      cout << "Please enter the AccountNumber?\n";
      AccountNumber = clsInputValidate::ReadString();

      while (!clsBankClient::IsClientExist(AccountNumber))
      {
          cout << "The Client Is NOT Exist! Please try again?\n";
          AccountNumber = clsInputValidate::ReadString();
      }
      clsBankClient Client = clsBankClient::Find(AccountNumber);
      Client.Print();

      cout << "\nAre you sure you want to delete this account?  Y/N: ";
      char Sure = 'N';
      cin >> Sure;

      if (toupper(Sure) == 'Y')
      {
          if (Client._Delete())
          {
              cout << "\nClient Deleted Successfully :)\n";
              Client.Print();
          }
          else
          {
              cout << "\nError Client Was not Deleted\n";
          }
          
      }
  }

  static vector <clsBankClient> GetClientsList()
  {
      return _GetDataFromFileToVector();
  }

  static void PrintBalanceInfoHeader(size_t ClientsNum)
  {
      cout << "\t\t\t\t\t\t Client List (" << ClientsNum << ") Client(s). \n\n";
      cout << "____________________________________________________________________________________________________________________\n\n";
      cout << setw(20) << left << "| Account Number";
      cout << setw(40) << left << "| Client Name";
      cout << setw(20) << left << "| Balance";
      cout << "\n____________________________________________________________________________________________________________________\n\n";
  }

  static void PrintBalanceInfo(clsBankClient Client)
  {
      cout << "| " << setw(18) << Client.GetAccountNumber();
      cout << "| " << setw(38) << Client.FullName();
      cout << "| " << setw(18) << Client.GetAccountBalance();
  }

  static float CalculateTotalBalance(vector<clsBankClient>& vClientInfo)
  {
      float TotalBalance = 0.0;
      for (clsBankClient& Client : vClientInfo)
          TotalBalance += Client.GetAccountBalance();
      return TotalBalance;
  }

  static void PrintClientBalanceList()
  {
      vector<clsBankClient> vFileData = _GetDataFromFileToVector();

      system("cls");
      PrintBalanceInfoHeader(vFileData.size());

      for (clsBankClient& Client : vFileData)
      {
          PrintBalanceInfo(Client);
          cout << endl;
      }
      float TotalBalances = CalculateTotalBalance(vFileData);
      cout << "\n____________________________________________________________________________________________________________________\n\n\n";
      cout << "\t\t\t\t Total Balance = " << TotalBalances << "\n\n";
      cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";

  }

   void Print()
  {
      cout << "\nClient Card:";
      cout << "\n___________________";
      cout << "\nFirstName   : " << FirstName;
      cout << "\nLastName    : " << LastName;
      cout << "\nFull Name   : " << FullName();
      cout << "\nEmail       : " << Email;
      cout << "\nPhone       : " << Phone;
      cout << "\nAcc. Number : " << GetAccountNumber();
      cout << "\nPin Code    : " << GetPinCode();
      cout << "\nBalance     : " << GetAccountBalance();
      cout << "\n___________________\n";
  }

};
