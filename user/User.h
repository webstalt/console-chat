#pragma once

class User {
public:
  void setLogin(string login);
  void setPassword(string password);
  boolean checkPassword(string password);
protected:
  string _login;
  string _id;
  string _password;
}