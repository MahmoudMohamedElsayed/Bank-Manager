#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"


class clsFindCurrencyScreen : protected clsScreen
{

private:

    enum enFind { ByCode = 1, ByCountry = 2 };

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

    static void _ShowResults(clsCurrency Currency)
    {
        
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Not Found :-(\n";
        }

    }


public:


    static void ShowFindCurrencyScreen()
    {
        
        _DrawScreenHeader("\tFind Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = clsInputValidate<short>::ReadNumberBetween(1, 2, "Enter Number between 1 to 2? ");

        if ((enFind)Answer == enFind::ByCode)
        {
            cout << "\nPlease Enter CurrencyCode: ";
            string CurrencyCode = clsInputValidate<string>::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);

        }
        else
        {
            cout << "\nPlease Enter Country Name: ";
            string Country = clsInputValidate<string>::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);

        }
        
    }


};

