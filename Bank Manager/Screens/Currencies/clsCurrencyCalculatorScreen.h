#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{

public:

    static void _PrintCurrencyCard(clsCurrency Currency, string Title)
    {
        cout << Title;
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$)   =  " << Currency.Rate();
        cout << "\n_____________________________\n\n";

    }

    static clsCurrency _GetCurrency(string Message)
    {
        cout << Message;
        string CurrencyCode = clsInputValidate<string>::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate<string>::ReadString();
        }

        clsCurrency CurrencyOne = clsCurrency::FindByCode(CurrencyCode);
        return CurrencyOne;
    }

    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = clsInputValidate<float>::ReadNumber();
        return Amount;
    }

    static void _PrintCalculationsResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
    {
        _PrintCurrencyCard(CurrencyFrom, "\nConvert From:\n");

        float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);

        cout << Amount << " " << CurrencyFrom.CurrencyCode() 
             << " = " << AmountInUSD << " USD\n";

        if (CurrencyTo.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to: \n";

        _PrintCurrencyCard(CurrencyFrom, "\nTo:\n");

        float AmountInCurrencyTo = CurrencyFrom.ConvertToOtherCurrency2(Amount, CurrencyTo);
        
        cout << Amount << " " << CurrencyFrom.CurrencyCode() 
             << " = " << AmountInCurrencyTo << " " << CurrencyTo.CurrencyCode();

    }

public:

    static void ShowCurrencyCalculatorScreen()
    {
        char Answer = 'n';

        do
        {
            system("cls");
            _DrawScreenHeader("\tCalculator Currency Screen");


            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code : ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code : ");
            float Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Answer;

        } while (toupper(Answer) == 'Y');

    }
};

