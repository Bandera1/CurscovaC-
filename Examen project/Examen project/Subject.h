#pragma once
#include "MainHeader.h"
#include "Test.h"

class Subject
{
public:
	int TestsCount = 0;
	string name;
	list <Test> Tests;

	Subject();
	~Subject();
};

