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
    while (true) {
        _curent_state->Execute();
        break;
    }
    //GetChatEngine(_curent_state)->GetCurentState()->SetState_Registration(this);
    //GetChatEngine(_curent_state)->GetCurentState()->SetState_MainMenu(this);
    //GetChatEngine(_curent_state)->GetCurentState()->SetState_Unautorise(this);
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
void IState::SetState_Chatting(ChatEngine* state, const ConversationKey& curent_key) {
    std::cout << "Going to the chat..." << std::endl;
    state->SetState(new Chatting(curent_key));
};

void Unautorised::Execute() {
    ChatEngine* de = ChatEngine::GetChatEngine(new Unautorised());
    de->GetCurentState()->SetState_MainMenu(de);
};
void Unautorised::DisplayHelp() {
    std::cout << "Press q to exit" << std::endl;
};

void MainMenu::Execute() {

};
void MainMenu::DisplayHelp() {

};

void Registration::Execute() {
    //std::cout << 'Enter name' << std::endl;
    //std::cin << name;
    //std::cout << 'name: ' << name << ', Enter login' << std::endl;
    //std::cin << login;
    //std::cout << 'login: ' << login << 'Enter password' << std::endl;
    //std::cin << password;
    //User u(name, login, password);
    //UserBase::AddUser(u);
    //ChatEngine::SetCurentUser(u);
    //std::cout << 'Success' << std::endl;
    //
    //ChatEngine* engine = ChatEngine::GetChatEngine(engine->GetCurentState());
    //engine->GetCurentState()->SetState_MainMenu(engine);
};
void Registration::DisplayHelp() {
    //std::cout << 'Press q to step back' << std::endl;
    //cin >> a;
    //switch (a)
    //{
    //    case 'q':
    //        ChatEngine* engine = ChatEngine::GetChatEngine(engine->GetCurentState());
    //        engine->GetCurentState()->SetState_MainMenu(engine);
    //        break;
    //   
    //    default:
    //        cout << "Command is not recognized" << endl
    //             << " ------ " << endl
    //             << endl;
    //}
};

void ProfileSettings::Execute() {};
void ProfileSettings::DisplayHelp() {};

