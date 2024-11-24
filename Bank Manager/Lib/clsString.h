#pragma once
#include<iostream>
#include<vector>
#include <cctype>
#include <string>
using namespace std;
class clsString
{
	string _Value;

public:
    // Dummy Constructor
	clsString() { _Value = ""; }
    // Constructor Parameterized
	clsString(string value)
	{
		_Value = value;
	}

	// Property Set
	void SetValue(string value) {
		_Value = value;
	}

	// Property Get
	string GetValue() {
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;

    // Method How Many Letter Of Words
    static short Length(string S1) {
        return S1.length();
    }

    // Overloading Method How Many Letter Of Words
    short Length() {
        return _Value.length();
    }

    // Function How many word in all string
    static short CountWords(string S1, string delim = " ")
    {
        string sWord = "";
        short pos = 0;
        short Counter = 0;

        while ((pos = S1.find(delim)) != S1.npos)
        {
            sWord = S1.substr(0, pos);
            if (sWord != "")
            {
                Counter++;
            }
            S1.erase(0, pos + delim.length());
        }
        if (S1 != "")
        {
            Counter++;
        }
        return Counter;
    }

    // Overloading Function How many word
    short CountWords() {
        return CountWords(_Value);
    }

    // Function count is character Uppercase in words
    static short isUpper(string S1) {
        short counter = 0;
        for (char& C : S1) 
            if (C >= 'A' && C <= 'Z') 
                counter++;
        return counter;
    }

    // Overloading Function count is character Uppercase in words
    short isUpper() {
        return isUpper(_Value);
    }

    // Method Caracter is UpperCase OR no
    bool isUpper(char C) {
        return C >= 'A' && C <= 'Z';
    }

    // Function count is character Lowercase  in words
    static short isLower(string S1)
    {
        short counter = 0;
        for (char& C : S1)
            if (C >= 'a' && C <= 'z')
                counter++;
        return counter;
    }

    // Overloading Function count is character Lowercase in words
    short isLower() {
        return isLower(_Value);
    }

    // Method Caracter is Lowercase OR no
    bool isLower(char C) {
        return C >= 'a' && C <= 'z';
    }

    // Method Convert character UpperCase To Lowercase
    static string LowerAllString(string S1) {
        for (char& C : S1) {
            if (isupper(C)) {
                C += 32;
            }
        }
        return S1;
    }

    // Overloading Method Convert character UpperCase To Lowercase
    string LowerAllString() {
        return LowerAllString(_Value);
    }

    // Method Convert character UpperCase To Lowercase
    static string UpperAllString(string S1) {
        for (char& C : S1) {
            if (islower(C)) {
                C -= 32;
            }
        }
        return S1;
    }

    // Method Convert character UpperCase To Lowercase
    string UpperAllString() {
        return UpperAllString(_Value);
    }

    // Method Convert First Letter Of Each Word To Uppercase
    static string UpperFirstLetterOfEachWord(string S1) {

        bool isFirstLetter = true;
        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = toupper(S1[i]);
            }
            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }

    //Overloading Method Convert First Letter Of Each Word To Uppercase
    string UpperFirstLetterOfEachWord() {

        return UpperFirstLetterOfEachWord(_Value);
    }    // Method Convert First Letter Of Each Word To Uppercase

    // Method Convert First Letter Of Each Word To Lowercase
    static string LowerFirstLetterOfEachWord(string S1) {

        bool isFirstLetter = true;
        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = tolower(S1[i]);
            }
            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }

    //Overloading Method Convert First Letter Of Each Word To Lowercase
    void LowerFirstLetterOfEachWord() {

        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    // Method How Many Letter of Each word
    enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };

    static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All) {

        if (WhatToCount == enWhatToCount::All)
            return S1.length();

        short Counter = 0;
        for (short i = 0; i < S1.length(); i++)
        {
            if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
            {
                Counter++;
            }

            if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
            {
                Counter++;
            }
        }
        return Counter;
    }
    
    // Method Split String and Add to Vector
    static vector<string> Split(string S1, string delim = " ") {

        vector<string> vString;
        short pos = 0;
        string sWord = "";

        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos);

            vString.push_back(sWord);

            S1.erase(0, pos + delim.length());
        }

        vString.push_back(S1);
        
        return vString;
    }

    // Overloading Method Split String and Add to Vector
    vector<string> Split() {

        return Split(_Value);
    }

    // Method Delete Space Of String Left
    static string TrimLeft(string S1) {

        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(i, S1.length() - i);
            }
        }
        return "";
    }

    // Overloading Method Delete Space Of String Left
    string TrimLeft() {

        return TrimLeft(_Value);
    }

    // Method Delete Space Of String Right
    static string TrimRight(string S1) {

        for (short i = S1.length() - 1; i >= 0; i--)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);
            }
        }
        return "";
    }

    // Overloading Method Delete Space Of String Right
    string TrimRight() {

        return TrimRight(_Value);
    }

    // Method Delete Space Of String Right and Left
    static string Trim(string S1) {

        return TrimLeft(TrimRight(S1));
    }

    // Overloading Method Delete Space Of String Right
    string Trim() {

        return Trim(_Value);
    }

    // Method Convert Vector To String
    static string JoinString(vector<string> vString, string delim = " ") {

        string S1 = "";
        for (string& S : vString)
        {
            S1 = S1 + S + delim;
        }
        return S1.substr(0, S1.length() - delim.length());
    }

    // Method Convert Array To String
    static string JoinString(string arr[], short Length, string delim = " ") {

        string S1 = "";
        for (int i = 0; i < Length; i++)
        {
            S1 = S1 + arr[i] + delim;
        }
        return S1.substr(0, S1.length() - delim.length());
    }

    // Method Reverse Words in All String
    static string ReverseWordsInString(string S1) { 

        vector<string> vString;
        string S2 = "";

        vString = Split(S1, " ");

        auto it = vString.end();
        while (it != vString.begin())
        {
            --it;
            S2 += *it + " ";
        }
        S2 = S2.substr(0, S2.length() - 1);
        return S2;
    }

    // Overloading Method Reverse Words in All String
    string ReverseWordsInString() {

        return ReverseWordsInString(_Value);
    }

    // Method Remove All Punctuations in String
    static string RemovePunctuations(string S1)
    {

        string S2 = "";

        for (char &C : S1)
        {
            if (!ispunct(C))
            {
                S2 += C;
            }
        }

        return S2;

    }

    // Overloading Method Remove All Punctuations in String
    void RemovePunctuations()
    {
        _Value = RemovePunctuations(_Value);
    }

};

