#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen
{

private:

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate<string>::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate<string>::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate<string>::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate<string>::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate<string>::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate<float>::ReadNumber();
    }

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

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t  Update Client Screen");

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

        cout << "\nAre You sure you want to Update this client y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {

            cout << "\nUpdate Client Info:";
            cout << "\n___________________\n";

            _ReadClientInfo(Client);

            clsBankClient::enSaveResults SaveResults;

            SaveResults = Client.Save();

            switch (SaveResults)
            {

            case clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\n\nAccount Update Successfully :-)\n";
                _PrintClient(Client);
                break;
            }

            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }

            }
        }


    }

};

