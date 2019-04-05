#include "MainHeader.h"
#include "Registration.h"
#include "Core.h"
#include "User.h"

Registration * RegSystem = Registration::GetInstance();
Core * CoreSystem = Core::GetInstance();

void FirstMenu();
void AdminMenu();
void PersonalOffice();
void SubjectsMenu(int _point = 0);
void TestsConstructorMenu();
void TestScroll(int _pointer, list<Subject> subjList);
void StartTest(string _nameTest, list<Subject> subjList);
void AddTestMenu();
void AddQuestions1();
void AddQuestions2(int _pointer, list<Subject> subjList);
void AddSubjectMenu();

void MainMenu()
{
	CoreSystem->UsersSynchronization(CoreSystem->getCurrentUser().login);
	RegSystem->SynchronizationSystemParams();

	char entered;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	while (true)
	{
		system("cls");

		cout << "\tWelcome " << CoreSystem->getCurrentUser().name << ".You ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << RegSystem->countOfLogin;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << " login user.\n";

		cout << "\t\tMain menu\n";
		cout << " 1) Tests\n";
		cout << " 2) Personal office\n";
		if (CoreSystem->getCurrentUser().isAdmin)
		{
			cout << " 3) Admin menu\n";
		}
		cout << " e) Back to login menu\n";

		Sleep(100);

		cin.clear();

		entered = _getch();
		cin.clear();
		switch (entered)
		{
			case '1':
			{
				SubjectsMenu();
				break;
			}
			case '2':
			{
				PersonalOffice();
				break;
			}
			case '3':
			{
				if (CoreSystem->getCurrentUser().isAdmin)
				{
					AdminMenu();
				}
				else
				{
					continue;
				}
			}
			case 'E':
			case 'e':
			{
				FirstMenu();
				break;
			}
			default:
				continue;
		}
	}
}

void SubjectsMenu(int _point)
{
	list<Subject> subjectList = CoreSystem->GetSubjectList();

	int pointer = _point;

	while (true)
	{
		int count = 0;

		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\tAll subjects\n";

		for (auto subj = subjectList.begin(); subj != subjectList.end(); subj++)
		{
			if (pointer == count)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << " + " << subj->name << "\n";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << " + " << subj->name << "\n";
			}
			count++;
		}
		Sleep(100);
		while (true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = CoreSystem->GetSubjectsCount()-1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer++;
				if (pointer == CoreSystem->GetSubjectsCount())
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				TestScroll(pointer,subjectList);
				break;
			}
			else if (GetAsyncKeyState(VK_ESCAPE))
			{
				MainMenu();
				break;
			}
		}
		Sleep(150);
	}
}
void TestScroll(int _pointer,list<Subject> subjList)
{
	int pointer = 0;
	string testName;
	int testsCount;

	while (true)
	{
		int count = 0;
		int count2 = 0;

		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\tAll subjects\n";

		for (auto subj = subjList.begin(); subj != subjList.end(); subj++)
		{
			if (count == _pointer)
			{
				testsCount = subj->TestsCount;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				cout << " + " << subj->name << "\n";
			}
			else 
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << " + " << subj->name << "\n";
			}

			if (count == _pointer)
			{
				if (subj->TestsCount != 0)
				{
					for (auto test = subj->Tests.begin(); test != subj->Tests.end(); test++)
					{
						if (pointer == count2)
						{
							testName = test->name;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
							cout << "   - " << test->name << "\n";
						}
						else
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << "   - " << test->name << "\n";
						}
						count2++;
					}
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					cout << "   - \n";
				}
			}

			count++;
		}
		Sleep(150);
		while (true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = testsCount-1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer++;
				if (pointer == testsCount)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				StartTest(testName, subjList);
				break;
			}
			else if (GetAsyncKeyState(VK_ESCAPE))
			{
				Sleep(100);
				SubjectsMenu(_pointer);
				break;
			}
		}
		Sleep(100);
	}
}
void StartTest(string _nameTest,list<Subject> subjList)
{
	int pointer = 0;
	int questCount = 1;
	int righAnswer = 0;

	bool enter = false;

	for (auto subj = subjList.begin(); subj != subjList.end(); subj++)
	{
		for (auto test = subj->Tests.begin(); test != subj->Tests.end(); test++)
		{
			if (test->name == _nameTest)
			{
				for (auto quest = test->Questions.begin(); quest != test->Questions.end(); quest++)
				{
					enter = false;
					pointer = 0;

					while(true)
					{
						int answCount = 0;
						system("cls");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << "\t\t\t" << questCount << "/" << test->QuestionsCount << endl;
						cout << " +++" << quest->_text << "+++\n";

						for (auto answ = quest->Answers.begin(); answ != quest->Answers.end(); answ++)
						{
							if (answCount == pointer)
							{
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
								cout << " " << *answ << endl;
							}
							else 
							{
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << " " << *answ << endl;
							}
							answCount++;
						}
						Sleep(150);
						while (true)
						{
							if (GetAsyncKeyState(VK_UP) != 0)
							{
								pointer--;
								if (pointer == -1)
								{
									pointer = quest->QuestionsCount-1;
								}
								break;
							}
							else if (GetAsyncKeyState(VK_DOWN) != 0)
							{
								pointer++;
								if (pointer == quest->QuestionsCount)
								{
									pointer = 0;
								}
								break;
							}
							else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
							{
								questCount++;

								if (pointer+1 == atoi(quest->correctAnswer.c_str()))
								{
									righAnswer++;

									User u = CoreSystem->getCurrentUser();
									u.rightAnswer++;
									CoreSystem->setCurrentUser(u);
									enter = true;
									
								}
								else
								{
									enter = true;
								}
								break;
							}
							else if (GetAsyncKeyState(VK_ESCAPE))
							{
								SubjectsMenu();
;								break;
							}
						}
						Sleep(100);
						if (enter)
							break;
					}
				}
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				system("cls");

				float r = righAnswer,q = test->QuestionsCount;

				cout << "\t\tRight answers " << righAnswer << "\\" << test->QuestionsCount << "  - " << r / q * 100 << "%\n" << endl;
				
				Sleep(2000);


			}
		}
	}
}

