#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClientRecord(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n------------------\n";
		cout << "\nFull Name       : " << Client.FullName();
		cout << "\nAccount Number  : " << Client.AccountNumber();
		cout << "\nAccount Balance : " << Client.AccountBalance;
		cout << "\n\n------------------\n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber;

		cout << "\nPlease Enter Account Number to Transfer From: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nInvalid, Please Enter Account Number to Transfer From: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient SourceClient)
	{
		double Amount;

		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate<double>::ReadNumber();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the Available Balance, Enter another Amount ? " << Amount;
			Amount = clsInputValidate<double>::ReadNumber();
		}

		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\tTransfer Screen");


		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClientRecord(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClientRecord(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		char Answer = 'n';
		cout << "\n\nAre you sure you want to perform this operation? [Y/N]? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
			{
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer Faild \n";
			}
		}

		_PrintClientRecord(SourceClient);
		_PrintClientRecord(DestinationClient);

	}

};

