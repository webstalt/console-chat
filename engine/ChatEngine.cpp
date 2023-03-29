#include "ChatEngine.h"

class ChatEngine;
class IState;
class Unautorised;
class MainMenu;
class Registration;
class ProfileSettings;
class ChatObserver;
class Chatting;

ChatEngine* ChatEngine::_chat_engine = nullptr;
ChatEngine* ChatEngine::GetChatEngine(IState* state) {
    if (_chat_engine == nullptr) {
        _chat_engine = new ChatEngine(state);
    }
    return _chat_engine;
};
void ChatEngine::RunEngine() {
    GetChatEngine(_curent_state)->GetCurentState()->SetState_Unautorise(this);
    while (false) {
        _curent_state->Execute();
    }
    GetChatEngine(_curent_state)->GetCurentState()->SetState_Registration(this);
    GetChatEngine(_curent_state)->GetCurentState()->SetState_MainMenu(this);
    GetChatEngine(_curent_state)->GetCurentState()->SetState_Unautorise(this);
    //GetChatEngine(_curent_state)->GetCurentState()->SetState_ProfileSettings(this);
    GetChatEngine(_curent_state)->GetCurentState()->SetState_ChatObserver(this);
    std::set <User> n;
    GetChatEngine(_curent_state)->GetCurentState()->SetState_Chatting(this, n);
}
void ChatEngine::SetState(IState* state)
{
    delete GetChatEngine(_curent_state)->_curent_state;
    _curent_state = state;
    std::cout << GetChatEngine(_curent_state)->GetCurentState()->GetName() << std::endl;
}
IState* ChatEngine::GetCurentState()const
{
    return GetChatEngine(_curent_state)->_curent_state;
}
void ChatEngine::SetCurentUser(const User& user) {
    if (ChatEngine::GetChatEngine(_curent_state)->GetCurentState()->GetName() != UNOUTORISED) {
        std::exception;//can be awoked only while regitrsration
    }
    if (user.GetLogin().empty() || 
        user.GetName().empty() ||
        user.GetPassword().empty())
        std::exception;//all fields must be field
    //user with such login already exist
    ChatEngine::GetChatEngine(_curent_state)->_curent_user = user;
};
User ChatEngine::GetCurentUser()const {
    if (ChatEngine::GetChatEngine(_curent_state)->_curent_user.GetLogin().empty())
        std::exception;
    return ChatEngine::GetChatEngine(_curent_state)->_curent_user;
};
ChatEngine::~ChatEngine()
{
    delete GetChatEngine(_curent_state)->_curent_state;
}

std::string IState::GetName()const
{
    return _state_name;
};
void IState::SetState_Unautorise(ChatEngine* state) {
    state->SetState(new Unautorised());
};
void IState::SetState_Registration(ChatEngine* state) {
    std::cout << "Going to registration menu..." << std::endl;
    state->SetState(new Registration());
};
void IState::SetState_MainMenu(ChatEngine* state) {
    std::cout << "Going to main menu..." << std::endl;
    state->SetState(new MainMenu());
};
void IState::SetState_ProfileSettings(ChatEngine* state) {
    std::cout << "Going to profile settings..." << std::endl;
    state->SetState(new ProfileSettings());
};
void IState::SetState_ChatObserver(ChatEngine* state) {
    std::cout << "Going to all chats..." << std::endl;
    state->SetState(new ChatObserver());
};
void IState::SetState_Chatting(ChatEngine* state, std::set <User> curent_key) {
    std::cout << "Going to the chat..." << std::endl;
    state->SetState(new Chatting(curent_key));
};

void Unautorised::Execute() {};
void Unautorised::DisplayHelp() {};

void MainMenu::Execute() {};
void MainMenu::DisplayHelp() {};

void Registration::Execute() {};
void Registration::DisplayHelp() {};

void ProfileSettings::Execute() {};
void ProfileSettings::DisplayHelp() {};

void ChatObserver::Execute() {};
void ChatObserver::DisplayHelp() {};

void Chatting::Execute() {};
void Chatting::DisplayHelp() {};