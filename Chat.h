#pragma once
#include<vector>
#include<exception>
#include<memory>

#include"Message.h"

struct UserLoginExp: public std::exception
{
	const char* what() const noexcept override { return "error: Login is busy"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "error: Name is busy"; }
};

class Chat
{
public:
	void startChat();
	bool isChatWork() const { return _isChatWork; }
	std::shared_ptr<User> getCurrentUser() const { return _currentUser; }
	void showLoginMenu();
	void showUserMenu();

private:
	bool _isChatWork = false;
	std::vector<User> _users;
	std::vector<Message> _messages;
	std::shared_ptr<User> _currentUser = nullptr;

	void login();
	void singUp();
	void showAllUsersName() const;
	void showChat() const;
	void addMessage();
	
	std::vector<User>& getAllUsers() { return _users; }
	std::vector<Message>& getAllmessages() { return _messages; }
};