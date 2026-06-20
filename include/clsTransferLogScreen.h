#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsBankClient.h"


class clsTransferLogScreen :protected clsScreen
{

private:

    static void PrintTransferLogRecordLine(clsBankClient::stTrnsferLogRecord TransferLogRecord)
    {

        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(23) << std::left << TransferLogRecord.DateTime;
        std::cout << "| " << std::setw(8) << std::left << TransferLogRecord.SourceAccountNumber;
        std::cout << "| " << std::setw(8) << std::left << TransferLogRecord.DestinationAccountNumber;
        std::cout << "| " << std::setw(8) << std::left << TransferLogRecord.Amount;
        std::cout << "| " << std::setw(10) << std::left << TransferLogRecord.srcBalanceAfter;
        std::cout << "| " << std::setw(10) << std::left << TransferLogRecord.destBalanceAfter;
        std::cout << "| " << std::setw(8) << std::left << TransferLogRecord.UserName;


    }

public:

    static void ShowTransferLogScreen ()
    {


        std::vector <clsBankClient::stTrnsferLogRecord> vTransferLogRecord = clsBankClient::GetTransfersLogList();

        std::string Title = "\tTransfer Log List Screen";
        std::string SubTitle = "\t    (" + std::to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

        std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(23) << "Date/Time";
        std::cout << "| " << std::left << std::setw(8) << "s.Acct";
        std::cout << "| " << std::left << std::setw(8) << "d.Acct";
        std::cout << "| " << std::left << std::setw(8) << "Amount";
        std::cout << "| " << std::left << std::setw(10) << "s.Balance";
        std::cout << "| " << std::left << std::setw(10) << "d.Balance";
        std::cout << "| " << std::left << std::setw(8) << "User";

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

        if (vTransferLogRecord.size() == 0)
            std::cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTrnsferLogRecord Record : vTransferLogRecord)
            {

                PrintTransferLogRecordLine(Record);
                std::cout << std::endl;
            }

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

    }

};
