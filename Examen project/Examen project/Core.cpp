#include "Core.h"

Registration *RegSystem_ = Registration::GetInstance();

string MoveStringToLeft(string truthString, int count)
{
	string newString;
	
	for (int i = 0; i < truthString.size() - count; i++)
	{
		newString += " ";
	}

	for (int i = 0; i < truthString.size()-count; i++)
	{
		newString[i] = truthString[i + count];
	}

	return newString;
}
string MoveStringToRight(string truthString, int count)
{
	string newString;

	for (int i = 0; i < truthString.size()+count; i++)
	{
		newString += " ";
	}

	for (int i = 0; i < truthString.size(); i++)
	{
		newString[i+count] = truthString[i];
	}

	return newString;
}

User Core::getCurrentUser() { return currentUser; }
void Core::setCurrentUser(User _currentUser) { currentUser = _currentUser; }

void Core::UsersSynchronization(string _login)
{
	list<string> usersData;
	string buf;
	char buffer[256];

	ifstream fin(usersPath, ifstream::in);
	
	while (fin.peek() != EOF) // Спочатку все виводимо з файлу
	{
		getline(fin, buf);
		usersData.push_back(buf);
	}

	fin.close();

	for (auto _str = usersData.begin(); _str != usersData.end(); _str++)
	{ 
		if (*_str == currentUser.login)
		{
			*_str = currentUser.login;
			
			++(_str);
			*_str = currentUser.password;

			++(_str);
			*_str = currentUser.name;
			
			++(_str);
			*_str = _itoa(currentUser.rightAnswer,buffer,10);
			
			++(_str);
			*_str = _itoa(currentUser.isAdmin,buffer,10);
			
			++(_str);
			*_str = currentUser.phone;

			break;
		}
	}


	SaveUsersInFile(usersData);
}
void Core::GiveAdmin(string _login)
{
	if (_login == RegSystem_->GetSuperAdminLogin())
		return;

	list<string> usersData;
	string buf;
	char buffer[256];

	ifstream fin(usersPath, ifstream::in);

	while (fin.peek() != EOF) // Спочатку все виводимо з файлу
	{
		getline(fin, buf);
		usersData.push_back(buf);
	}

	fin.close();

	for (auto _str = usersData.begin(); _str != usersData.end(); _str++)
	{
		if (*_str == _login)
		{
            ++(_str);
			++(_str);
			++(_str);
			++(_str);
			if (*_str == "0")
				*_str = _itoa(1, buffer, 10);
			else
				*_str = _itoa(0, buffer, 10);

			break;
		}
	}

	SaveUsersInFile(usersData);
}
void Core::DeleteUser(string _login)
{

	if (_login == RegSystem_->GetSuperAdminLogin())
		return;

	list<string> usersData;

	string buf;

	ifstream fin(usersPath, ifstream::in);

	while (fin.peek() != EOF) // Спочатку все виводимо з файлу
	{
		getline(fin, buf);
		if (buf == _login)
		{
			for (int i = 0; i < 5; i++)
				getline(fin, buf);
		}
		usersData.push_back(buf);
	}

	fin.close();

	SaveUsersInFile(usersData);
}
void Core::ChangePassword(string _newPassword)
{
	list<string> usersData;

	string buf;

	ifstream fin(usersPath, ifstream::in);

	while (fin.peek() != EOF) // Спочатку все виводимо з файлу
	{
		getline(fin, buf);
		if (buf == currentUser.login)
		{
			usersData.push_back(buf);
			getline(fin, buf);
			buf = _newPassword;
		}
		usersData.push_back(buf);
	}

	fin.close();

	SaveUsersInFile(usersData);
}


void Core::SaveUsersInFile(list<string> usersData)
{
	ofstream fout(usersPath, ofstream::out);

	for (auto _str = usersData.begin(); _str != usersData.end(); _str++)
	{
		fout << *_str << endl;
	}

	fout.close();

}


int Core::GetSubjectsCount()
{
	return SubjectsCount;
}

