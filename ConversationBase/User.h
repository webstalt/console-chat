#pragma once
#include <string>

class User {
public:
	User(const std::string& name, 
			const std::string& login, 
			const std::string& password,
			const int& id)
				: _name(name), _login(login), _password(password), _id(id)
	{ 

	};
	void setName(const std::string&);
	void setLogin(const std::string&);
	void setPassword(const std::string&);
	void setId(const int&);
	std::string getName() const;
	std::string getLogin() const;
	std::string getPassword() const;
	std::string getId() const;
private:
	std::string _name;
	std::string _login;
	std::string _password;
	int _id;
};


