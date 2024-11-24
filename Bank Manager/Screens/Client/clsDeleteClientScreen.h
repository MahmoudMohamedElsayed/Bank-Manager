#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
{

private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }


public:


	static void ShowDeleteClientScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t  Delete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate<string>::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate<string>::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        
        _PrintClient(Client);

        cout << "\nAre You sure you want to delete this client y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nAccount Deleted Successfully :-)\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
	}


};


