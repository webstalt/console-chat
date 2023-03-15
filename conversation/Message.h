#pragma once
#include <string>
#include "../user/User.h"
class Message {
public:
	explicit Message(const std::string& content,
			const User& from,
			const User& to) :
				_content(content), _from(from), _to(to) {};
	std::string GetContent()const;
	User GetSender()const;
	User GetRecipient()const;
	bool IsRead()const;
	void MarkAsRead();
private:
	std::string _content;
	User _from;
	User _to;
	bool _is_read = false;
};