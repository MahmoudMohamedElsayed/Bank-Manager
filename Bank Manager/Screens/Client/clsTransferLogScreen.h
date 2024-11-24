#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{


private:

    static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord Record)
    {

        cout << setw(8) << left << "" << "| " << setw(20) << left << Record.DateTime;
        cout << "| " << setw(12) << left << Record.S_AccountNumber;
        cout << "| " << setw(12) << left << Record.D_AccountNumber;
        cout << "| " << setw(12) << left << Record.Amount;
        cout << "| " << setw(12) << left << Record.S_AccountBalanceAfter;
        cout << "| " << setw(12) << left << Record.D_AccountBalanceAfter;
        cout << "| " << setw(12) << left << Record.UserName;

    }


public:

	static void ShowTransferLogScreen()
	{
		vector<clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTranferLogList();

		string Title = "\tTransfer Log List Screen";
		string SubTitle = "\t  (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(20) << "Date/Time";
        cout << "| " << left << setw(12) << "S.Account";
        cout << "| " << left << setw(12) << "D.Account";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(12) << "S.Balance";
        cout << "| " << left << setw(12) << "D.Balance";
        cout << "| " << left << setw(12) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord)
            {

                _PrintTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


	}

};

