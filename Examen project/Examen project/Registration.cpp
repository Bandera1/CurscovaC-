#include "Registration.h"

User Registration::InputLogin(string _login, string _password)
{
	User inputUser;

	countOfLogin++;
	inputUser = GetFromFile(_login);

	return inputUser;
}

User Registration::InputRegistrat(string _login,string _name, string _password, string _phoneNumber)
{
	User inputUser;

	SaveToFile(_login,_name,_password,_phoneNumber);
	
	return inputUser = GetFromFile(_login);
}

bool Registration::CheckLogin(string _login)
{
	
	char blockSymbols[] = { '//','\\','[',']',':',';','=',',','+','*','?','<','>',' ' };

	if (_login == superAdminLogin || _login.size() > 20 || _login.size() < 5)
		return false; 

	for (int i = 0; i < _login.size(); i++)
	{
		for (int j = 0; j < strlen(blockSymbols); j++)
		{
			if (_login[i] == blockSymbols[j])
				return false;
		}
	}

	return true;
}
bool Registration::CheckPassword(string _password)
{
	if (_password == "communism" || _password == "Communism")
	{
		system("cls");
		cout << "\tHA-HA-HA\n";
		cout << " It`s password didn`t work\n";
		Sleep(2000);
		cout << "\tOMG,WHAT HAPPENEND	?\n";
		Sleep(800);
		system("cls");
		mciSendString("open \"USSR.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
		mciSendString("play mp3", NULL, 0, NULL);
		system("color 4C");
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout <<	"%%%%%%%%%%%%%%%%%%%%%%%%%(#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%#&&*%&%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%#%%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%, %%*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%(%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%#####%%%##%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%#####%%%%%%## / %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%#######(%%%%%%##%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%#%%%####%%%%##(%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%##%####%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%(###%%%%(#####%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%##*%###########%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%####%%%%%%%%%%%%####%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%*#%%%%%%%%%%%%%%%%*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		_getch();
		system("exit");
	}
	else if (_password == "USA" || _password == "usa" || _password == "America" || _password == "america" || _password == "OIL")
	{
		system("cls");
		cout << "\tOH SHIT\n";
		cout << " WHERE`S MY OIL\n";
		Sleep(2000);
		cout << "\tOMG,WHAT HAPPENEND	?\n";
		cout << "\tNOOOOOOOOOO\n";
		Sleep(800);
		system("cls");
		mciSendString("open \"USA.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
		mciSendString("play mp3", NULL, 0, NULL);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "| ** * * * * * * * * OOOOOOOOOOOOOOOOOOOOOOOOO|" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "| ** * * * * * * *   :::::::::::::::::::::::::| " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "|** * * * * * * * *  OOOOOOOOOOOOOOOOOOOOOOOOO|" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "| ** * * * * * * *   :::::::::::::::::::::::: |" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "|** * * * * * * * *  OOOOOOOOOOOOOOOOOOOOOOOOO|" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "| ** * * * * * * *  ::::::::::::::::::::::::::|" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "|** * * * * * * * *  OOOOOOOOOOOOOOOOOOOOOOOOO|" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "|:::::::::::::::::::::::::::::::::::::::::::::|" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "|OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO|" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "|:::::::::::::::::::::::::::::::::::::::::::::|" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "|OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO|" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "|:::::::::::::::::::::::::::::::::::::::::::::|" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "|OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO|" << endl;

		_getch();
		system("exit");
	}
	if (_password.size() < 8 || _password.size() >= 128)
		return false;

	return true;
}

string Registration::GetSuperAdminLogin()
{
	return superAdminLogin;
}

void Registration::LoadSystemParams()
{
	string buf = "";
	ifstream fin(paramsPath, ifstream::in);

	getline(fin, buf);
	countOfLogin = atoi(buf.c_str());

	fin.close();
}

void Registration::SynchronizationSystemParams()
{
	ofstream fout(paramsPath, ofstream::out);

	fout << countOfLogin << endl;
}

void SaveToFile(string _login, string _name, string _password, string _phoneNumber)
{
	ofstream fout("userData.txt",ofstream::app);

	char buffer[256];
	string str;

	fout << _login << endl;
	fout << _password << endl;
	fout << _name << endl;
	str = _itoa(0, buffer, 10);
	fout << str << endl;
	fout << str << endl;
	fout << _phoneNumber << endl;

	fout.close();
}

User GetFromFile(string _login)
{
	User bufUser;

	ifstream fin("userData.txt", ifstream::in);

	string buf = "";

	for (int i = 0; fin.peek() != EOF; i++)
	{
		if (i % 5 == 0 || i == 0)
		{
			getline(fin, buf);
			if (buf == _login)
			{
				bufUser.login = buf;
				
				getline(fin, buf);
				bufUser.password = buf;

				getline(fin, buf);
				bufUser.name = buf;
				

				getline(fin, buf);
				bufUser.rightAnswer = atoi(buf.c_str());
				

				getline(fin, buf);
				bufUser.isAdmin = atoi(buf.c_str());
				

				getline(fin, buf);
				bufUser.phone = buf;
				

				return bufUser;

			}
		}
	}
	return User();
}

bool Registration::IsExist(string _login,string _password)
{
	ifstream fin("userData.txt", ifstream::in);

	string bufLogin,bufPasswd;
	bool lgin = false,passwd = false;

	for (int i = 0; fin.peek() != EOF;i++)
	{
		getline(fin, bufLogin);
		if (i % 3 == 0 || i == 0)
		{  
			if (bufLogin == _login)
			{
				if (_password == "none")
					return true;
				lgin = true;
			}
		}

		getline(fin, bufPasswd);
		
		if (bufPasswd == _password)
				passwd = true;

		if (lgin && passwd)
			return true;

	}
	fin.close();
	return false;
}

Registration::Registration()
{
	LoadSystemParams();
}
Registration::~Registration()
{
}

Registration *Registration::instance = NULL;