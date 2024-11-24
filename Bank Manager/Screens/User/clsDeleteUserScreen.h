#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{

private:

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


public:

	static void ShowDeleteUserScreen()
	{

		_DrawScreenHeader("\t  Delete User Screen");

		cout << "\nPlease Enter UserName: ";
		string UserName = clsInputValidate<string>::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName is not found, Choose another one: ";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintUser(User);

		char Answer = 'n';
		cout << "\nAre you sure you want to delete this User? [Y/N]? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{

			if (User.Delete())
			{

				cout << "\nDeleted User Successfully :-)\n";

				_PrintUser(User);
			}
			else
			{

				cout << "\nError User Was Not Deleted :-(\n";
			}

		}
	}

};

