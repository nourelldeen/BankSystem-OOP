#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FirstLib.h"
#include <iomanip>
using namespace std;

string FileName = "Clients.txt";

struct stClientInfo
{
	string AccountNumber = "";
	string PinCode = "";
	string ClientName = "";
	string PhoneNum = "";
	float  Balance = 0.0;
	bool DeleteChick = false;
};

stClientInfo* FindClientByAccount(vector <stClientInfo>& vClientInfo, const string& AccountNum)
{
	for (auto& Client : vClientInfo)
	{
		if (Client.AccountNumber == AccountNum)
			return &Client;
	}
	return nullptr;
}

void MarkAccountToDelete(vector <stClientInfo>& vClientInfo, string AccountNum)
{
	for (stClientInfo& Info : vClientInfo)
	{
		if (Info.AccountNumber == AccountNum)
			Info.DeleteChick = true;
	}
}

string ConvertDataToRecordLine(stClientInfo Data, string Delim = "#//#")
{
	string RecordLine = "";

	RecordLine += Data.AccountNumber + Delim;
	RecordLine += Data.PinCode + Delim;
	RecordLine += Data.ClientName + Delim;
	RecordLine += Data.PhoneNum + Delim;
	RecordLine += to_string(Data.Balance);

	return RecordLine;
}

void ReadAccountNumber(string& AccountNumber)
{
	cout << "Enter Account Number? ";
	getline(cin >> ws, AccountNumber);
}

void ReadClientInfo(stClientInfo& ClientInfo)
{
	cout << "Enter Pin Code? ";
	getline(cin >> ws, ClientInfo.PinCode);

	cout << "Enter Name? ";
	getline(cin, ClientInfo.ClientName);

	cout << "Enter Phone? ";
	getline(cin, ClientInfo.PhoneNum);

	cout << "Enter Account Balance? ";
	cin >> ClientInfo.Balance;
}

vector <string> SplitRecordLine(string RecordLine, string Delim = "#//#")
{
	vector <string> vSplitData;
	size_t start = 0, Pos;
	while ((Pos = RecordLine.find(Delim, start)) != std::string::npos)
	{
		if (Pos > start)
			vSplitData.push_back(RecordLine.substr(start, Pos - start));

		start = Pos + Delim.length();
	}

	if (start < RecordLine.length())
		vSplitData.push_back(RecordLine.substr(start));

	return vSplitData;
}

stClientInfo ConvertRecordLineToStructData(string RecordLine)
{
	vector <string> vData;
	stClientInfo Client;

	vData = SplitRecordLine(RecordLine);
	Client.AccountNumber = vData[0];
	Client.PinCode = vData[1];
	Client.ClientName = vData[2];
	Client.PhoneNum = vData[3];
	Client.Balance = stof(vData[4]);

	return Client;
}

void ReadDataFromFile(vector <stClientInfo>& vClientData)
{
	fstream File;
	File.open(FileName, ios::in);

	string RecordLine;
	if (File.is_open())
	{
		while (getline(File, RecordLine))
		{
			vClientData.push_back(ConvertRecordLineToStructData(RecordLine));
		}
		File.close();
	}
	else
		cout << "The File Couldn't open!\n";
}

void DeleteClientFromVector(vector <stClientInfo>& vClientInfo)
{
	vector <stClientInfo> vClientInfo2;

	for (stClientInfo& DeletedAccount : vClientInfo)
	{
		if (!DeletedAccount.DeleteChick)
		{
			vClientInfo2.push_back(DeletedAccount);
		}
	}

	vClientInfo.clear();
	vClientInfo = vClientInfo2;
}
void UpdateDataToFile(vector <stClientInfo>& vClientInfo)
{
	fstream File;
	File.open(FileName, ios::out);

	string RecordLine;
	if (File.is_open())
	{
		for (stClientInfo& UpdateData : vClientInfo)
		{
			File << ConvertDataToRecordLine(UpdateData) << endl;
		}
		File.close();
	}
	else
		cout << "The File didn't open!\n";
}