void TestsConstructorMenu() // New menu builder methods!
{
	string Menu_[4] = { "Add Subject.","Add Test.","Add Question.","e) Exit." };
	char entered;
	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\t\tTest constructor\n";
		for (int i = 0; i < (sizeof(Menu_) / sizeof(*Menu_)); i++)
		{
			if (i != (sizeof(Menu_) / sizeof(*Menu_))-1)
				cout << " " << i + 1 << ") " << Menu_[i] << endl;
			else
				cout << " " << Menu_[i] << endl;
		}

		Sleep(200);
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			AdminMenu();
		}

		entered = _getch();

		switch (entered)
		{
			case '1':
			{
				AddSubjectMenu();
				break;
			}
			case '2':
			{
				AddTestMenu();
				break;
			}
			case '3':
			{
				AddQuestions1();
				break;
			}
			default:
				continue;
		}
	}
}
void AddSubjectMenu()
{
	string subjName;

	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "\tAdd subject\n";
	cout << " Enter name subject: ";
	cin >> subjName;

	CoreSystem->AddSubject(subjName);

}
void AddTestMenu()
{
	int pointer = 0;
	int count = 0;

	string subjName;

	list<Subject> subjList = CoreSystem->GetSubjectList();
	while (true)
	{
		count = 0;

		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\tAll subjects\n";

		for (auto subj = subjList.begin(); subj != subjList.end(); subj++)
		{
			if (pointer == count)
			{
				subjName = subj->name;

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << " + " << subj->name << "\n";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << " + " << subj->name << "\n";
			}
			count++;
		}
		Sleep(100);
		while (true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = CoreSystem->GetSubjectsCount() - 1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer++;
				if (pointer == CoreSystem->GetSubjectsCount())
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				string testName;

				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "\tAdd new test --> ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << subjName; 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "." << endl;
				cout << " Enter test name: ";
				cin >> testName;


				CoreSystem->AddTest(subjName,testName);
				break;
			}
			else if (GetAsyncKeyState(VK_ESCAPE))
			{
				TestsConstructorMenu();
				break;
			}
		}
		Sleep(100);
	}

}
void AddQuestions1()
{
	list<Subject> subjectList = CoreSystem->GetSubjectList();

	int pointer = 0;

	while (true)
	{
		int count = 0;

		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\tAll subjects\n";

		for (auto subj = subjectList.begin(); subj != subjectList.end(); subj++)
		{
			if (pointer == count)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << " + " << subj->name << "\n";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << " + " << subj->name << "\n";
			}
			count++;
		}

		while (true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = CoreSystem->GetSubjectsCount() - 1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer++;
				if (pointer == CoreSystem->GetSubjectsCount())
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				AddQuestions2(pointer, subjectList);
				break;
			}
			else if (GetAsyncKeyState(VK_ESCAPE))
			{
				MainMenu();
				break;
			}
		}
		Sleep(150);
	}
}
void AddQuestions2(int _pointer, list<Subject> subjList)
{
	int pointer = 0;

	string subjName;
	string testName;

	bool flag = false;

	int testsCount;

	while (true)
	{
		int count = 0;
		int count2 = 0;

		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\tAll subjects\n";

		for (auto subj = subjList.begin(); subj != subjList.end(); subj++)
		{
			if (count == _pointer)
			{
				testsCount = subj->TestsCount;
				subjName = subj->name;

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				cout << " + " << subj->name << "\n";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << " + " << subj->name << "\n";
			}

			if (count == _pointer)
			{
				if (subj->TestsCount != 0)
				{
					for (auto test = subj->Tests.begin(); test != subj->Tests.end(); test++)
					{
						if (pointer == count2)
						{
							testName = test->name;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
							cout << "   - " << test->name << "\n";
						}
						else
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << "   - " << test->name << "\n";
						}
						count2++;
					}
				}
				else
				{
					flag = true;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					cout << "   - \n";
				}
			}

			count++;
		}
		Sleep(150);
		while (true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = testsCount - 1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer++;
				if (pointer == testsCount)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				Sleep(100);
				if (!flag)
				{
					bool exit = false;
					bool answFlag = false;

					string questionsText;
					list<string> answers;
					string rightAnswers;

					
					system("cls");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "\tAdd new questions --> ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << subjName << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "\t                        |\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << "\t                       " << testName << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

					cout << "\t\tEnter questions text: ";
					cin >> questionsText;

					system("cls");
					cout << "\t+ - Add new answer/Esc - To finish add answers\n";
					_getch();

					while (true)
					{
						system("cls");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << "\tAdd new questions --> ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						cout << subjName << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << "\t                        |\n";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						cout << "\t                       " << testName << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

						cout << "\t\t" << questionsText << endl;
						if (answers.size() != 0)
						{
							for (auto answ = answers.begin(); answ != answers.end(); answ++)
							{
								cout << "\t\t+ " << *answ << endl;
							}
						}
						Sleep(150);
						while (true)
						{
							char entered = _getch();
							if (entered == '+' )
							{
								answFlag = true;
								string newAsnwer;
								cout << "\t\t";
								cin >> newAsnwer;
								answers.push_back(newAsnwer);
								break;

							}
							else if (entered == 27)
							{
								exit = true;
								break;
							}
						}
						if (exit && answFlag)
							break;
						Sleep(150);
					}

					int bufInt;
					char buffer[256];

					cout << "---------------------------------------------\n";
					cout << "\tEnter right answer\n";

					cin >> bufInt;

					rightAnswers = _itoa(bufInt, buffer, 10);
					CoreSystem->AddQuestions(subjName, testName, questionsText, answers, rightAnswers);
				}
				break;
			}
			else if (GetAsyncKeyState(VK_ESCAPE))
			{
				Sleep(100);
				SubjectsMenu(_pointer);
				break;
			}
		}
		Sleep(100);
	}
}

