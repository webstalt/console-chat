#include "User.h"
#include <set>

bool operator < (User c1, User c2)
{
    return c1.getName() < c2.getName();
}

int main() {
	std::set <User> s;
    User u ("123", "tolik", "123ads");
    s.insert(u);
    User u1("123", "aaaa", "123ads");
    s.insert(u1);
    s.erase(u);

    int arr[5] = { 1,2,3,4,5 };
}