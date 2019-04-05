#pragma once
#include "MainHeader.h"

class User
{
public:
	string login = "none", name = "none", password = "none", phone = "none";
	int rightAnswer = 0;
	bool isAdmin = false;
	
	User();
	~User();
};

