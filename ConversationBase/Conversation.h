#pragma once
#include "Message.h"
#include <vector>


class Conversation {
public:
	void PushMessage(const Message&);
	~Conversation() = default noexcept;
private:
	std::vector <Message> _correspondence;
	int _new_messages_counter = 0;
private:
	Conversation(const Message&);
};