void ChatObserver::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    UserBase* u_base = UserBase::GetUserBase();
    ConversationBase* c_base = ConversationBase::GetConversationBase();

    if (c_base->GetNewMessageCounter(engine->GetCurentUser().GetLogin()) == 0) {
        std::cout << engine->GetCurentUser().GetName() << ", you haven't got new messages!" << std::endl;
    }
    else {
        std::cout << engine->GetCurentUser().GetName() << ", you have new messages from " << c_base->GetNewMessageCounter(engine->GetCurentUser().GetLogin()) << " converstations:" << std::endl;
        int counter = 0;
        for (const auto& msg_source: c_base->GetNewMessageSource(engine->GetCurentUser().GetLogin()))
        {
            ++counter;
            std::cout << counter << ". " << msg_source.GetAlias() << std::endl;
        }
    }
    this->DisplayHelp();
    while (engine->GetCurentState()->GetName() == CHATOBSERVER)
    {
        char command;
        std::cin >> command;
        switch (command)
        {
        case 'c': {
            std::string alias;
            std::cin >> alias;
            if (alias == "@ALL") {
                std::cout << "Input messages to all users; input '~end' to end inputting" << std::endl;
                while (true)
                {
                    std::string message_text;
                    std::cin >> message_text;
                    if (message_text == "~end") {
                        this->DisplayHelp();
                        break;
                    }
                    for (auto& recipient : u_base->GetUsers()) {
                        std::set <std::string> key;
                        key.insert(recipient.first);
                        key.insert(engine->GetCurentUser().GetLogin());
                        message_text.append(" /*to @ALL*/");
                        c_base->WriteMessage(engine->GetCurentUser().GetLogin(),
                                            { key , engine->GetCurentUser().GetLogin() },
                                            message_text);
                    }
                }
            }
            else if (!c_base->FindConversationKey(alias).GetAlias().empty()) {
                this->SetState_Chatting(engine, c_base->FindConversationKey(alias));
            }
            else if (u_base->UserExist(alias)) {
                this->SetState_Chatting(engine, { {alias},alias });
            }
            else {
                std::cout << "Creation of new conversation: input logins of recipients, input 'end' twice to end inputing" << std::endl;
                std::set<std::string>key;
                while (true) {
                    std::string user_login;
                    std::cin >> user_login;
                    if (user_login == "end") {
                        std::string confirmation;
                        std::cin >> confirmation;
                        if (confirmation == "end") {
                            if (key.empty()) {
                                std::cout << "Empty list of recipients, at least one is required!" << std::endl;
                            }
                            else {
                                break;
                            }
                        }
                    }
                    else if (u_base->UserExist(user_login) == false) {
                        std::cout << "User with such login doesn't exist" << std::endl;
                    }
                    else {
                        key.insert(user_login);
                        std::cout<< user_login << " successfuly added to conversation" << std::endl;
                    }
                }
                this->SetState_Chatting(engine, {key ,alias});
            }
            break;
        }
        case 'm': {
            this->SetState_MainMenu(engine);
            break;
        }
        case 's': {
            std::cout << "Do you realy want to sign out? Print 'yes' to confirm." << std::endl;
            std::string confirmation;
            std::cin >> confirmation;
            if (confirmation == "yes") {
                engine->SetCurentUser({ "","","" });
                this->SetState_Unautorise(engine);
            }
            std::cout << "You are still in chat observer..." << std::endl;
            break;           
        }
        case 'i': {
            this->DisplayHelp();
            break;
        }
        default:
            std::cout << "Unknown command, please repeat input" << std::endl;
            break;
        }
    }
};
void ChatObserver::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "Chat observer menu:" <<std::endl;
    std::cout << "1. to go to conversation, write comand (no matter does exist this" << std::endl;
    std::cout << "conversation or doesn't): c conversation_alias" << std::endl;
    std::cout << "2. to write messages to all users: c @ALL" << std::endl;
    std::cout << "3. to go to main menu, write comand: m" << std::endl;
    std::cout << "4. to sign out, write comand: s" << std::endl;
    std::cout << "5. to show help, write command: i" << std::endl;
    std::cout << std::endl;
};

void Chatting::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    ConversationBase* c_base = ConversationBase::GetConversationBase();

    DisplayHelp();
    bool new_messages = false;
    for (const auto& msg : c_base->GetConversationBaseData()[this->GetCurentKey()]) {
        if (msg._read_flag && new_messages && msg._author != engine->GetCurentUser().GetLogin()) {
            new_messages = false;
            std::cout << "========NEW MESSAGES========" << std::endl;
        }
        if (msg._author != engine->GetCurentUser().GetLogin()) {
            msg._read_flag == true;
        }
        std::cout << msg._author << ": " << msg._content << std::endl;
    }
    std::string message_content;

    while (engine->GetCurentState()->GetName() == CHATTING) {
        std::cout << engine->GetCurentUser().GetLogin() << ": ";
        std::cin >> message_content;
        if (message_content == "~end") {
            this->SetState_ChatObserver(engine);
        }
        else if (message_content == "~inf") {
            DisplayHelp();
        }
        else {
            c_base->WriteMessage(engine->GetCurentUser().GetLogin(), this->GetCurentKey(), message_content);
        }
    }
};
void Chatting::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "Chat menu:" << std::endl;
    std::cout << "1. to go to back to chat observer, write comand: ~end" << std::endl;
    std::cout << "2. to write messages just input message text" << std::endl;
    std::cout << "3. to show help, write command: ~inf" << std::endl;
    std::cout << std::endl;
};
ConversationKey Chatting::GetCurentKey()const {
    return this->_curent_key;
};