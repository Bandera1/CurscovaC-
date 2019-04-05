#pragma once
#include "MainHeader.h"
#include "User.h"
#include "Subject.h"
#include "Registration.h"

class Core
{
	Core();
	static Core * instance;

	User currentUser;

	string filePath = "testsData.txt";
	string usersPath = "userData.txt";

	int SubjectsCount = 0;
	list<Subject> allSubjects;
public:
	User getCurrentUser();
	void setCurrentUser(User _currentUser);

	void UsersSynchronization(string _login);
	void GiveAdmin(string _login);
	void DeleteUser(string _login);
	void ChangePassword(string _newPassword);

	void SaveUsersInFile(list<string> usersData);

	int GetSubjectsCount();

	//void DeleteSubject(string _subjectName);

	void AddSubject(string _name);
	void AddTest(string _subjectName,string _name);
	void AddQuestions(string _subjName,string _testName,string textQuest,list<string> _answers,string _rightAnswer);

	list<Subject> GetSubjectFromFile();
	list<Subject> GetSubjectList();
	void SynchronizationSubject();

	static Core * GetInstance()
	{
		if (instance == NULL)
		{
			instance = new Core();
		}
		return instance;
	}
	~Core();
};
