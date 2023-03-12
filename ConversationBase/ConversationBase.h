#pragma once
#include <map>
#include "Conversation.h"

class ConversationBase {
public:
	ConversationBase(ConversationBase&) = delete;
    void operator=(const ConversationBase&) = delete;
	ConversationBase ChangeConversationBase(const Message&);

private:
	std::pair <User, User> _conversation_key;
	std::map <_conversation_key, Conversation> _conversation_base;
private:
	ConversationBase();
	std::pair <User, User> MakeKey(const User&, const User&);
	bool _exist = false;
};
