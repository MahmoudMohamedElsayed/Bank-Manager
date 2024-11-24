#pragma once
#include<iostream>


class clsInterfaceCommunication
{

public:

	virtual void SendSMS(std::string SMS) = 0;
	virtual void SendEmail(std::string Email) = 0;

};

