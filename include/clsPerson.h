#pragma once
#include <iostream>
#include <string>

class clsPerson
{

private:

    std::string _FirstName;
    std::string _LastName;
    std::string _Email;
    std::string _Phone;

public:

    clsPerson(std::string FirstName, std::string LastName, std::string Email, std::string Phone)
    {

        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }

    //Property Set
    void SetFirstName(std::string FirstName)
    {
        _FirstName = FirstName;
    }

    //Property Get
    std::string GetFirstName()
    {
        return _FirstName;
    }
    __declspec(property(get = GetFirstName, put = SetFirstName)) std::string FirstName;

    //Property Set
    void SetLastName(std::string LastName)
    {
        _LastName = LastName;
    }

    //Property Get
    std::string GetLastName()
    {
        return _LastName;
    }
    __declspec(property(get = GetLastName, put = SetLastName)) std::string LastName;

    //Property Set
    void SetEmail(std::string Email)
    {
        _Email = Email;
    }

    //Property Get
    std::string GetEmail()
    {
        return _Email;
    }
    __declspec(property(get = GetEmail, put = SetEmail)) std::string Email;

    //Property Set
    void SetPhone(std::string Phone)
    {
        _Phone = Phone;
    }

    //Property Get
    std::string GetPhone()
    {
        return _Phone;
    }
    __declspec(property(get = GetPhone, put = SetPhone)) std::string Phone;

    std::string FullName()
    {
        return _FirstName + " " + _LastName;
    }

    void Print()
    {
        std::cout << "\nInfo:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName: " << _FirstName;
        std::cout << "\nLastName : " << _LastName;
        std::cout << "\nFull Name: " << FullName();
        std::cout << "\nEmail    : " << _Email;
        std::cout << "\nPhone    : " << _Phone;
        std::cout << "\n___________________\n";

    }

};
