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
	size_t GetUsersAmount()const;
	bool UserExist(const std::string&) const;
	void ChangeName(const User& curent_user, const std::string& new_name);
	void ChangePassword(const User& curent_user, const std::string& new_password);
private:
	std::map<std::string, User> _user_base_data;
	static UserBase* _user_base;
	UserBase();
};