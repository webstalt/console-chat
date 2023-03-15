#pragma once

#include "UserBase.h"

struct find_by_name {
  find_by_name(const std::string& name): _name(name) 
  {};
  bool operator()(const User& user) 
  {
    return user._name = name;
  };
private:
  std::string _name;
};

struct find_by_login {
  find_by_login(const std::string& login): _login(login) 
  {};
  bool operator()(const User& user) 
  {
    return user._login = login;
  };
private:
  std::string _login;
};

void UserBase::addUser(const User& user)
{
  _userBase.insert(user);
};

std::set<User> UserBase::getUsers() const
{
  return _userBase;
};

int UserBase::getUsersAmount() const
{
  return _userBase.size();
};

std::set<User>::iterator UserBase::getUserByName(const string& name) const
{
  return std::find_if(_userBase.begin(), _userBase.end(), find_by_name(name));
};

std::set<User>::iterator UserBase::getUserByLogin(const string& login) const
{
  return std::find_if(_userBase.begin(), _userBase.end(), find_by_login(login));
};

UserBase::~UserBase()
{
  _userBase.clear();
};