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
    }
}
void ChatEngine::SetState(IState* state)
{
    delete GetChatEngine(_curent_state)->_curent_state;
    _curent_state = state;
    std::cout << "\n\n" << GetChatEngine(_curent_state)->GetCurentState()->GetName();
}
IState* ChatEngine::GetCurentState()const
{
    return GetChatEngine(_curent_state)->_curent_state;
}
void ChatEngine::SetCurentUser(const User& user) {
    ChatEngine::GetChatEngine(_curent_state)->_curent_user = user;
};
User ChatEngine::GetCurentUser()const {
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
    std::cout << "going to start menu..." << std::endl;
    state->SetState(new Unautorised());
};
void IState::SetState_Registration(ChatEngine* state) {
    std::cout << "going to registration menu..." << std::endl;
    state->SetState(new Registration());
};
void IState::SetState_MainMenu(ChatEngine* state) {
    std::cout << "going to main menu..." << std::endl;
    state->SetState(new MainMenu());
};
void IState::SetState_ProfileSettings(ChatEngine* state) {
    std::cout << "going to profile settings..." << std::endl;
    state->SetState(new ProfileSettings());
};
void IState::SetState_ChatObserver(ChatEngine* state) {
    std::cout << "going to all chats..." << std::endl;
    state->SetState(new ChatObserver());
};
void IState::SetState_Chatting(ChatEngine* state, const ConversationKey& curent_key) {
    std::cout << "going to the chat..." << std::endl;
    state->SetState(new Chatting(curent_key));
};

void Unautorised::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    UserBase* u_base = UserBase::GetUserBase();

    DisplayHelp();
    while (engine->GetCurentState()->GetName() == UNAUTORISED) {
        std::cout << "input command: ";
        char command;
        std::cin >> command;
        switch (command)
        {
        case 'q': {
            std::exit(0);
            break;
        }
        case 's': {
            std::string login, password;
            std::cout << "enter login: ";
            std::cin >> login;
            if (u_base->UserExist(login) == false) {
                std::cout << "this user doesn't exist!" << std::endl;
                break;
            }
            std::cout << "enter password: ";
            int attempts = 3;
            while (attempts--)
            {
                std::cin >> password;
                if (u_base->GetUsers()[login].GetPassword() == password) {
                    std::cout << "signing in..." << std::endl;
                    engine->SetCurentUser(u_base->GetUsers()[login]);
                    this->SetState_MainMenu(engine);
                    break;
                }
                else {
                    std::cout << "attempts lost: " << attempts << std::endl;
                }
            }
            break;
        }
        case 'r': {
            this->SetState_Registration(engine);
            break;
        }
        case 'i': {
            DisplayHelp();
            break;
        }
        default:
            std::cout << "Unknown command, please repeat input" << std::endl;
            break;
        }
    }
};
void Unautorised::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "start menu:" << std::endl;
    std::cout << "1. to terminate app, write command: q" << std::endl;
    std::cout << "2. to sign in, write command: s" << std::endl;
    std::cout << "3. to registrate new user, write command: r" << std::endl;
    std::cout << "4. to show help, write command: i" << std::endl;
    std::cout << std::endl;
};

void MainMenu::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    DisplayHelp();
    while (engine->GetCurentState()->GetName() == MAINMENU) {
        std::cout << "input command: ";
        char command;
        std::cin >> command;
        switch (command)
        {
        case 's': {
            engine->SetCurentUser({"", "", ""});
            this->SetState_Unautorise(engine);
            break;
        }
        case 'p': {
            this->SetState_ProfileSettings(engine);
            break;
        }
        case 'c': {
            this->SetState_ChatObserver(engine);
            break;
        }
        case 'i': {
            DisplayHelp();
            break;
        }
        default:
            std::cout << "Unknown command, please repeat input" << std::endl;
            break;
        }
    }
};
void MainMenu::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "main menu:" << std::endl;
    std::cout << "1. to sign out, write comand: s" << std::endl;
    std::cout << "2. to go to profilesettings, write comand: p" << std::endl;
    std::cout << "3. for chatting, write comand: c" << std::endl;
    std::cout << "4. to show help, write command: i" << std::endl;
    std::cout << std::endl;
};

