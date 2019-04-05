#pragma once
#include "MainHeader.h"
#include "User.h"


class Registration
{
	Registration();
	static Registration * instance;
	string superAdminLogin = "Super"; // The super admin name,super admin can give the admins for users

	string filePath = "userData.txt"; // Path to user data 
	string paramsPath = "paramsData.txt";
public:
	int countOfLogin = 0; // All login count;

	void LoadSystemParams(); 
	void SynchronizationSystemParams();

	User InputLogin(string _login, string _password); // Get login and password
	User InputRegistrat(string _login, string _name, string _password, string _phoneNumber); // Registration of new user
	
	bool IsExist(string _login, string _password = "none"); // Return true if user exist
	bool CheckLogin(string _login); // Check login for block symbols
	bool CheckPassword(string _password); // Check password for block symbols

	string GetSuperAdminLogin(); // Return super administrator login

	friend void SaveToFile(string _login, string _name, string _password, string _phoneNumber); // Save new user to file
	friend User GetFromFile(string _login = "none"); // Get user from file

	static Registration * GetInstance()
	{
		if (instance == NULL)
		{
			instance = new Registration();
		}
		return instance;
	}

	~Registration();
};
