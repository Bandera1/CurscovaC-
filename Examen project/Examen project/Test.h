#pragma once
#include "MainHeader.h"
#include "Question.h"

class Test
{
public:
	int QuestionsCount = 0;
	string name;
	list <Question> Questions;

	Test();
	~Test();
};

