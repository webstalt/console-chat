#pragma once
#include<string>
#include<iostream>
#include <cstdlib>
#include"../user/UserBase.h"
#include"../conversation/ConversationBase.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define UNAUTORISED "UNAUTORISED"
#define MAINMENU "MAINMENU"
#define REGISTRARION "REGISTRARION"
#define PROFILESETTINGS "PROFILESETTINGS"
#define CHATOBSERVER "CHATOBSERVER"
#define CHATTING "CHATTING"
#define SIGNOUT "SIGNOUT"
#define EXIT "EXIT"


class ChatEngine;
class IState
{
public:
    IState(const std::string& state_name) :_state_name(state_name) {};
    std::string GetName()const;//áåñïîëåçíî
    virtual void Execute() = 0;
    virtual void DisplayHelp() = 0;
    virtual void SetState_Unautorise(ChatEngine*);
    virtual void SetState_Registration(ChatEngine*);
    virtual void SetState_MainMenu(ChatEngine*);
    virtual void SetState_ProfileSettings(ChatEngine*);
    virtual void SetState_ChatObserver(ChatEngine*);
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&);
private:
    std::string _state_name;//áåñïîëåçíî
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
    Unautorised() : IState(UNAUTORISED) {};
    virtual void Execute() ;
    virtual void DisplayHelp();
private:
    virtual void SetState_Unautorise(ChatEngine*) override {};//unacceptable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_MainMenu(ChatEngine*)override {}//unacceptable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {};//unacceptable command, does nothing
};
class MainMenu : public IState
{
public:
    MainMenu() : IState(MAINMENU) {};
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_Registration(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_MainMenu(ChatEngine*)override {}//unacceptable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {}//unacceptable command, does nothing
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
    virtual void SetState_MainMenu(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {};//unexpectable command, does nothing
};
class ProfileSettings : public IState
{
public:
    ProfileSettings() : IState(PROFILESETTINGS) {};
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_Unautorise(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_Registration(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ChatObserver(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {};//unacceptable command, does nothing
};
class ChatObserver : public IState
{
    virtual void SetState_Registration(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ChatObserver(ChatEngine*)override {};//unacceptable command, does nothing
public:
    ChatObserver() : IState(CHATOBSERVER) {};
    virtual void Execute();
private:
    virtual void DisplayHelp();
    void PrintDialogsHistory(ChatEngine*)const;
    void PrintÀvailableUsers(ChatEngine*)const;
};
class Chatting : public IState
{
    virtual void SetState_Unautorise(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_Registration(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {};//unacceptable command, does nothing
public:
    Chatting(const ConversationKey& curent_key) : IState(CHATTING), _curent_key(curent_key){};
    virtual void Execute();
private:
    ConversationKey GetCurentKey()const;
    virtual void DisplayHelp();
    ConversationKey _curent_key;
};