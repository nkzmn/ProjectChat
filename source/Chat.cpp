#include "Chat.h"

void Chat::startChat()
{
	_isChatWork = true;
}

void Chat::showLoginMenu()
{
	_currentUser = nullptr;
	char operation;
<<<<<<< HEAD
<<<<<<< HEAD
	std::cout << "\t\tChat 1.0 is run.\n\a";
=======
	std::cout << "\t\tChat 2.0 is run.\n\a";
>>>>>>> master
=======
	std::cout << "\t\tChat 2.0 is run.\n\a";
>>>>>>> master
	do
	{
		
		std::cout << "\n(1)SignUp\t";
		std::cout << "(2)Login\t";
		std::cout << "(0)ShutDown\n>> ";
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			try
			{
				singUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case '2':
			login();
			break;
		case'0':
			_isChatWork = false;
			break;
		default:
			std::cout << "1 or 2..." << std::endl;
			break;
		}
	} while (!_currentUser && _isChatWork);
}

void Chat::showUserMenu()
{
	char operation;
	std::cout << "Hi, " << _currentUser->getUserName()<<".\n";

	while (_currentUser)
	{
		std::cout << "Menu:(1)Show chat | (2)Add message | (3)Users | (4)Delete last message | (0)Logout" << "\n>> ";
		std::cin >> operation;
		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case '4':
			deleteLastMessage();
			break;
		case '0':
			_currentUser = nullptr;
			break;
		default:
			std::cout << "Unknown choice.." << std::endl;
			break;
		}
	}
}

void Chat::showAllUsersName() const
{
	std::locale::global(std::locale("en_US.UTF-8"));
	uint32_t Spades = 0x2642;
	uint32_t Spades1 = 0x2640;

	std::cout << "--- Users ---" << std::endl;

<<<<<<< HEAD
<<<<<<< HEAD
	for (const auto& user : _users)
	{
		std::wcout << (user.getUserGender() == "Male" ? (wchar_t)Spades : (wchar_t)Spades1) << " ";
		std::cout << user.getUserName();

		if (_currentUser->getUserLogin() == user.getUserLogin())
=======
=======
>>>>>>> master
	std::ifstream user_file("users.txt");

	std::string login;
	std::string password;
	std::string name;
	std::string gender;

	while (user_file >> login >> password >> name >> gender)
	{
		User user(login, password, name, gender);

		if (user.getUserGender() == "Male")
			std::wcout << (wchar_t)Spades << " ";
		else if (user.getUserGender() == "Female")
			std::wcout << (wchar_t)Spades1 << " ";

		std::cout << user.getUserName();

		if (login == _currentUser->getUserLogin())
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
			std::cout << "(me)";

		std::cout << std::endl;
	}

	std::cout << "----------" << std::endl;
}

void Chat::singUp()
{
<<<<<<< HEAD
<<<<<<< HEAD
	std::string login, name, gender;
	std::vector<char> password;
	std::cout << "Login: ";
	std::cin >> login;
	std::cout << "Password: ";
	char c;
	while ((c = _getch()) != '\r')
	{
		password.push_back(c);
		_putch('*');
	}
	std::cout << "\nName: ";
=======
=======
>>>>>>> master
	std::string login, name, gender, password;
	std::cout << "Login: ";
	std::cin >> login;
	std::cout << "Password: ";
	std::cin >> password;
	std::cout << "Name: ";
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
	std::cin >> name;
	std::cout << "Gender:";

	do
	{
		std::cout << "\n(Male,Female) ";
		std::cin >> gender;
		if (!(gender == "Male" || gender == "Female"))
			std::cout << "Enter Male or Female";
	} while (!(gender == "Male" || gender == "Female"));

	if (getUserByLogin(login) || login == "All")
		throw UserLoginExp();
	if (getUserByName(name) || name == "All")
		throw UserNameExp();

	User user(login, password, name, gender);
	_users.push_back(user);
	_currentUser = std::make_shared<User>(user);
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> master

	if (!user_file)
		user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);

	if (user_file)
	{
		User obj(login, password, name, gender);
		user_file << obj << std::endl;
	}
	else
		std::cout << "Could not open file users.txt!" << std::endl;
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
}


void Chat::login()
{
	std::string login;
<<<<<<< HEAD
<<<<<<< HEAD
	std::vector <char> password;
	char operation;
	char ñ;
=======
	std::string password;
	char operation;

>>>>>>> master
=======
	std::string password;
	char operation;

>>>>>>> master
	do
	{
		std::cout << "Login: ";
		std::cin >> login;
<<<<<<< HEAD
<<<<<<< HEAD
		_currentUser = getUserByLogin(login);
		std::cout << "Password: ";
		while ((ñ = _getch()) != '\r')
		{
			password.push_back(ñ);
			_putch('*');
		}
		std::cout << "\n";
		if (_currentUser == nullptr || (password != _currentUser->getUserPassword()))
		{
			_currentUser=nullptr;

				std::cout << "Login invalid."<<std::endl;
				std::cout << "(0)exit or any key to return menu: ";
				std::cin >> operation;

				if(operation=='0')
					break;
		}
=======
=======
>>>>>>> master

		_currentUser = getUserByLogin(login);
		if (_currentUser == nullptr)
		{
			std::cout << "Login invalid." << std::endl;
			std::cout << "(0)exit or any key to return menu: ";
			std::cin >> operation;

			if (operation == '0')
				break;

			continue;
		}

		std::cout << "Password: ";
		std::cin >> password;

		if (password != _currentUser->getUserPassword())
		{
			_currentUser = nullptr;

			std::cout << "Login invalid." << std::endl;
			std::cout << "(0)exit or any key to return menu: ";
			std::cin >> operation;

			if (operation == '0')
				break;
		}

<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
	} while (!_currentUser);
}

