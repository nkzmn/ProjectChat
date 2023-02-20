#include<iostream>
#include"Chat.h"
#include "User.h"
#include <io.h>
#include <fcntl.h>
#include <locale.h>
#include <fcntl.h>
#include <iostream>


void Chat::startChat()
{
	_isChatWork = true;
}

void Chat::showLoginMenu()
{
	_currentUser = nullptr;
	char operation;
	std::cout << "Chat 1.0 is run.\n";
	do
	{
		
		std::cout << "(1)Login\n";
		std::cout << "(2)SingUp\n";
		std::cout << "(0)ShutDown\n";
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				singUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
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
	std::cout << "Hi, " << _currentUser->getUserName()<<endl;

	while (_currentUser)
	{
		std::cout << "Menu:(1)Show chat | (2)Add message | (3)Users | (4)Delete last message | (0)Logout" << std::endl << ">> ";
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
	std::cout << "--- Users ---" << std::endl;
	for (auto& user : _users)
	{
		
		if (user.getUserGender()=="Male")
		{
			std::cout << u8"\u2626" << " ";
		}
		else
		{
			std::cout << u8"\u2641" << " ";
		}
		std::cout <<user.getUserName();

		if (_currentUser->getUserLogin() == user.getUserLogin())
			std::cout << "(me)";

		std::cout << std::endl;
	}
	std::cout << "----------" << std::endl;
}


void Chat::login()
{
	std::string login, password;
	char operation;
	do
	{
		std::cout << "Login: ";
		std::cin >> login;
		std::cout << "Password: ";
		std::cin >> password;

		_currentUser = getUserByLogin(login);

		if (_currentUser == nullptr || (password != _currentUser->getUserPassword()))
		{
			_currentUser=nullptr;

				std::cout << "Login invalid."<<std::endl;
				std::cout << "(0)exit or any key to return menu: ";
				std::cin >> operation;

				if(operation=='0')
					break;
		}
	} while (!_currentUser);
}

void Chat::singUp()
{

	std::string login, password,name, gender;

	std::cout << "Login: ";
	std::cin >> login;
	std::cout << "Password: ";
	std::cin >> password;
	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "Gender:(Male,Female) ";
	do
	{
		std::cin >> gender;
	} while (!(gender=="Male"|| gender == "Female"));
	

	if (getUserByLogin(login) || login == "All")
	{
		throw UserLoginExp();
	}
	if (getUserByName(name) || name == "All")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name, gender);
	_users.push_back(user);
	_currentUser = std::make_shared<User>(user);

}

void Chat::showChat() const
{
	std::string from,to;

	std::cout << "Chat 1.0 "<<std::endl;

	for (auto &mess:_messages)
	{
		if(_currentUser->getUserLogin()==mess.getFrom()|| _currentUser->getUserLogin() == mess.getTo()||mess.getTo() == "All")
		{
			from = (_currentUser->getUserLogin() == mess.getFrom()) ? "Me" : getUserByLogin(mess.getFrom())->getUserName();
			if (mess.getTo() == "All")
			{
				to = "All";
			}
			else
			{
				to = (_currentUser->getUserLogin() == mess.getTo()) ? "Me" : getUserByLogin(mess.getTo())->getUserName();
			}

			std::cout << "Message from " << from << " to " << to << std::endl;
			std::cout << "Text: "<<mess.getText() << std::endl;
		}
	}
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

	if (!(to == "all" || to == "All" || getUserByName(to)))
	{
		std::cout << "error send message: can't find " << to << std::endl;
		return;
	}

	if (to == "All" || to == "all")
		_messages.push_back(Message{ _currentUser->getUserLogin(), "All", text });
		
	else
		_messages.push_back(Message{ _currentUser->getUserLogin(), getUserByName(to)->getUserLogin(), text });
}

void Chat::deleteLastMessage()
{
	if (!(_messages.empty()))
	{
		Message s = _messages.back();

		if ((_currentUser->getUserName() == "Admin") || (s.getFrom() == _currentUser->getUserLogin()))
		{
			_messages.pop_back();
			std::cout << endl << "Message was deleted" << endl;
		}
		else
		{
			std::cout << "Not enough rights to delete" << endl;
		}
	}
	std::cout << "Chat is empty!" << endl;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : _users)
	{
		if (login == user.getUserLogin())
			return std::make_shared<User>(user);
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

