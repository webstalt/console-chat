#pragma once  
#include <iostream>

#include "User.h"

void User :: SetName(const std::string& name)
{
	_name = name;
};
void User :: SetLogin(const std::string& login)
{
	_login = login;
};
void User :: SetPassword(const std::string& password)
{
	_password = password;
};
void User :: SetId(const int& id)
{
	_id = id;
};
std::string User::GetName() const 
{
	return _name;
};
std::string User::GetLogin() const 
{
	return _login;
};
std::string User::GetPassword() const 
{
	return _password;
};
bool operator < (User c1, User c2)
{
	return c1.getName() < c2.getName();
}