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




class clsBankClient : public clsPerson
{
private:
    enum enMode { enEmptyMode = 0, enUpdateMode = 1, enAddNew = 2, enDelete = 3 };
    enMode _Mode;
    std::string _AccountNumber;
    std::string _PinCode;
    double _AccountBalance;
    bool _IsDeleted = false;

    void _MarkAccountToDelete(std::vector <clsBankClient>& vClientInfo, std::string AccountNum)
    {
        for (clsBankClient& Client : vClientInfo)
        {
            if (Client.GetAccountNumber() == AccountNum)
                Client._IsDeleted = true;
        }
    }


    static clsBankClient _ConvertLinetoClientObject(std::string Line, std::string Seperator = "#//#")
    {
        std::vector<std::string> _vClientData;
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
                std::stod(_vClientData[6])            // AccountBalance as double
            );
        }
        else
            std::cout << "Error in Data File\n";

        return _GetEmptyClientObject();

    }

    static std::string _ConvertObjectToLine(clsBankClient ClientInfo, std::string Seperator = "#//#")
    {
        std::string LineInfo;

        LineInfo =
            ClientInfo.FirstName + Seperator
            + ClientInfo.LastName + Seperator
            + ClientInfo.Email + Seperator
            + ClientInfo.Phone + Seperator
            + ClientInfo.GetAccountNumber() + Seperator
            + ClientInfo.PinCode + Seperator
            + std::to_string(ClientInfo.AccountBalance);
        return LineInfo;
    }

    static std::vector <clsBankClient> _GetDataFromFileToVector()
    {
        std::vector <clsBankClient> vFileData;

        std::fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            std::string Line;
            while (getline(MyFile, Line))
            {
                if (!Line.empty())
                    vFileData.push_back(_ConvertLinetoClientObject(Line));
            }
            MyFile.close();
        }
        else
            std::cout << "The file can't open!\n";

        return vFileData;
    }

    static void _UploadDataToFile(std::vector <clsBankClient>& vFileData)
    {
        std::fstream MyFile;
        MyFile.open("Clients.txt", ios::out);

        if (MyFile.is_open())
        {
            std::string Line;
            for (clsBankClient& ClientInfo : vFileData)
            {
                if (ClientInfo._IsDeleted == false)
                {
                    MyFile << _ConvertObjectToLine(ClientInfo) << std::endl;
                }
            }
            MyFile.close();
        }
        else
            std::cout << "The file can't open!\n";
    }

    static void _GetInfoFromUser(clsBankClient& Client)
    {

        std::cout << "Please enter First Name: ";
        Client.FirstName = clsInputValidate::ReadString();

        std::cout << "Please enter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();

        std::cout << "Please enter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        std::cout << "Please enter Email: ";
        Client.Email = clsInputValidate::ReadString();

        std::cout << "Please enter Pin Code: ";
        Client.PinCode = clsInputValidate::ReadString();

        std::cout << "Please enter Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();

    }

    void _Update()
    {
        std::vector <clsBankClient> _vClients;
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
    void _AddDataLineToFile(std::string  stDataLine)
    {
        std::fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << std::endl;

            MyFile.close();
        }
        else
            std::cout << "The File Can't Open!\n";

    }
   
    static clsBankClient _GetEmptyClientObject()
        {
            return clsBankClient(enMode::enEmptyMode, "", "", "", "", "", "", 0);
        }
   
    std::string _PrepareTransferLogRecord(double Amount, clsBankClient DestinationClient,
        std::string UserName, std::string Seperator = "#//#")
    {
        std::string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += GetAccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.GetAccountNumber() + Seperator;
        TransferLogRecord += std::to_string(Amount) + Seperator;
        TransferLogRecord += std::to_string(AccountBalance) + Seperator;
        TransferLogRecord += std::to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    struct stTrnsferLogRecord;
    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(std::string Line, std::string Seperator = "#//#")
    {
        stTrnsferLogRecord TrnsferLogRecord;

        std::vector <std::string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;

    }
    void _RegisterTransferLog(double Amount, clsBankClient DestinationClient, std::string UserName)
    {

        std::string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

        std::fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << std::endl;

            MyFile.close();
        }

    }
public:
    clsBankClient(enMode Mode, std::string FirstName, std::string LastName,
        std::string Email, std::string Phone, std::string AccountNumber, std::string PinCode,
        double AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    struct stTrnsferLogRecord
    {
        std::string DateTime;
        std::string SourceAccountNumber;
        std::string DestinationAccountNumber;
        double  Amount;
        double  srcBalanceAfter;
        double  destBalanceAfter;
        std::string UserName;
    };

    std::string GetAccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(std::string PinCode)
    {
        _PinCode = PinCode;
    }
    std::string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) std::string PinCode;

    void SetAccountBalance(double AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    double GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

    static bool IsClientExist(std::string AccountNumber)
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
    static  clsBankClient GetAddNewClientObject(std::string AccountNumber) {
        return clsBankClient(enMode::enAddNew, "", "", "", "", AccountNumber, "", 0);
    }

  static clsBankClient Find(std::string AccountNumber)
    {
        std::fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            std::string Line;
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
  static clsBankClient Find(std::string AccountNumber, std::string PinCode)
    {

        std::fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            std::string Line;
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
      std::vector <clsBankClient> vFileData = _GetDataFromFileToVector();

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

  static std::vector <clsBankClient> GetClientsList()
  {
      return _GetDataFromFileToVector();
  }
   void Print()
  {
      std::cout << "\nClient Card:";
      std::cout << "\n___________________";
      std::cout << "\nFirstName   : " << FirstName;
      std::cout << "\nLastName    : " << LastName;
      std::cout << "\nFull Name   : " << FullName();
      std::cout << "\nEmail       : " << Email;
      std::cout << "\nPhone       : " << Phone;
      std::cout << "\nAcc. Number : " << GetAccountNumber();
      std::cout << "\nPin Code    : " << GetPinCode();
      std::cout << "\nBalance     : " << GetAccountBalance();
      std::cout << "\n___________________\n";
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
   bool Transfer(double Amount, clsBankClient& DestinationClient, std::string UserName)
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
   static  std::vector <stTrnsferLogRecord> GetTransfersLogList()
   {
       std::vector <stTrnsferLogRecord> vTransferLogRecord;

       std::fstream MyFile;
       MyFile.open("TransferLog.txt", ios::in);//read Mode

       if (MyFile.is_open())
       {

           std::string Line;

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
