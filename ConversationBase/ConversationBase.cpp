#include "ConversationBase.h"

ConversationBase ConversationBase::ChangeConversationBase(const Message& m) {

    if (_exist=false) {
        ConversationBase();
        _exist = true;
    }
    return _conversation_base;
};