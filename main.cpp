#include "./user/User.h"
#include "./user/User.cpp"
#include "./user/UserBase.h"
#include "./user/UserBase.cpp"
#include <set>

bool operator < (User c1, User c2)
{
    return c1.getName() < c2.getName();
}

int main() {
	UserBase userBase;
    User u ("u", "logintolik", "123ads", '1');
    userBase.addUser(u);
    User u1("u1", "login1aaaa", "123ads", '2');
    userBase.addUser(u1);
    std::cout << userBase.getUsers() << std::endl;
    std::cout << userBase.getUserByName("u") << std::endl;
}