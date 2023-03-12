#include "Conversation.h"

std::pair <User, User> Conversation::MakeKey(const User& u1, const User& u1) {
	return (u1 < u2) ? {u1, u2} : {u2, u1};
};

