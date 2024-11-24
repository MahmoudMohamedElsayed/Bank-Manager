#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"


class clsShowTransactionsMenue : protected clsScreen
{

private:

	enum enTransactionsMenueOption { 
		eDeposit = 1, eWithdraw = 2, 
		eShowTotalBalances = 3, eTransfer = 4,
		eTransferLog = 5, eShowMainMenue = 6
	};

	static short _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate<short>::ReadNumberBetween(1, 6, "Enter Number between 1 to 4? ");
		return Choice;
	}

	static  void _GoBackToTransactionsMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _ShowDepositScreen()
	{

		clsDepositScreen::ShowDepositScreen();

	}

	static void _ShowWithdrawScreen()
	{

		clsWithdrawScreen::ShowWithdrawScreen();

	}

	static void _ShowTotalBalancesScreen()
	{

		clsTotalBalancesScreen::ShowTotalBalances();

	}

	static void _ShowTransferScreen()
	{

		clsTransferScreen::ShowTransferScreen();

	}

	static void _ShowTransferLogScreen()
	{

		clsTransferLogScreen::ShowTransferLogScreen();

	}


	static void _PerfromTransactionsMenueOption(enTransactionsMenueOption TransactionsMenueOption)
	{
		switch (TransactionsMenueOption)
		{

		case enTransactionsMenueOption::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOption::eWithdraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOption::eShowTotalBalances:
		{
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOption::eTransfer:
		{
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOption::eTransferLog:
		{
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOption::eShowMainMenue:
		{
			//
		}

		}
	}



public:

	static void ShowTransactionsMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
		{
			return;// this will exit the function and it will not continue
		}

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] TotalBalances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromTransactionsMenueOption((enTransactionsMenueOption)_ReadTransactionsMenueOption());
	}


};

