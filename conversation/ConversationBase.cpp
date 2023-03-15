#include "ConversationBase.h"
bool operator < (const User& u1, const User& u2) {
	return u1.getName() < u2.getName();
};

bool operator < (const ConversationKey& kkey1, const ConversationKey& kkey2) {
	if (kkey1.GetConversationKeySize() == kkey1.GetConversationKeySize()) {
		return kkey1.GetConversationKey() < kkey2.GetConversationKey();
	}
	else {
		return kkey1.GetConversationKeySize() < kkey2.GetConversationKeySize();
	}
};
ConversationKey::ConversationKey(const User& u1) {
	_conversation_key.insert(u1);
};
ConversationKey::ConversationKey(const std::initializer_list<User>& user_list) {
	_conversation_key.insert(user_list.begin(), user_list.end());
};
size_t ConversationKey::GetConversationKeySize() const {
	return _conversation_key.size();
};
std::set<User> ConversationKey::GetConversationKey() const {
	return _conversation_key;
};;

Conversation::Conversation() {};
void Conversation::AddMessageNewMessage(const Message&) {};
size_t Conversation::GetNewMessageCounter(const ConversationKey&) {};
std::vector <Message> Conversation::GetHistory() {};
std::vector <Message> Conversation::GetNewMessages() {};

ConversationBase* ConversationBase::_conversation_base = nullptr;
ConversationBase::ConversationBase() {
	std::map <ConversationKey, Conversation> _conversation_base_data;
}
ConversationBase* ConversationBase::GetConversationBase() {
    if (_conversation_base == nullptr) {
        auto _conversation_base = new ConversationBase();
    }
	return _conversation_base;
};


