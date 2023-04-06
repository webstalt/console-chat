#pragma once

#include "ConversationKey.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#define KEY_TO_ALL { {"ALL"}, "@ALL"}

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
	//from-message
	void WriteMessageAll(const std::string&, const std::string&);
	//key of conversation
	void ShowMessage(const std::string&,const ConversationKey&) const;
	void ShowMessageAll() const;
	std::vector<Message> ReadConversation(const std::string&, const ConversationKey&) const;
	std::set<ConversationKey> GetNewMessageSource(const std::string&)const;
	std::set<ConversationKey> GetConversationHistory(const std::string&)const;
	size_t GetNewMessageCounter(const std::string&) const;
	ConversationKey FindConversationKey(const std::string&);
	bool ConversationExist(const ConversationKey&)const;
private:
	ConversationBase();
	static ConversationBase* _conversation_base;
	std::map <ConversationKey, std::vector<Message>> _conversation_base_data;
	std::map <std::string, std::set<ConversationKey>>_new_message_source;
	std::map <std::string, std::set<ConversationKey>>_conversation_history;
};