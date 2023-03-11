#pragma once

#include "User.h"
#include <set>

class UserBase {
public:
  void createUser(User user);
  User getUser(string userId);
private:

  std::set<User> _userbase;
}