void AdminMenu()
{
	char entered;

	while (true)
	{
		system("cls");

		cout << "\tAdmin menu\n";
		cout << " 1) Test constructor\n";
		cout << " 2) Delete User\n";
		if (CoreSystem->getCurrentUser().login == RegSystem->GetSuperAdminLogin())
		{
			cout << " 3) Give admin to User\n";
			cout << " 4) Take admin to User\n";
		}
		cout << " e) Back to main menu\n";
		Sleep(100);

		entered = _getch();

		switch (entered)
		{
			case '1':
			{
				TestsConstructorMenu();
				break;
			}
			case '2':
			{
				string login;

				system("cls");
				cout << "\tDelete user\n";
				cout << " Enter user login: ";
				cin >> login;
				
				if (RegSystem->IsExist(login))
				{
					CoreSystem->DeleteUser(login);
					system("cls");
					cout << "\t" << login << " have been deleted\n";
					_getch(); 
					break;
				}
				else
				{
					system("cls");
					cout << "\t" << login << " not found\n";
					_getch();
				}

				break;
			}
			case '3':
			{
				if (CoreSystem->getCurrentUser().login != RegSystem->GetSuperAdminLogin())
					break;

				string login;

				system("cls");
				cout << "\tGive admin\n";
				cout << " Who is this lucky: ";
				cin >> login;

				if (RegSystem->IsExist(login))
				{
					system("cls");
					CoreSystem->GiveAdmin(login);
					cout << "\tOtse " << login << " podfartilo\n";
					_getch();
					break;
				}
				else
				{
					system("cls");
					cout << "\t" << login << " not found\n";
					_getch();
				}
				break;
			}
			case '4':
			{
				if (CoreSystem->getCurrentUser().login != RegSystem->GetSuperAdminLogin())
					break;

				string login;

				system("cls");
				cout << "\tTake admin\n";
				cout << " Enter login: ";
				cin >> login;

				if (RegSystem->IsExist(login))
				{
					system("cls");
					CoreSystem->GiveAdmin(login);
					cout << "\tDone\n";
					_getch();
					break;
				}
				else
				{
					system("cls");
					cout << "\t" << login << " not found\n";
					_getch();
				}
				break;
			}
			case 27:
			{
				MainMenu();
				break;
			}
			case 'e':
			{
				MainMenu();
				break;
			}
			default:
				continue;
		}
	}
}
void PersonalOffice()
{
	char entered;

	
	system("cls");

	cout << "\t" << CoreSystem->getCurrentUser().name << " personal office\n\n";
	cout << " Login" << " - " << CoreSystem->getCurrentUser().login << endl;

	cout << " Password" << " - ";
	for (int i = 0; i < CoreSystem->getCurrentUser().password.size();i++)
	{
		if (i >= 2 && i < CoreSystem->getCurrentUser().password.size() - 2)
			cout << "*";
		else
			cout << CoreSystem->getCurrentUser().password[i];
	}
	cout << endl;

	cout << " Name" << " - " << CoreSystem->getCurrentUser().name << endl;
	cout << " Right answers" << " - " << CoreSystem->getCurrentUser().rightAnswer << endl;
	cout << " Admin Rights" << " - ";

	CoreSystem->getCurrentUser().isAdmin ? cout << "Yes\n" : cout << "No\n";

	cout << " Phonenumber" << " - " << CoreSystem->getCurrentUser().phone << endl;
	cout << endl;
	cout << " 1) Change password\n";


	entered = _getch();

	switch (entered)
	{
		case '1':
		{
			string existPassword,newPassword;

			system("cls");
			cout << "\tChange password\n";
			cout << " Enter exist password: ";
			cin >> existPassword;
			cout << " Enter new password: ";
			cin >> newPassword;

			if (existPassword == CoreSystem->getCurrentUser().password && RegSystem->CheckPassword(newPassword))
			{
				CoreSystem->ChangePassword(newPassword);
				system("cls");
				cout << "\t\tDone!\n";
				_getch();
				break;
			}
			else
			{
				system("cls");
				cout << "\t\tYour password or exist password wrong.\n";
				_getch();
				break;
			}
			break;
		}
	}
	
}

