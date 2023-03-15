#pragma once

#include "User.h"
#include <set>

class UserBase {
public:
  void addUser(const User& user);
  std::set<User> getUsers() const;
  int getUsersAmount() const;
  std::set<User>::iterator getUserByName(const string& name) const;
  std::set<User>::iterator getUserByLogin(const string& login) const;
private:
  std::set<User> _userBase;
};