void PrintClientData(stClientInfo& ClientData)
{
	cout << "----------------------------------------------------------\n";
	cout << "\t\t Client Information\n";
	cout << "----------------------------------------------------------\n\n\n";

	cout << "Account Number : " << ClientData.AccountNumber << endl;
	cout << "Pin Code       : " << ClientData.PinCode << endl;
	cout << "Name           : " << ClientData.ClientName << endl;
	cout << "Phone          : " << ClientData.PhoneNum << endl;
	cout << "Account Balance: " << ClientData.Balance << endl;
	cout << "----------------------------------------------------------\n\n\n";

}

void PrintScreenItem(string Item)
{
	system("cls");
	cout << "----------------------------------------------------------\n";
	cout << "\t\t" << Item << " Screen\n";
	cout << "----------------------------------------------------------\n\n\n";
}

void DeleteClient(vector <stClientInfo>& vClientData)
{
	PrintScreenItem("Delete Client");

	string AccountNumber;

	ReadAccountNumber(AccountNumber);

	stClientInfo* is_exist = FindClientByAccount(vClientData, AccountNumber);
	if (is_exist)
	{
		PrintClientData(*is_exist);

		char Sure = 'N';

		cout << "\nAre you sure you want to delete this account?  Y/N: ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			MarkAccountToDelete(vClientData, AccountNumber);
			DeleteClientFromVector(vClientData);
		}
	}
	else
		cout << "Client With Account Number (" << AccountNumber << ") Is Not Found!\n";
}

void UpdateClientScreen(vector <stClientInfo>& vClientData)
{
	PrintScreenItem("Update Client");

	string AccountNumber;
	ReadAccountNumber(AccountNumber);

	stClientInfo* is_exist = FindClientByAccount(vClientData, AccountNumber);

	if (is_exist != nullptr)
	{
		PrintClientData(*is_exist);

		ReadClientInfo(*is_exist);

		cout << "\nThe Client Information Updated Successfully ;)\n";
	}
	else
		cout << "Client With Account Number (" << AccountNumber << ") Is Not Found!\n";

}

void FindClient(vector <stClientInfo> vClientData)
{
	PrintScreenItem("Fined Client");

	string AccountNumber;
	ReadAccountNumber(AccountNumber);

	stClientInfo* is_exist = FindClientByAccount(vClientData, AccountNumber);
	if (is_exist != nullptr)
	{
		PrintClientData(*is_exist);
	}
	else
		cout << "Client With Account Number (" << AccountNumber << ") Is Not Found!\n";

}

void PrintClientListHeader(size_t ClientsNum)
{
	cout << "\t\t\t\t\t\t Client List (" << ClientsNum << ") Client(s). \n\n";
	cout << "____________________________________________________________________________________________________________________\n\n";
	cout << setw(20) << left << "| Account Number";
	cout << setw(20) << left << "| Pin Code";
	cout << setw(40) << left << "| Client Name";
	cout << setw(20) << left << "| Phone";
	cout << setw(20) << left << "| Balance";
	cout << "\n____________________________________________________________________________________________________________________\n\n";
}

void PrintListInfo(const stClientInfo Client)
{
	cout << "| " << setw(18) << Client.AccountNumber;
	cout << "| " << setw(18) << Client.PinCode;
	cout << "| " << setw(38) << Client.ClientName;
	cout << "| " << setw(18) << Client.PhoneNum;
	cout << "| " << setw(18) << Client.Balance;
}
void PrintBalanceInfoHeader(size_t ClientsNum)
{
	cout << "\t\t\t\t\t\t Client List (" << ClientsNum << ") Client(s). \n\n";
	cout << "____________________________________________________________________________________________________________________\n\n";
	cout << setw(20) << left << "| Account Number";
	cout << setw(40) << left << "| Client Name";
	cout << setw(20) << left << "| Balance";
	cout << "\n____________________________________________________________________________________________________________________\n\n";
}
void PrintBalanceInfo(stClientInfo Client)
{
	cout << "| " << setw(18) << Client.AccountNumber;
	cout << "| " << setw(38) << Client.ClientName;
	cout << "| " << setw(18) << Client.Balance;
}


