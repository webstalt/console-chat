#pragma once

#include "UserBase.h"

UserBase::UserBase() {
	std::set<User> _user_base_data;
}
UserBase* UserBase::_user_base = nullptr;
UserBase* UserBase::GetUserBase() {
	if (_user_base == nullptr) {
		_user_base = new UserBase();
	}
	return _user_base;
}
//struct find_by_name {
//  find_by_name(const std::string& name): _name(name) 
//  {};
//  bool operator()(const User& user) 
//  {
//    return user.setName(name);
//  };
//private:
//  std::string _name;
//};
//struct find_by_login {
//  find_by_login(const std::string& login): _login(login) 
//  {};
//  bool operator()(const User& user) 
//  {
//    return user.setLogin(login);
//  };
//private:
//  std::string _login;
//};
std::set<User> UserBase::GetUsers() const
{
	return GetUserBase()->_user_base_data;
};
void UserBase::AddUser(const User& user)
{
	GetUserBase()->_user_base_data.insert(user);
};
size_t UserBase::GetUsersAmount() const
{
	return GetUsers().size();
};
//std::set<User>::iterator UserBase::getUserByName(const std::string& name) const
//{
//  return std::find_if(_userBase.begin(), _userBase.end(), find_by_name(name));
//};
//std::set<User>::iterator UserBase::getUserByLogin(const std::string& login) const
//{
//  return std::find_if(_userBase.begin(), _userBase.end(), find_by_login(login));
//};