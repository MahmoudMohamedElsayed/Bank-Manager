#pragma once

#include<iostream>
#include<string>
#include "clsDate.h"

using namespace std;

template <class T>

class clsInputValidate
{
public:

	static bool IsNumberBetween(T Number, T From, T To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo)
	{
		return ((clsDate::IsDate1BeforeDate2(DateFrom, Date) || clsDate::IsDate1EqualDate2(DateFrom, Date))
				&&
				(clsDate::IsDate1AfterDate2(DateTo, Date) || clsDate::IsDate1EqualDate2(DateTo, Date)))

				||

			   ((clsDate::IsDate1BeforeDate2(DateTo, Date) || clsDate::IsDate1EqualDate2(DateTo, Date))
				&&
				(clsDate::IsDate1AfterDate2(DateFrom, Date) || clsDate::IsDate1EqualDate2(DateFrom, Date)));
	}

	static string ReadString()
	{
		string S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}

	static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		T Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static T ReadNumberBetween(T From, T To, string Message)
	{
		T Number = ReadNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << Message;
			Number = ReadNumber();
		}
		return Number;
	}

	static bool ISValidDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}
	
};