void ShowBalanceList(vector <stClientInfo>& vClient)
{
	system("cls");
	PrintBalanceInfoHeader(vClient.size());

	for (stClientInfo& Info : vClient)
	{
		PrintBalanceInfo(Info);
		cout << endl;
	}
	cout << "\n____________________________________________________________________________________________________________________\n\n\n";

}
void ShowClientList(vector <stClientInfo>& vClient)
{
	system("cls");
	PrintClientListHeader(vClient.size());

	for (stClientInfo& Info : vClient)
	{
		PrintListInfo(Info);
	}
	cout << "\n____________________________________________________________________________________________________________________\n\n\n";

}

void GetValidAccountNumber(vector <stClientInfo> vClientInfo, stClientInfo& sClientInfo)
{
	ReadAccountNumber(sClientInfo.AccountNumber);

	while (FindClientByAccount(vClientInfo, sClientInfo.AccountNumber) != nullptr)
	{
		cout << "Client with [" << sClientInfo.AccountNumber << "] Already Exists, Please Enter Another Account Number? ";
		getline(cin, sClientInfo.AccountNumber);
	}
}
void AddNewClient(vector <stClientInfo>& vClientInfo)
{
	stClientInfo sClientInfo;
	char AddMore = 'Y';

	PrintScreenItem("Add New Clients");

	GetValidAccountNumber(vClientInfo, sClientInfo);

	while (toupper(AddMore) == 'Y')
	{
		ReadClientInfo(sClientInfo);
		vClientInfo.push_back(sClientInfo);

		cout << "\nClient Added Successfully, do you want to add more clients? Y/N: ";
		cin >> AddMore;
	}

}

void AddDeposit(stClientInfo* is_exist)
{
	float deposit = 0.0;
	cout << "Please Enter Deposit Amount? ";
	cin >> deposit;

	char sure = 'Y';
	cout << "Are you sure you want to add this deposit? Y/N  ";
	cin >> sure;

	if (toupper(sure) == 'Y')
	{
		is_exist->Balance += deposit;
	}
}
void WithdrawProcess(stClientInfo* is_existed)
{
	float withdraw = 0.0;
	cout << "Please Enter Withdraw Money? ";
	cin >> withdraw;

	while (withdraw > is_existed->Balance)
	{
		cout << "You don't have enough amount, Please try again:  ";
		cin >> withdraw;
	}
	char sure = 'Y';
	cout << "Are you sure you want to get the Withdraw? Y/N  ";
	cin >> sure;

	if (toupper(sure) == 'Y')
	{
		is_existed->Balance += withdraw * -1;
	}
}

void Deposit(vector <stClientInfo>& vClientInfo)
{
	PrintScreenItem("Deposit");

	string AccountNumber;
	ReadAccountNumber(AccountNumber);
	stClientInfo* is_exist;
	do
	{
		is_exist = FindClientByAccount(vClientInfo, AccountNumber);
		if (is_exist == nullptr)
		{
			cout << "Client With Account Number (" << AccountNumber << ") Doesn't Exist!\n";
			ReadAccountNumber(AccountNumber);
		}

	} while (is_exist == nullptr);

	PrintClientData(*is_exist);

	AddDeposit(is_exist);

	cout << "\nThe Process Done Successfully ;)\n";
}
void Withdraw(vector <stClientInfo>& vClientInfo)
{
	PrintScreenItem("Withdraw");

	string AccountNumber;
	ReadAccountNumber(AccountNumber);

	stClientInfo* is_exist;
	do
	{
		is_exist = FindClientByAccount(vClientInfo, AccountNumber);
		if (is_exist == nullptr)
		{
			cout << "Client With Account Number (" << AccountNumber << ") Doesn't Exist!\n";
			ReadAccountNumber(AccountNumber);
		}

	} while (is_exist == nullptr);

	PrintClientData(*is_exist);
	WithdrawProcess(is_exist);

	cout << "\nThe Process Done Successfully ;)\n";
}

float CalculateTotalBalance(vector <stClientInfo>& vClientInfo)
{
	float TotalBalance = 0.0;

	for (stClientInfo BalanceInfo : vClientInfo)
	{
		TotalBalance += BalanceInfo.Balance;
	}
	return TotalBalance;
}

