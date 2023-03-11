#pragma once  
#include <iostream>

#include "User.h"

User::User(string id, string login, string password): _id(id), _login(login), _password(password)
{
}

void User:setPassword(string password) 
{
  _password = password;
}

void User:setLogin(string login) 
{
  _login = login;
}

bool User:checkPassword(string password) 
{
  return _password == password;
}