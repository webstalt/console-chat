#pragma once  
#include <iostream>

#include "User.h"

void User :: setName(const std::string& name)
{
	_name = name;
};

void User :: setLogin(const std::string& login)
{
	_login = login;
};

void User :: setPassword(const std::string& password)
{
	_password = password;
};

void User :: setId(const int& id)
{
	_id = id;
};

std::string User::getName() const 
{
	return _name;
};

std::string User::getLogin() const 
{
	return _login;
};

std::string User::getPassword() const 
{
	return _password;
};

int User::getId() const 
{
	return _id;
};
bool operator < (User c1, User c2)
{
	return c1.getName() < c2.getName();
}