#include "Message.h"

std::string Message::GetContent()const{
	return _content;
};
User Message::GetSender()const {
	return _from;
};
User Message::GetRecipient()const {
	return _to;
};
bool Message::IsRead()const {
	return _is_read;
};
void Message::MarkAsRead() {
	_is_read = true;
};