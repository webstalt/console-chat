#pragma once

#include "User.h"
#include <map>

class UserBase {
public:
	UserBase(UserBase&) = delete;
	void operator=(const UserBase&) = delete;
	static UserBase* GetUserBase();
	void AddUser(const User&);
	std::map<std::string, User> GetUsers() const;
	size_t GetUsersAmount() const;
	User GetUserByLogin(const std::string&);
private:
	std::map<std::string,User> _user_base_data;
	static UserBase* _user_base;
	UserBase();
};