#include "./user/UserBase.h"
#include "conversation/ConversationBase.h"
#include <iostream>

void CDtest() {

}
void UBtest() {
    UserBase userBase;
    User u("u", "logintolik", "123ads", '1');
    userBase.addUser(u);
    User u1("u1", "login1aaaa", "123ads", '2');
    userBase.addUser(u1);
    std::cout << userBase.getUsers() << std::endl;
    std::cout << userBase.getUserByName("u") << std::endl;
}
int main() {
    return 0;
}