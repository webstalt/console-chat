#pragma once
#include "Conversation.h"
#include <map>
#include <set>
#include <atlstr.h>
#include <exception>

class ConversationBase {
public:
	ConversationBase(ConversationBase&) = delete;
    void operator=(const ConversationBase&) = delete;
	static ConversationBase ChangeConversationBase(const Message&);

	//class of unique keys to identificate conversation: may consist of 2 or more users
	class ConversationKey {
	public:
		//key for dialog
		explicit ConversationKey(const User&, const User&);

		//key for group chat
		template<typename T, typename ... Args>
		explicit ConversationKey(const& T,const& Args ...);
	private:
		CString _tipe_comparator = "class User";
		set <int> _conversation_key;
	};

private:
	static std::map <ConversationKey, Conversation> _conversation_base;
private:
	ConversationBase(const Message&);
	static bool _conversation_base_exist = false;
};
