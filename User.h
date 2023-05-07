#pragma once

class User
{
	const std::string _login;
	std::vector<char> _password;
	std::string _name;
	std::string _gender;
public:
	User(const std::string& login, const std::vector<char>& password, const std::string &name):_login(login),_password(password),_name(name){}
	User(const std::string& login, const std::vector<char>& password, const std::string &name, const std::string &gender) :_login(login), _password(password), _name(name),_gender(gender) {}
	const std::string& getUserLogin() const { return _login;}
	const std::vector<char> getUserPassword() const { return _password; }
	void setUserPassword(const std::vector<char> &password) { _password=password; }
	const std::string& getUserName() const { return _name; }
	void setUserName(const std::string& name) { _name = name; }
	const std::string& getUserGender() const { return _gender; }
	void setUserGender(std::string gender) { _gender=gender; }
};
