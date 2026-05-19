#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include <fstream>
#include <vector>

using namespace std;

class clsBankClient :public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNew = 2 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static string _ConvertObjectToLine(clsBankClient ClientInfo, string Seperator = "#//#")
    {
        string LineInfo;
        // Ensure we include the separator between every field so each client is
        // serialized as a single line with proper field delimiting.
        LineInfo = ClientInfo.FirstName + Seperator
            + ClientInfo.LastName + Seperator
            + ClientInfo.Phone + Seperator
            + ClientInfo.Email + Seperator
            + ClientInfo.GetAccountNumber() + Seperator
            + ClientInfo.PinCode + Seperator
            + to_string(ClientInfo._AccountBalance);
        return LineInfo;
    }
    static clsBankClient _UpdateClientDataInVector(vector <clsBankClient>& vFileData, string AccountNumber)
    {
        for (clsBankClient& Client : vFileData)
        {
            if (Client.GetAccountNumber() == AccountNumber)
            {
                return GetInfoFromUser(Client);

            }
        }
        return _GetEmptyClientObject();
    }
  static  clsBankClient _GetAddNewClient(string AccountNumber) {
        return clsBankClient(enMode::AddNew, "", "", "", "", AccountNumber, "", 0);
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

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        return (!Client1.IsEmpty());
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
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

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
    static vector <clsBankClient> GetDataFromFileToVector(vector <clsBankClient>& vFileData)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vFileData.push_back(_ConvertLinetoClientObject(Line));
            }
            MyFile.close();
        }
        else
            cout << "The file can't open!\n";

        return vFileData;
    }
    static clsBankClient GetInfoFromUser(clsBankClient Client)
    {

        cout << "Please enter First Name: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "Please enter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "Please enter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "Please enter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "Please enter Password: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Please enter Balance: ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();

        return Client;
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
                MyFile << _ConvertObjectToLine(ClientInfo) << endl;
            }
            MyFile.close();
        }
        else
            cout << "The file can't open!\n";
    }

    static	clsBankClient UpdateClientData()
    {
        string AccountNumber;
        vector <clsBankClient> vFileData;
        
        cout << "Please Enter The Account Number?\n";
        AccountNumber = clsInputValidate::ReadString();

        while (!IsClientExist(AccountNumber))
        {
            cout << "The Client Is NOT Exist! Please try again?\n";
            AccountNumber = clsInputValidate::ReadString();
        }
        
        clsBankClient Client = Find(AccountNumber);
        Client.Print();

        GetDataFromFileToVector(vFileData);
        clsBankClient ClientAfterUpdated = _UpdateClientDataInVector(vFileData, AccountNumber);
         UploadDataToFile(vFileData);
         ClientAfterUpdated.Print();

        return ClientAfterUpdated;
    }
    string GetAccountNumber()
    {
        cout << "Please enter the Account Number?\n";
        return clsInputValidate::ReadString();
    }
    
    static void AddNewClient()
    {
       // vector <clsBankClient> vFileData;
        string AccountNumber;
        cout << "Please enter the AccountNumber?\n";
        AccountNumber = clsInputValidate::ReadString();

        while (IsClientExist(AccountNumber))
        {
            cout << "The Client Is Exist! Please enter another PinCode?\n";
            AccountNumber = clsInputValidate::ReadString();
        }
       // GetDataFromFileToVector(vFileData);
        clsBankClient NewClient = _GetAddNewClient(AccountNumber);
        AddNewClientToFill(NewClient);
        

        
        
    }
};
