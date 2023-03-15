#include "./user/UserBase.h"
#include "./conversation/ConversationBase.h"
#include <iostream>

void CDtest() {

}
void UBtest() {
    
    UserBase* ub = UserBase::GetUserBase();
    User u("u", "logintolik", "123321");
    ub->AddUser(u);
    User u1("u1", "login1aaaa", "123ads");
    ub->AddUser(u1);
    ub->AddUser({ "Anton", "bacravaj", "sa11" });
    ub->AddUser({ "Maria", "webstalt", "sa113sa" });
    /*std::cout << userBase.getUsers() << std::endl;
    std::cout << userBase.getUserByName("u") << std::endl;*/
}
int main() {
    UBtest();
    return 0;
}