void PrintClientBalanceList(vector <stClientInfo>& vClientInfo)
{
	ShowBalanceList(vClientInfo);
	cout << "\t\t\t\t Total Balance = " << CalculateTotalBalance(vClientInfo) << "\n\n";
}

void PrintMainMenuScreen()
{
	cout << "===================================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "===================================================\n\n";

	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete  Client.\n";
	cout << "\t[4] Update Client.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Exit.\n";

	cout << "===================================================\n\n";
}

void PrintTransactionMenuScreen()
{
	cout << "===================================================\n";
	cout << "\t\tTransaction Menu Screen\n";
	cout << "===================================================\n\n";

	cout << "\t[1] Deposit.\n";
	cout << "\t[2] withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menu.\n";

	cout << "===================================================\n\n";
}
enum enTransactionOption
{
	enDeposit = 1, enWithDraw = 2,
	enBalanceList = 3, enBackToTransActionMenu = 4
};

enum enMenuOptions
{
	enShowClientList = 1, enAddNewClient = 2,
	enDeleteClient = 3, enUpdateClient = 4,
	enFindClient = 5, enTransaction = 6,
	Exist = 7
};

short ChooseFromMenu(string Prompt)
{
	short ChoiceNum = MF::ReadValidNum(Prompt);
	return ChoiceNum;
}

void GoBackToMainMenu()
{
	cout << "Press any key to back to the Main Menu. . .\n";
	system("pause>0");
	system("cls");
	PrintMainMenuScreen();
}
void GoBackToTransactionMenu()
{
	cout << "Press any key to back to the Transaction Menu. . .\n";
	system("pause>0");
	system("cls");
	PrintTransactionMenuScreen();
}

void TransActionOptions(vector <stClientInfo>& vClientInfo)
{
	system("cls");

	PrintTransactionMenuScreen();

	enTransactionOption ChooseNum;
	do
	{
		ChooseNum = (enTransactionOption)ChooseFromMenu("Choose what do you want to do? [ 1 to 4 ] ?  ");

		switch (ChooseNum)
		{
		case enTransactionOption::enDeposit:
			Deposit(vClientInfo);
			GoBackToTransactionMenu();
			break;

		case enTransactionOption::enWithDraw:
			Withdraw(vClientInfo);
			GoBackToTransactionMenu();
			break;

		case enTransactionOption::enBalanceList:
			PrintClientBalanceList(vClientInfo);
			GoBackToTransactionMenu();
			break;
		case enTransactionOption::enBackToTransActionMenu:
			system("cls");
			break;
		}

	} while (ChooseNum > 0 && ChooseNum < 4);
}

void ChoosingProcess(vector <stClientInfo>& vClientInfo)
{
	PrintMainMenuScreen();
	ReadDataFromFile(vClientInfo);

	enMenuOptions ChooseNum;
	do
	{
		ChooseNum = (enMenuOptions)ChooseFromMenu("Choose what do you want to do? [ 1 to 7 ] ?  ");

		switch (ChooseNum)
		{
		case enMenuOptions::enShowClientList:
			ShowClientList(vClientInfo);
			GoBackToMainMenu();
			break;

		case enMenuOptions::enAddNewClient:
			AddNewClient(vClientInfo);
			GoBackToMainMenu();
			break;

		case enMenuOptions::enDeleteClient:
			DeleteClient(vClientInfo);
			GoBackToMainMenu();
			break;

		case enMenuOptions::enUpdateClient:
			UpdateClientScreen(vClientInfo);
			GoBackToMainMenu();
			break;

		case enMenuOptions::enFindClient:
			FindClient(vClientInfo);
			GoBackToMainMenu();
			break;

		case enMenuOptions::enTransaction:
			TransActionOptions(vClientInfo);// make a transaction
			PrintMainMenuScreen();
			break;
		case enMenuOptions::Exist:
			system("cls");
			cout << "===================================================\n";
			cout << "\t\tGoodbye :)\n";
			cout << "===================================================\n\n";
			break;

		}
		UpdateDataToFile(vClientInfo);


	} while (ChooseNum > 0 && ChooseNum < 7);
}

int main()
{
	vector <stClientInfo> vClientData;
	ChoosingProcess(vClientData);

	return 0;
}