#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include <fstream>
#include <vector>
#include <iomanip>


using namespace std;

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNew = 2, Delete = 3};
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }
    static string _ConvertObjectToLine(clsBankClient ClientInfo, string Seperator = "#//#")
    {
        string LineInfo;
       
        LineInfo = ClientInfo.FirstName + Seperator
            + ClientInfo.LastName + Seperator
            + ClientInfo.Phone + Seperator
            + ClientInfo.Email + Seperator
            + ClientInfo.GetAccountNumber() + Seperator
            + ClientInfo.PinCode + Seperator
            + to_string(ClientInfo._AccountBalance);
        return LineInfo;
    }

    bool _IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    void _MarkAccountToDelete(vector <clsBankClient>& vClientInfo, string AccountNum)
    {
        for (clsBankClient& Client : vClientInfo)
        {
            if (Client.GetAccountNumber() == AccountNum)
                Client._MarkForDelete = true;
        }
    }


    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
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


    static clsBankClient UpdateClientDataInVector(vector <clsBankClient>& vFileData, string AccountNumber)
    {
        for (clsBankClient& Client : vFileData)
        {
            if (Client.GetAccountNumber() == AccountNumber)
            {
                GetInfoFromUser(Client);
                return Client;
            }
        }
        return _GetEmptyClientObject();
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        return (!Client1._IsEmpty());
    }

    static  clsBankClient GetAddNewClient(string AccountNumber) {
        return clsBankClient(enMode::AddNew, "", "", "", "", AccountNumber, "", 0);
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
                clsBankClient Client = _ConvertLinetoClientObject(Line);
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

    static vector <clsBankClient> GetDataFromFileToVector()
    {
        vector <clsBankClient> vFileData;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if(!Line.empty())
                vFileData.push_back(_ConvertLinetoClientObject(Line));
            }
            MyFile.close();
        }
        else
            cout << "The file can't open!\n";

        return vFileData;
    }

    static void GetInfoFromUser(clsBankClient& Client)
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

    static void AddNewClientToFill(clsBankClient Client)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::app);

        if (MyFile.is_open())
        {
            MyFile << _ConvertObjectToLine(Client) << endl;
            MyFile.close();
        }
        else
            cout << "The file can't open!\n";
    }

    static void UploadDataToFile(vector <clsBankClient>& vFileData)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);

        if (MyFile.is_open())
        {
            string Line;
            for (clsBankClient& ClientInfo : vFileData)
            {
                if(ClientInfo._MarkForDelete == false)
                {
                    MyFile << _ConvertObjectToLine(ClientInfo) << endl;
                }
            }
            MyFile.close();
        }
        else
            cout << "The file can't open!\n";
    }

    
    static  void DeleteClientFromFile(string AccountNumber)
    {
        vector <clsBankClient> vFileData = GetDataFromFileToVector();

        for (clsBankClient& Client : vFileData)
        {
            if (Client.GetAccountNumber() == AccountNumber)
            {
                Client._MarkForDelete = true;
                UploadDataToFile(vFileData);
                Client = _GetEmptyClientObject();
                break;
            }
        }

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
      vector<clsBankClient> vFileData = GetDataFromFileToVector();

      system("cls");
      PrintBalanceInfoHeader(vFileData.size());

      for (clsBankClient& Client : vFileData)
      {
          PrintBalanceInfo(Client);
          cout << endl;
      }
      cout << "\n____________________________________________________________________________________________________________________\n\n\n";
      cout << "\t\t\t\t Total Balance = " << CalculateTotalBalance(vFileData) << "\n\n";
  }

};
