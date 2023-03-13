#pragma once
#include <string>
#include "User.h"
class Message {
public:
	explicit Message(const std::string& content,
			const User& from,
			const User& to) :
				_content(content), _from(from), _to(to) {};
	std::string GetContent()const;
	std::string GetSender()const;
	std::string GetRecipient()const;
	bool IsRead()const;
	void MarkAsRead();
	~Message() = default noexcept;
private:
	std::string _content;
	User _from;
	User _to;
	bool _is_read = false;
};