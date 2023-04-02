#include "ConversationKey.h"

std::set <std::string> ConversationKey::GetKey()const {
	return this->_conversation_key;
};
std::string ConversationKey::GetAlias()const {
	return this->_alias;
};
bool operator < (const ConversationKey& c_key1, const ConversationKey& c_key2) {
	if (c_key1.GetAlias() < c_key2.GetAlias())
		return true;
	return false;
};
