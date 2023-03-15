#pragma once

#include "User.h"
#include <set>

class UserBase {
public:
  UserBase();
  void addUser(const User& user);
  std::set<User> getUsers() const;
  size_t getUsersAmount() const;
  std::set<User>::iterator getUserByName(const std::string& name) const;
  std::set<User>::iterator getUserByLogin(const std::string& login) const;
private:
  std::set<User> _userBase;
};