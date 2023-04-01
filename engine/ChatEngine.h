#pragma once
#include<string>
#include<iostream>
#include"../user/UserBase.h"
#include"../conversation/ConversationBase.h"

#define UNOUTORISED "Wellcome to console chat!"
#define MAINMENU "You are in main menu!"
#define REGISTRARION "You are in registration menu!"
#define PROFILESETTINGS "You are in profile settings!"
#define CHATOBSERVER "You are in chat observer menu!"
#define CHATTING "Chatting!"
#define SIGNOUT "Signing out..."
#define EXIT "Exiting from application..."

class ChatEngine;
class IState
{
public:
    IState(const std::string& state_name) :_state_name(state_name) {};
    std::string GetName()const;//бесполезно
    virtual void Execute() = 0;
    virtual void DisplayHelp() = 0;
    virtual void SetState_Unautorise(ChatEngine*);
    virtual void SetState_Registration(ChatEngine*);
    virtual void SetState_MainMenu(ChatEngine*);
    virtual void SetState_ProfileSettings(ChatEngine*);
    virtual void SetState_ChatObserver(ChatEngine*);
    virtual void SetState_Chatting(ChatEngine*, std::set <User>);
private:
    std::string _state_name;//бесполезно
};
//core class
class ChatEngine
{
public:
    ChatEngine(ChatEngine&) = delete;
    void operator=(const ChatEngine&) = delete;
    static ChatEngine* GetChatEngine(IState*);

    void RunEngine();
    void SetState(IState*);
    IState* GetCurentState()const;
    void SetCurentUser(const User&);
    User GetCurentUser()const;
    ~ChatEngine();
private:
    IState* _curent_state;
    User _curent_user;
    static ChatEngine* _chat_engine;
    ChatEngine(IState* istate) : _curent_state(istate) {};
};

class Unautorised : public IState
{
public:
    Unautorised() : IState(UNOUTORISED) {};
    virtual void Execute() ;
    virtual void DisplayHelp();
private:
    virtual void SetState_Unautorise(ChatEngine*) override {};//unexpectable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unexpectable, does nothing
    virtual void SetState_ChatObserver(ChatEngine*)override {};//unexpectable, does nothing
    virtual void SetState_Chatting(ChatEngine*, std::set <User>)override {};//unexpectable, does nothing
    IState* _istate;
};
class MainMenu : public IState
{
public:
    MainMenu() : IState(MAINMENU) {}
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_Registration(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_MainMenu(ChatEngine*)override {}//unexpectable command, does nothing;
    virtual void SetState_Chatting(ChatEngine*, std::set <User>)override {}//unexpectable command, does nothing;
};
class Registration : public IState
{
public:
    Registration() : IState(REGISTRARION) {}
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_Registration(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_ChatObserver(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, std::set <User>)override {};//unexpectable command, does nothing
};
class ProfileSettings : public IState
{
public:
    ProfileSettings() : IState(PROFILESETTINGS) {}
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_Unautorise(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_Registration(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_ChatObserver(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, std::set <User>)override {};//unexpectable command, does nothing
};
class ChatObserver : public IState
{
public:
    ChatObserver() : IState(CHATOBSERVER) {}
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_Registration(ChatEngine*)override {}//unexpectable command, does nothing;
    virtual void SetState_ProfileSettings(ChatEngine*)override {}//unexpectable command, does nothing;
    virtual void SetState_ChatObserver(ChatEngine*)override {}//unexpectable command, does nothing;
};
class Chatting : public IState
{
public:
    Chatting(std::set <User> curent_key) : IState(CHATTING), _curent_key(curent_key){};
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_Unautorise(ChatEngine*)override {}//unexpectable command, does nothing;
    virtual void SetState_Registration(ChatEngine*)override {}//unexpectable command, does nothing;
    virtual void SetState_ProfileSettings(ChatEngine*)override {}//unexpectable command, does nothing;
    virtual void SetState_Chatting(ChatEngine*, std::set <User>)override {}//unexpectable command, does nothing;
    std::set <User> _curent_key;
};