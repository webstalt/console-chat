#pragma once  
#include <iostream>

#include "User.h"

void User :: setName(std::string& name)
{
	_name = name;
};

void User :: setLogin(std::string& login)
{
	_login = login;
};

void User :: setPassword(std::string& password)
{
	_password = password;
};

void User :: setId(int& id)
{
	_id = id;
};

std::string User::getName() {
	return _name;
};

std::string User::getLogin() {
	return _login;
};

std::string User::getPassword() {
	return _password;
};

std::string User::getId() {
	return _id;
};