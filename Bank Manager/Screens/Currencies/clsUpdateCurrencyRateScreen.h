#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"


class clsUpdateCurrencyRateScreen : protected clsScreen
{

private:


    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$)   =  " << Currency.Rate();

        cout << "\n_____________________________\n";

    }

    static float _ReadNewRate()
    {

        cout << "\nEnter New Rate: ";
        float NewRate = clsInputValidate<float>::ReadNumber();
        return NewRate;
    }

public:


    static void ShowUpdateCurrencyRateScreen()
    {
        
        _DrawScreenHeader("\t Update Currency Screen");

        cout << "\nPlease Enter Currency Screen: ";
        string CurrencyCode = clsInputValidate<string>::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate<string>::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        _PrintCurrency(Currency);

        char Answer = 'n';
        cout << "\nAre you sure you want to update the rate of this Currency [Y/N]? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {

            cout << "\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            Currency.UpdateRate(_ReadNewRate());
            cout << "\nCurrency Rate Update Successfully :-)\n";
            _PrintCurrency(Currency);

        }

    }


};

