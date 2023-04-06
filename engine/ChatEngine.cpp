#include "ChatEngine.h"

class ChatEngine;
class IState;
class Unauthorized;
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
    GetChatEngine(_curent_state)->GetCurentState()->SetState_Unauthorize(this);
    while (true) {
        _curent_state->Execute();
        break;
    }
    //GetChatEngine(_curent_state)->GetCurentState()->SetState_Registration(this);
    //GetChatEngine(_curent_state)->GetCurentState()->SetState_MainMenu(this);
    //GetChatEngine(_curent_state)->GetCurentState()->SetState_Unauthorize(this);
    //GetChatEngine(_curent_state)->GetCurentState()->SetState_ProfileSettings(this);
    //GetChatEngine(_curent_state)->GetCurentState()->SetState_ChatObserver(this);
    //std::set <User> n;
    //GetChatEngine(_curent_state)->GetCurentState()->SetState_Chatting(this, n);
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
    if (ChatEngine::GetChatEngine(_curent_state)->GetCurentState()->GetName() != UNAUTHORIZED) {
        std::exception;//can be evoked only while regitsration
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
void IState::SetState_Unauthorize(ChatEngine* state) {
    state->SetState(new Unauthorized());
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

void Unauthorized::Execute() {
    ChatEngine* de = ChatEngine::GetChatEngine(new Unauthorized());
    de->GetCurentState()->SetState_MainMenu(de);
};

void Unauthorized::DisplayHelp() {
    std::cout << "Press q to exit" << std::endl;
    cin >> a;
    switch (a)
    {
        case 'q':
            ChatEngine* engine = ChatEngine::GetChatEngine(engine->GetCurentState());
            engine->GetCurentState()->SetState_MainMenu(engine);
            break;
       
        default:
            cout << "Command is not recognized" << endl
                 << " ------ " << endl
                 << endl;
    }
};

void MainMenu::Execute() {

};
void MainMenu::DisplayHelp() {

};

void Registration::Execute() {
    std::cout << 'Enter name' << std::endl;
    std::cin << name;
    std::cout << 'name: ' << name << ', Enter login' << std::endl;
    std::cin << login;
    std::cout << 'login: ' << login << 'Enter password' << std::endl;
    std::cin << password;
    User u(name, login, password);
    UserBase::AddUser(u);
    ChatEngine::SetCurentUser(u);
    std::cout << 'Success' << std::endl;
    
    ChatEngine* engine = ChatEngine::GetChatEngine(engine->GetCurentState());
    engine->GetCurentState()->SetState_MainMenu(engine);
};

void Registration::DisplayHelp() {
    std::cout << 'Press q to step back' << std::endl;
    cin >> a;
    switch (a)
    {
        case 'q':
            ChatEngine* engine = ChatEngine::GetChatEngine(engine->GetCurentState());
            engine->GetCurentState()->SetState_MainMenu(engine);
            break;
       
        default:
            cout << "Command is not recognized" << endl
                 << " ------ " << endl
                 << endl;
    }
};

void ProfileSettings::Execute() {

};
void ProfileSettings::DisplayHelp() {
    
};

void ChatObserver::Execute() {};
void ChatObserver::DisplayHelp() {};

void Chatting::Execute() {};
void Chatting::DisplayHelp() {};