void Registration::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    UserBase* u_base = UserBase::GetUserBase();
    DisplayHelp();

    while (engine->GetCurentState()->GetName() == REGISTRARION) {
        std::cout << "input command: ";
        char command;
        std::cin >> command;
        switch (command)
        {
        case 'b':{
            this->SetState_Unautorise(engine);
            break;
        }
        case 'n':{
            std::string login, name, password;
            std::cout << "enter login: ";
            std::cin >> login;
            if (u_base->UserExist(login)) {
                std::cout << "this user is already exist!" << std::endl;
                break;
            }
            std::cout <<"enter name: ";
            std::cin >> name;
            std::cout << "enter password: ";
            std::cin >> password;
            if (name.empty() ||
                login.empty() ||
                password.empty())
            {
                std::cout << "any fields cant be empty!" << std::endl;
                break;
            }
            User new_user(name, login, password);
            u_base->AddUser(new_user);
            std::cout << "new user successfully created!" << std::endl;
            std::cout << "want sign in now? (print 'y' to sign in or 'n' to go back): ";
            while (true) {
                char transition;
                std::cin >> transition;
                if (transition == 'y') {
                    engine->SetCurentUser(new_user);
                    this->SetState_MainMenu(engine);
                    break;
                }
                else if (transition == 'n') {
                    engine->SetCurentUser(new_user);
                    this->SetState_Unautorise(engine);
                    break;
                }
            }
            break;
        }
        case 'i':{
            DisplayHelp();
            break;
        }
        default:
            std::cout << "Unknown command, please repeat input" << std::endl;
            break;
        }
    }
};
void Registration::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "registration menu:" << std::endl;
    std::cout << "1. to go to back to autorisation menu, write comand: b" << std::endl;
    std::cout << "2. to write create new user, write command: n" << std::endl;
    std::cout << "3. to show help, write command: i" << std::endl;
    std::cout << std::endl;
};

void ProfileSettings::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    UserBase* u_base = UserBase::GetUserBase();
    DisplayHelp();
    while (engine->GetCurentState()->GetName() == PROFILESETTINGS) {
        std::cout << "input command: ";
        char command;
        std::cin >> command;
        switch (command)
        {
        case 'm':{
            this->SetState_MainMenu(engine);
            break;
        }
        case 'p':{
            std::cout << "print new password twice:" << std::endl;
            std::string new_passwrod1, new_passwrod2;
            std::cin >> new_passwrod1 >> new_passwrod2;
            if (new_passwrod1 != new_passwrod2) {
                std::cout << "new passwords are not equal!" << std::endl;
            }
            else if (new_passwrod1 == new_passwrod2 && new_passwrod1.empty()) {
                std::cout << "password cant be empty!" << std::endl;
            }
            else {
                u_base->GetUsers()[engine->GetCurentUser().GetLogin()].SetPassword(new_passwrod1);
                engine->GetCurentUser().SetPassword(new_passwrod1);
                std::cout << "password successfully changed!" << std::endl;
            }
            break;
        }
        case 'n':{
            std::cout << "print new name: ";
            std::string new_name;
            std::cin >> new_name;
            if (new_name.empty()) {
                std::cout << "name cant be empty!" << std::endl;
            }
            else {
                u_base->GetUsers()[engine->GetCurentUser().GetLogin()].SetName(new_name);
                engine->SetCurentUser(u_base->GetUsers()[engine->GetCurentUser().GetLogin()]);
                std::cout << "name successfully changed!" << std::endl;
            }
            break;
        }
        case 'i':{
            DisplayHelp();
            break;
        }
        default:
            std::cout << "Unknown command, please repeat input" << std::endl;
            break;
        }

    }
};
void ProfileSettings::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "profileSettings menu:" << std::endl;
    std::cout << "1. to go to back to chat main menu, write comand: m" << std::endl;
    std::cout << "2. to change password, write comand: p" << std::endl;
    std::cout << "3. to change name, write comand: n" << std::endl;
    std::cout << "4. to show help, write command: i" << std::endl;
    std::cout << std::endl;
};

void ChatObserver::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    UserBase* u_base = UserBase::GetUserBase();
    ConversationBase* c_base = ConversationBase::GetConversationBase();
    this->DisplayHelp();
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
    while (engine->GetCurentState()->GetName() == CHATOBSERVER)
    {
        std::cout << "input command: ";
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
                        message_text.append(" /*sended to @ALL*/");
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
                std::cout << "Creation of new conversation: input logins of recipients:" << std::endl;
                std::cout << "1. input '~end' twice to end inputing" << std::endl;
                std::cout << "2. input '~users' to show userlist" << std::endl;
                std::set<std::string>key;
                while (true) {
                    std::string user_login;
                    std::cin >> user_login;
                    if (user_login == "~end") {
                        std::string confirmation;
                        std::cin >> confirmation;
                        if (confirmation == "~end") {
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
                break;
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
    std::cout << "chat observer menu:" <<std::endl;
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
    std::cout << "chat menu:" << std::endl;
    std::cout << "1. to go to back to chat observer, write command: ~end" << std::endl;
    std::cout << "2. to write messages just input message text" << std::endl;
    std::cout << "3. to show help, write command: ~inf" << std::endl;
    std::cout << std::endl;
};
ConversationKey Chatting::GetCurentKey()const {
    return this->_curent_key;
};