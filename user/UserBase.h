#pragma once

#include "User.h"

class UserBase {
public:
  void createUser(User user);
  User getUser(string userId);
protected:
  User[] _users;
}