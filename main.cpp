#include "./user/UserBase.h"
//#include "./conversation/ConversationBase.h"
#include <iostream>

void CDtest() {

}
void UBtest() {
    UserBase* ub = UserBase::GetUserBase();
    User u("u", "logintolik", "123321");
    ub->AddUser(u);
    std::cout << ub->GetUsersAmount() << std::endl;
    UserBase* ub1 = UserBase::GetUserBase();
    User u1("u1", "login1aaaa", "123ads");
    ub->AddUser(u1);
    std::cout << ub->GetUsersAmount() << std::endl;
    ub->AddUser({ "Anton", "bacravaj", "sa11" });
    std::cout << ub->GetUsersAmount() << std::endl;
    ub1->AddUser({ "Maria", "webstalt", "sa113sa" });
    std::cout << ub->GetUsersAmount() << " " << ub->GetUserBase() << std::endl;
    std::cout << ub1->GetUsersAmount() << " " << ub1->GetUserBase() << std::endl;
    //ub1 and ub pointing to the same object of UserBase class 
}
int main() {
    UBtest();
    return 0;
}