void Core::AddSubject(string _name)
{
	bool flag = false;
	for (auto subj = allSubjects.begin(); subj != allSubjects.end(); subj++)
	{
		if (subj->name == _name)
			flag = true;
	}

	if (flag)
		return;

	Subject s;
	s.name = _name;
	SubjectsCount++;
	allSubjects.push_back(s);

	SynchronizationSubject();
}
void Core::AddTest(string _subjectName, string _name)
{
	bool testFlag = false,subjectFlag = false;
	for (auto subj = allSubjects.begin(); subj != allSubjects.end(); subj++)
	{
		if (subj->name == _subjectName)
			subjectFlag = true;

		for (auto test = subj->Tests.begin(); test != subj->Tests.end(); test++)
		{
			if (test->name == _name)
				testFlag = true;
		}
	}
	
	if (testFlag || !subjectFlag)
		return;

	Test t;
	t.name = _name;

	for (auto subj = allSubjects.begin(); subj != allSubjects.end(); subj++)
	{
		if (subj->name == _subjectName)
		{
			subj->TestsCount++;
			subj->Tests.push_back(t);
		}
	}

	SynchronizationSubject();

}
void Core::AddQuestions(string _subjName,string _testName, string textQuest, list<string> _answers, string _rightAnswer)
{
	bool subjFlag = false, testFlag = false;

	for (auto subj = allSubjects.begin(); subj != allSubjects.end(); subj++)
	{

		if (subj->name == _subjName)
			subjFlag = true;

		for (auto test = subj->Tests.begin(); test != subj->Tests.end(); test++)
		{
			if (test->name == _testName)
				testFlag = true;
		}
	}

	if (!subjFlag || !testFlag)
		return;

	Question q;
	q._text = textQuest;
	q.correctAnswer = _rightAnswer;
	for (auto a = _answers.begin(); a != _answers.end(); a++)
	{
		q.Answers.push_back(*a);
		q.QuestionsCount++;
	}

	for (auto subj = allSubjects.begin(); subj != allSubjects.end(); subj++)
	{
		for (auto test = subj->Tests.begin(); test != subj->Tests.end(); test++)
		{
			if (test->name == _testName && subj->name == _subjName)
			{
				test->QuestionsCount++;
				test->Questions.push_back(q);
			}
		}
	}

	SynchronizationSubject();
}

list<Subject> Core::GetSubjectFromFile()
{
	ifstream fin(filePath, ifstream::in);

	string buf;

	list<Subject> returnSubjects;

	// !ОБЕРЕЖНО! ГОВНОКОД 18+
	while (fin.peek() != EOF)
	{
		//-------------------------
		//----------Subjects-------

		if (buf[0] != ':')
			getline(fin, buf);

		if (buf[0] == ':')
		{
#pragma region Subject 
			Subject s;

			SubjectsCount++;


			buf = MoveStringToLeft(buf, 1);
			s.name = buf;
			while (true)
			{
				//---------------------
				//-------Tests---------
				
				if (buf[0] == ':')
					break;

				if (buf[0] != '-')
					getline(fin, buf);

				if (buf[0] == '-')
				{
	#pragma region Test
					s.TestsCount++;
					Test t;

					buf = MoveStringToLeft(buf, 1);
					t.name = buf;
					
					//----------------
					//-------Questions
					while (true) // here
					{
						if (buf[0] != '|')
							getline(fin, buf);

					
						if (buf[0] == '|')
						{
#pragma region Questions
							t.QuestionsCount++;

							Question q;

							buf = MoveStringToLeft(buf, 1);
							q._text = buf;
							//-----------
							//--Answers--
							while (true)
							{
								getline(fin, buf);

						        if (buf[0] == '&' && buf[1] == ':')
						        {
									buf = MoveStringToLeft(buf, 2);
						        
						        	q.correctAnswer = buf;
									
									break;
						        }
								else if (buf[0] == '&') 
								{
									buf = MoveStringToLeft(buf, 1);
									q.QuestionsCount++;
									q.Answers.push_back(buf);
								}
								else
								{
									break;
								}
							} 
							t.Questions.push_back(q);
#pragma endregion
						}
						else 
						{
							break;
						}
						
					}
					s.Tests.push_back(t);
	#pragma endregion
				}
				else
				{
					break;
				}
			} 
			returnSubjects.push_back(s);
#pragma endregion
		} 
	} 

	fin.close();
	return returnSubjects;
}
list<Subject> Core::GetSubjectList()
{
	return allSubjects;
}
void Core::SynchronizationSubject()
{
	list<string> bufSubjects;
	string buf;

	for (auto subj = allSubjects.begin(); subj != allSubjects.end(); subj++)
	{
		buf = subj->name;
		buf = MoveStringToRight(buf, 1);
		buf[0] = ':';
		bufSubjects.push_back(buf);

		for (auto test = subj->Tests.begin(); test != subj->Tests.end(); test++)
		{
			buf = test->name;
			buf = MoveStringToRight(buf, 1);
			buf[0] = '-';
			bufSubjects.push_back(buf);

			for (auto quest = test->Questions.begin(); quest != test->Questions.end(); quest++)
			{
				buf = quest->_text;
				buf = MoveStringToRight(buf, 1);
				buf[0] = '|';
				bufSubjects.push_back(buf);

				for (auto answ = quest->Answers.begin(); answ != quest->Answers.end(); answ++)
				{
					buf = *answ;
					buf = MoveStringToRight(buf, 1);
					buf[0] = '&';
					bufSubjects.push_back(buf);
				}

				buf = quest->correctAnswer;
				buf = MoveStringToRight(buf, 2);
				buf[0] = '&';
				buf[1] = ':';
				bufSubjects.push_back(buf);
			}
		}
	}
	ofstream fout(filePath, ofstream::out);

	for (auto _str = bufSubjects.begin(); _str != bufSubjects.end(); _str++)
	{
		fout << *_str << endl;
	}

	fout.close();
	GetSubjectFromFile();
}

Core::Core()
{
	allSubjects = GetSubjectFromFile();
	/*for (auto subj = allSubjects.begin(); subj != allSubjects.end(); subj++)
	{
		cout << subj->name << endl;
	}
	system("pause");*/
}
Core::~Core()
{
}

Core *Core::instance = NULL;