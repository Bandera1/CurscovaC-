#pragma once
#include "MainHeader.h"

class Question
{
public:
	string _text;
	list <string> Answers;
	int QuestionsCount = 0;
	string correctAnswer;

	Question();
	~Question();
};

