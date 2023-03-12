#pragma once
#include "Message.h"
#include <vector>
#include <map>

class Conversation {
public:
	void SendMessage(const Message&);
	void ShowNew()const;
	void ShowAll()const;

private:
	std::pair <User, User> _conversation_key;
	std::map <_conversation_key, std::vector <std::string>> _correspondence;
private:
	std::pair <User, User> MakeKey(const User&, const User&);
	Conversation(const Message&);
};