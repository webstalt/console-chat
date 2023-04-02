#pragma once

#include "ConversationKey.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <exception>


bool operator < (const ConversationKey&, const ConversationKey&);
class ConversationBase {
public:
	struct Message {
		std::string _content;
		std::string _author;
		bool _read_flag = false;
	};
	ConversationBase(ConversationBase&) = delete;
	void operator=(const ConversationBase&) = delete;
	std::map <ConversationKey, std::vector<Message>> GetConversationBaseData();
	static ConversationBase* GetConversationBase();

	//from-{to}-message
	void WriteMessage(const std::string&, const ConversationKey&, const std::string&);
	//key of conversation
	std::vector<Message> ReadConversation(const std::string&, const ConversationKey&) const;
	std::set<ConversationKey> GetNewMessageSource(const std::string&)const;
	size_t GetNewMessageCounter(const std::string&) const;
	ConversationKey FindConversationKey(const std::string&);
private:
	ConversationBase();
	static ConversationBase* _conversation_base;
	std::map <ConversationKey, std::vector<Message>> _conversation_base_data;
	std::map <std::string, std::set<ConversationKey>>_new_message_source;
};