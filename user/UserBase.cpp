#pragma once

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
User UserBase::GetUserByLogin(const std::string& login)
{
	//try catch
	return GetUserBase()->_user_base_data.at(login);
};