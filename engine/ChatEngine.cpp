#include "ChatEngine.h"

ChatEngine::ChatEngine() {
	_chat_engine = Unautorised::Unautorised();
};
ChatEngine* ChatEngine::_chat_engine = nullptr;
ChatEngine* ChatEngine::GetChatEngine() {
	if (_chat_engine == nullptr) {
		_chat_engine = new ChatEngine();
	}
	return _chat_engine;
}
void ChatEngine::SetEngineState (State* state){
	GetChatEngine()->_curent_state = state;
}
void ChatEngine::GOTO_StartMenu() {
};
void ChatEngine::GOTO_RegistrationMenu() {

};
void ChatEngine::GOTO_MainMenu() {

};
void ChatEngine::GOTO_ChangeProfileMenu() {

};
void ChatEngine::GOTO_AllConversations() {

};
void ChatEngine::GOTO_StartChatting() {

};