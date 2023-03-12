#include "ConversationBase.h"

ConversationBase ConversationBase::ChangeConversationBase(const Message& m) {

    if (_exist=false) {
        ConversationBase(const Message& m);
        _exist = true;
    }
    return _conversation_base;
};
ConversationBase::ConversationBase(const Message& m) {
    _conversation_base.insert[ConversationKey(const& T u, const& Args ... args)].
}
ConversationKey::ConversationKey(const User& u1, const User& u2) {
    _conversation_key.insert(u1);
    _conversation_key.insert(u2);
};

ConversationKey::ConversationKey(const& T u, const& Args ... args) {
    if (T != _tipe_comparator) {
        _conversation_key.insert(u);
        ConversationKey(const& Args ... args);
    }
    else {
        throw std::exception();
    }
};