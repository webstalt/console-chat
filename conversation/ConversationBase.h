#pragma once
#include "Message.h"
#include <vector>
#include <map>
#include <set>
#include <atlstr.h>
#include <exception>
#include <initializer_list>
/*supporting class for keeping identification key of conversations
set of one member (recepient) for dialog and set of all members for group chat*/
class ConversationKey {
public:
	//key constructor for dialog
	ConversationKey(const User&);
	//key constructor for group chat
	ConversationKey(const std::initializer_list<User>&);
	size_t GetConversationKeySize() const;
	std::set<User> GetConversationKey() const;

private:
	std::set <User> _conversation_key;
};
bool operator < (const ConversationKey&, const ConversationKey&);
/*database of all conversations for curent user
*/
class Conversation {
public:
	void AddMessageNewMessage(const Message&);
	size_t GetNewMessageCounter(const ConversationKey&);
	std::vector <Message> GetHistory();
	std::vector <Message> GetNewMessages();
private:
	std::set <ConversationKey> _new_message_source;
	std::map <ConversationKey, Conversation> _correspondence;
	Conversation();
};
/*database of all conversations
made as "singleton"*/
class ConversationBase {
public:
	ConversationBase(ConversationBase&) = delete;
    void operator=(const ConversationBase&) = delete;
	static ConversationBase* GetConversationBase();
private:
	std::map <ConversationKey, Conversation> _conversation_base_data;
	static ConversationBase* _conversation_base;
	ConversationBase();
};