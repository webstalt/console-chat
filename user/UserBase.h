#pragma once

#include "User.h"
#include <set>

class UserBase {
public:
	UserBase(UserBase&) = delete;
	void operator=(const UserBase&) = delete;
	static UserBase* GetUserBase();
	void AddUser(const User& user);
	std::set<User> GetUsers() const;
	size_t GetUsersAmount() const;
	//std::set<User>::iterator getUserByName(const std::string& name) const;
	//std::set<User>::iterator getUserByLogin(const std::string& login) const;
private:
	std::set<User> _user_base_data;
	static UserBase* _user_base;
	UserBase();
};