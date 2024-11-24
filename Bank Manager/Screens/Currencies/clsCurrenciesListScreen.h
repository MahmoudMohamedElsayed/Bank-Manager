#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>


class clsCurrenciesListScreen : protected clsScreen
{

private:

    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << left << setw(30) << Currency.Country();
        cout << "| " << left << setw(8) << Currency.CurrencyCode();
        cout << "| " << left << setw(42) << Currency.CurrencyName();
        cout << "| " << left << setw(12) << Currency.Rate();
    }

public:

    static void ShowCurrenciesListScreen()
    {
        vector<clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();
        string Title = "\tCurrencies List Screen";
        string SubTitle = "\t  (" + to_string(vCurrencys.size()) + ") tCurrencies.";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(42) << "Name";
        cout << "| " << left << setw(12) << "Rate(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrencys.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";

        else
        {

            for (clsCurrency& C : vCurrencys)
            {
                _PrintCurrencyRecordLine(C);
                cout << endl;
            }

        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

};

