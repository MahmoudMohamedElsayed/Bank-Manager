#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "Global.h"
#include "clsUtil.h"

using namespace std;

static string FileNameClients = "Clients.txt";

class clsBankClient : public clsPerson
{
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 3 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDelete = false;

	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		vector<string> vString = clsString::Split(Line, Seperator);
		stTransferLogRecord TransferLogRecord;

		TransferLogRecord.DateTime = vString[0];
		TransferLogRecord.S_AccountNumber = vString[1];
		TransferLogRecord.D_AccountNumber = vString[2];
		TransferLogRecord.Amount = stoi(vString[3]);
		TransferLogRecord.S_AccountBalanceAfter = stoi(vString[4]);
		TransferLogRecord.D_AccountBalanceAfter = stoi(vString[5]);
		TransferLogRecord.UserName = vString[6];

		return TransferLogRecord;
	}

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vString;
		vString = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vString[0], vString[1], vString[2], vString[3], vString[4], clsUtil::DecryptText(vString[5]), stod(vString[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";

		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += clsUtil::EncryptText(Client.PinCode) + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static vector<clsBankClient> _LoadDateFromFileToObject(string FileName)
	{
		vector<clsBankClient> vClients;

		fstream Clients;
		Clients.open(FileNameClients, ios::in);

		if (Clients.is_open())
		{
			string Line = "";
			while (getline(Clients, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);

			}

			Clients.close();
		}

		return vClients;
	}

	static void _SaveClientObjectToFile(vector<clsBankClient> vClients)
	{
		
		fstream Clients;
		Clients.open(FileNameClients, ios::out);

		string AddLine = "";

		if (Clients.is_open())
		{

			for (clsBankClient& Client : vClients)
			{
				if (Client._MarkForDelete == false)
				{
					AddLine = _ConvertClientObjectToLine(Client);

					Clients << AddLine << endl;
				}
			}

			Clients.close();
		}
	}

	void _Update()
	{
		vector<clsBankClient> _vClients = _LoadDateFromFileToObject(FileNameClients);

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientObjectToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream Clients;
		Clients.open(FileNameClients, ios::out | ios::app);

		if (Clients.is_open())
		{
			Clients << stDataLine << endl;

			Clients.close();
		}

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _PrepareTransferLogRecord(double Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#")
	{
		string TransferRecord = "";

		TransferRecord += clsDate::GetSystemDateTimestring() + Seperator;
		TransferRecord += AccountNumber() + Seperator;
		TransferRecord += DestinationClient.AccountNumber() + Seperator;
		TransferRecord += to_string(Amount) + Seperator;
		TransferRecord += to_string(AccountBalance) + Seperator;
		TransferRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferRecord += UserName;

		return TransferRecord;
	}

	void _RegisterTransferLog(double Amount, clsBankClient DestinationClient, string UserName)
	{
		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("transfers.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}


public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLogRecord
	{

		string DateTime;
		string S_AccountNumber;
		string D_AccountNumber;
		float Amount;
		float S_AccountBalanceAfter;
		float D_AccountBalanceAfter;
		string UserName;

	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	// Read Only Property
	string AccountNumber()
	{
		return _AccountNumber;
	}

	// Property Set
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	// Property Get
	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	// Property Set
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	// Property Get
	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName       : " << FirstName;
		cout << "\nLastName        : " << LastName;
		cout << "\nFull Name       : " << FullName();
		cout << "\nEmail           : " << Email;
		cout << "\nPhone           : " << Phone;
		cout << "\nAccount Number  : " << _AccountNumber;
		cout << "\nPassword        : " << _PinCode;
		cout << "\nAccount Balance : " << _AccountBalance;
		cout << "\n___________________\n";
	}*/

	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClients;
		fstream Clients;
		Clients.open(FileNameClients, ios::in);

		if (Clients.is_open())
		{
			string Line = "";

			while (getline(Clients, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					Clients.close();
					return Client;
				}

				vClients.push_back(Client);
			}
			Clients.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vClients;
		fstream Clients;
		Clients.open(FileNameClients, ios::in);

		if (Clients.is_open())
		{
			string Line = "";

			while (getline(Clients, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					Clients.close();
					return Client;
				}

				vClients.push_back(Client);
			}
			Clients.close();
		}

		return _GetEmptyClientObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{

		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();

			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;

				return enSaveResults::svSucceeded;

			}
			break;
		}

		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	bool Delete()
	{
		vector<clsBankClient> vClients = _LoadDateFromFileToObject(FileNameClients);

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientObjectToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadDateFromFileToObject(FileNameClients);
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

	bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName)
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

	static double GetTotalBalance()
	{
		vector<clsBankClient> vClients = GetClientsList();

		double TotalBalance = 0;

		for (clsBankClient& C : vClients)
		{
			TotalBalance += C.AccountBalance;
		}

		return TotalBalance;
	}

	static vector<stTransferLogRecord> GetTranferLogList()
	{
		vector<stTransferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("Transfers.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";
			stTransferLogRecord TransferLogRecord;

			while (getline(MyFile, Line))
			{
				TransferLogRecord = _ConvertTransferLogLineToRecord(Line);

				vTransferLogRecord.push_back(TransferLogRecord);
			}

			MyFile.close();
		}

		return vTransferLogRecord;
	}
};