void RegistrationMenu()
{

	string login, name, password, phoneNumber;
	while (true)
	{
		system("cls");

		cout << "\tRegistration\n";
		cout << " Enter login: ";
		cin >> login;
		cout << " Enter name: ";
		cin >> name;
		cout << " Enter password: ";
		cin >> password;
		cout << " Enter phonenumber: ";
		cin >> phoneNumber;

		cout << "\t\t\t";
		for (int i = 0; i < 3; i++)
		{
			cout << "* ";
			Sleep(500);
		}
		cout << endl;

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			system("exit");
		}

		if (!RegSystem->CheckLogin(login))
		{
			system("cls");
			cout << "\tYour login not suitable.Please enter new login\n";
			_getch();
			continue;
		}

		if (!RegSystem->CheckPassword(password))
		{
			system("cls");
			cout << "\tYour password not suitable.Please enter new password\n";
			_getch();
			continue;
		}

		if (RegSystem->IsExist(login, password))
		{
			system("cls");
			cout << "\tAn account already exists\n";
			_getch();
		}
		else
		{
			CoreSystem->setCurrentUser(RegSystem->InputRegistrat(login, name, password, phoneNumber));
			MainMenu();
		}
	}
}
void LoginMenu()
{
	char entered;
	string login, password;

	while (true)
	{
		system("cls");
		cout << "\tLogin\n";
		cout << " Enter login: ";
		cin >> login;
		cout << " Enter password: ";
		cin >> password;

		if (RegSystem->IsExist(login, password))
		{
			CoreSystem->setCurrentUser(RegSystem->InputLogin(login, password));
			MainMenu();
		}
		else
		{
			system("cls");
			cout << "\tLogin or password wrong\n";
			cout << "\tMaybe you want to register?\n";
			cout << "\t\tY/N\n";
			entered = _getch();
			switch (entered)
			{
				case 'y':
				case 'Y':
				{
					RegistrationMenu();
					break;
				}

				default:
				case 'n':
				case 'N':
				{
					continue;
				}
			}
		}
		
	}
}

void FirstMenu()
{
	char entered;

	while (true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		system("cls");

		cout << "\tWelcome to super test program\n";
		cout << " 1) Login.\n";
		cout << " 2) Registration.\n";
	
		entered = _getch();

		switch (entered)
		{
			case '1':
			{
				LoginMenu();
				break;
			}
			case '2':
			{
				RegistrationMenu();
				break;
			}
			default:
				continue;
		}
	}
}