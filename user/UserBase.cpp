#pragma once

#include "../exceptions.h"
#include "UserBase.h"

UserBase::UserBase() {
	std::map<std::string, User> _user_base_data;
}
UserBase* UserBase::_user_base = nullptr;
UserBase* UserBase::GetUserBase() {
	if (_user_base == nullptr) {
		_user_base = new UserBase();
	}
	return _user_base;
}

std::map<std::string, User> UserBase::GetUsers() const
{
	return GetUserBase()->_user_base_data;
};

void UserBase::AddUser(const User& user)
{
	GetUserBase()->_user_base_data[user.GetLogin()] = user;
};

size_t UserBase::GetUsersAmount() const
{
	return GetUsers().size();
};

User UserBase::FindUserByLogin(const std::string& login)
{
  if (GetUserBase()->_user_base_data.find(login) == GetUserBase()->_user_base_data.end()) {
    throw Invalid_login();
  } else {
    return GetUserBase()->_user_base_data.at(login);
  }
};

User UserBase::GetUserByLogin(const std::string& login)
{
  try 
  {
    FindUserByLogin(login);
  } 
  catch (Invalid_login& e) 
  {
    std::cout << e.what() << std::endl;
  } 
};