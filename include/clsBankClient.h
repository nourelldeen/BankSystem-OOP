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
   
    static clsBankClient _GetEmptyClientObject()
        {
            return clsBankClient(enMode::enEmptyMode, "", "", "", "", "", "", 0);
        }
   
    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
        string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += GetAccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.GetAccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    struct stTrnsferLogRecord;
    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTrnsferLogRecord TrnsferLogRecord;

        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;

    }
    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

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

    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float  Amount;
        float  srcBalanceAfter;
        float  destBalanceAfter;
        string UserName;
    };

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
    static  clsBankClient GetAddNewClientObject(string AccountNumber) {
        return clsBankClient(enMode::enAddNew, "", "", "", "", AccountNumber, "", 0);
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

  bool Delete()
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

  static vector <clsBankClient> GetClientsList()
  {
      return _GetDataFromFileToVector();
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
   void Deposit(double Amount)
   {
       _AccountBalance += Amount;
       Save();
   }


   bool Withdraw(double Amount)
   {
       if (Amount > _AccountBalance)
       {
           return false;
       }
       else
       {
           _AccountBalance -= Amount;
           Save();
           return true;
       }

   }
   bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
   {
       if (Amount > AccountBalance)
       {
           return false;
       }

       Withdraw(Amount);
       DestinationClient.Deposit(Amount);
       _RegisterTransferLog(Amount, DestinationClient, UserName);

       return true;
   }
   static  vector <stTrnsferLogRecord> GetTransfersLogList()
   {
       vector <stTrnsferLogRecord> vTransferLogRecord;

       fstream MyFile;
       MyFile.open("TransferLog.txt", ios::in);//read Mode

       if (MyFile.is_open())
       {

           string Line;

           stTrnsferLogRecord TransferRecord;

           while (getline(MyFile, Line))
           {

               TransferRecord = _ConvertTransferLogLineToRecord(Line);

               vTransferLogRecord.push_back(TransferRecord);

           }

           MyFile.close();

       }

       return vTransferLogRecord;

   }
};