void Chat::showChat() const
{
<<<<<<< HEAD
<<<<<<< HEAD
	std::string from,to;

	std::cout << "Chat 1.0 "<<std::endl;

	for (auto &mess:_messages)
	{
		if(_currentUser->getUserLogin()==mess.getFrom()|| _currentUser->getUserLogin() == mess.getTo()||mess.getTo() == "All")
		{
			from = (_currentUser->getUserLogin() == mess.getFrom()) ? "Me" : getUserByLogin(mess.getFrom())->getUserName();
			if (mess.getTo() == "All")
=======
=======
>>>>>>> master
	std::string from, to, text;

	std::cout << "____START____ "<<std::endl;

	std::ifstream messagesFile("messages.txt");
	if (!messagesFile.is_open())
	{
		std::cout << "Error opening file!" << std::endl;
		return;
	}

	while (getline(messagesFile, from, ' ') && getline(messagesFile, to, ' ') && getline(messagesFile, text))
	{
		if (_currentUser->getUserLogin() == from || _currentUser->getUserLogin() == to || to == "All")
		{
			from = (_currentUser->getUserLogin() == from) ? "Me" : getUserByLogin(from)->getUserName();
			if (to == "All")
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
			{
				to = "All";
			}
			else
			{
<<<<<<< HEAD
<<<<<<< HEAD
				to = (_currentUser->getUserLogin() == mess.getTo()) ? "Me" : getUserByLogin(mess.getTo())->getUserName();
			}

			std::cout << "Message from " << from << " to " << to << std::endl;
			std::cout << "Text: "<<mess.getText() << std::endl;
		}
	}
=======
=======
>>>>>>> master
				to = (_currentUser->getUserLogin() == to) ? "Me" : getUserByLogin(to)->getUserName();
			}

			std::cout << "Message from " << from << " to " << to << std::endl;
			std::cout << "Text: " << text << std::endl;
		}
	}

	messagesFile.close();

<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
	std::cout << "____END____ " << std::endl;
}

void Chat::addMessage()
{
	std::string to, text;

	std::cout << "To (name or All): ";
	std::cin >> to;
	std::cout << "Text: ";
	std::cin.ignore();
	std::getline(std::cin, text);

<<<<<<< HEAD
<<<<<<< HEAD
	if (!(to == "all" || to == "All" || getUserByName(to)))
	{
		std::cout << "error send message: can't find " << to << std::endl;
		return;
	}

	if (to == "All" || to == "all")
		_messages.emplace_back(_currentUser->getUserLogin(), "All", text);
		
	else
		_messages.emplace_back(_currentUser->getUserLogin(), getUserByName(to)->getUserLogin(), text);
=======
=======
>>>>>>> master
	if (to == "All" || to == "all")
	{
		Message message(_currentUser->getUserLogin(), "All", text);
		_messages.push_back(message);

		msg_file << message << std::endl;
		msg_file.close();
	}
	else
	{
		std::ifstream users_file("users.txt");
		std::string login, password, name, gender;

		bool found = false;
		while (users_file >> login >> password >> name >> gender) 
		{
			if (name == to) 
			{
				found = true;
				Message message(_currentUser->getUserLogin(), login, text);
				_messages.push_back(message);

				msg_file << message << std::endl;
				msg_file.close();

				break;
			}
		}
		users_file.close();

		if (!found)
		{
			std::cout << "Error: user not found\n";
			return;
		}
	}
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
}

void Chat::deleteLastMessage()
{
	if (!(_messages.empty()))
	{
		Message s = _messages.back();

		if ((_currentUser->getUserName() == "Admin") || (s.getFrom() == _currentUser->getUserLogin()))
		{
			_messages.pop_back();
			std::cout << std::endl << "Message was deleted." << std::endl;
		}
		else
		{
			std::cout << "Not enough rights to delete." << std::endl;
		}
	}
	std::cout << "Chat is empty!" << std::endl;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
<<<<<<< HEAD
<<<<<<< HEAD
	for (auto& user : _users)
	{
		if (login == user.getUserLogin())
			return std::make_shared<User>(user);
=======
=======
>>>>>>> master
	std::ifstream user_file("users.txt");
	if (!user_file.is_open())
	{
		std::cout << "Error opening users file." << std::endl;
		return nullptr;
	}

	std::string userLogin;
	std::string userPassword;
	std::string userName;
	std::string userGender;

	while (user_file >> userLogin >> userPassword >> userName >> userGender)
	{
		if (userLogin == login)
		{
			return std::make_shared<User>(userLogin, userPassword, userName, userGender);
		}
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
	}
	return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
{
	for (auto& user : _users)
	{
		if (name == user.getUserName())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> master
std::fstream& operator >>(std::fstream& is, User& obj)
{
	is >> obj._name;
	is >> obj._login;
	is >> obj._password;
	is >> obj._gender;
	return is;
}
std::ostream& operator <<(std::ostream& os, const User& obj)
{
	os << obj._login;
	os << ' ';
	os << obj._password;
	os << ' ';
	os << obj._name;
	os << ' ';
	os << obj._gender;
	return os;
}

std::ostream& operator <<(std::ostream& os, const Message& msg)
{
	os << msg._from;;
	os << ' ';
	os << msg._to;
	os << ' ';
	os << msg._text;
	return os;
<<<<<<< HEAD
}
>>>>>>> master
=======
}
>>>>>>> master
