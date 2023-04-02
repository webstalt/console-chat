#include "ConversationBase.h"


ConversationBase::ConversationBase() {
	std::map <ConversationKey, std::vector<ConversationBase::Message>> _conversation_base_data;
};
ConversationBase* ConversationBase::_conversation_base = nullptr;
std::map <ConversationKey, std::vector<ConversationBase::Message>> ConversationBase::GetConversationBaseData() {
	return _conversation_base_data;
}
ConversationBase* ConversationBase::GetConversationBase() {
	if (ConversationBase::_conversation_base == nullptr) {
		ConversationBase::_conversation_base = new ConversationBase();
	}
	return ConversationBase::_conversation_base;
};
void ConversationBase::WriteMessage(const std::string& curent_user, 
									const ConversationKey& to,
									const std::string& s) {
	GetConversationBase()->_conversation_base_data[to].push_back({ s,curent_user,false });
	ConversationKey extended_key(to);
	for (const auto& it : extended_key.GetKey()) {
		if (it == curent_user) {
			continue;
		}
		GetConversationBase()->GetNewMessageSource(it).insert(to);
	}
};
std::vector<ConversationBase::Message> ConversationBase::ReadConversation(	const std::string& curent_user,
																			const ConversationKey& ck) const {
	if (GetConversationBase()->_new_message_source[curent_user].find(ck) !=
		GetConversationBase()->_new_message_source[curent_user].end())
		GetConversationBase()->_new_message_source[curent_user].erase(ck);
	return GetConversationBase()->GetConversationBaseData()[ck];
};
std::set<ConversationKey> ConversationBase::GetNewMessageSource(const std::string& u) const {
	return GetConversationBase()->_new_message_source[u];
};
size_t ConversationBase::GetNewMessageCounter(const std::string& u) const {
	return GetNewMessageSource(u).size();
};
ConversationKey ConversationBase::FindConversationKey(const std::string& alias) {
	for (const auto& it : this->GetConversationBaseData()) {
		if (it.first.GetAlias() == alias) {
			return it.first;
		}
	}
	return { {},{} };
};


