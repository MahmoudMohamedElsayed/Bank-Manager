#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{

private:

	static void _ReadUserInfo(clsUser& User)
	{

		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate<string>::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate<string>::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate<string>::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate<string>::ReadString();

		cout << "\nEnter Permissions: ";
		User.Permissions = _ReadPermissionsToSet();

	}

	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

	/*static int _ReadPermissionsToSet()
	{
		int Permissions = 0;

		char Answer = 'n';
		cout << "\nDo You want to give full access? [Y/N]? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions = -1;
		}
		else
		{
			cout << "\nDo You want to give access to: ";

			cout << "\n\nShow Client List? [Y/N]? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += 1 << 0;
			}

			cout << "\nAdd New Client? [Y/N]? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += 1 << 1;
			}

			cout << "\nDelete Client? [Y/N]? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += 1 << 2;
			}

			cout << "\nUpdate Client Info? [Y/N]? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += 1 << 3;
			}

			cout << "\nFind Client? [Y/N]? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += 1 << 4;
			}

			cout << "\nTransactions? [Y/N]? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += 1 << 5;
			}

			cout << "\nManage Users? [Y/N]? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += 1 << 6;
			}
		}

		return Permissions;
	}*/

	static int _ReadPermissionsToSet()
	{

		int Permissions = 0;
		char Answer = 'n';


		cout << "\nDo you want to give full access? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to : \n ";

		cout << "\nShow Client List? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{


			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pUpdateClients;
		}

		cout << "\nFind Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pTranactions;
		}

		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		cout << "\nLogin Register? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pLoginRegister;
		}

		return Permissions;

	}


public:

	static void ShowAddNewUserScreen()
	{

		_DrawScreenHeader("\t  Add New User Screen");

		cout << "\nPlease Enter UserName: ";
		string UserName = clsInputValidate<string>::ReadString();
		
		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName is Already Used, Choose another one: ";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser User = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(User);

		clsUser::enSaveResults SaveResults;
		SaveResults = User.Save();

		switch (SaveResults)
		{

		case clsUser::enSaveResults::svSucceeded:
		{

			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(User);
			break;
		}

		case clsUser::enSaveResults::svFaildEmptyObject:
		{

			cout << "\nError account was not saved because it's Empty";
			break;
		}

		case clsUser::enSaveResults::svFaildUserExists:
		{

			cout << "\nError account was not saved because user name is used!\n";
			break;
		}

		}

	}

};

