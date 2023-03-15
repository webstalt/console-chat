//state and singleton patterns
#pragma once
#include <iostream>
#include "../conversation/ConversationBase.h"
#include "../user/UserBase.h"
class ChatEngine {
public:
	ChatEngine(ChatEngine&) = delete;
	void operator=(const ChatEngine&) = delete;
	static void SetEngineState(const State* s);
	void GOTO_StartMenu();
	void GOTO_RegistrationMenu();
	void GOTO_MainMenu();
	void GOTO_ChangeProfileMenu();
	void GOTO_AllConversations();
	void GOTO_StartChatting();
private:
	static class State* curent_state;
	ChatEngine();//run Unautorised with initializer of ChatEngine
};

class State {
	virtual void GOTO_StartMenu(ChatEngine*);
	virtual void GOTO_RegistrationMenu(ChatEngine*);
	virtual void GOTO_MainMenu(ChatEngine*);
	virtual void GOTO_ChangeProfileMenu(ChatEngine*);
	virtual void GOTO_AllConversations(ChatEngine*);
	virtual void GOTO_StartChatting(ChatEngine*);
};

//further constructors are not necessary
//function "Execute" runs enterface of class (in perfect case it starts
//automaticly in GOTO_... functions) 
class Unautorised : public State {
public:
	void Execute();
	void GOTO_RegistrationMenu(ChatEngine*);
	void GOTO_MainMenu(ChatEngine*);
private:
	Unautorised();
};
class Registration : public State {
public:
	void Execute();
	void GOTO_StartMenu(ChatEngine*);
	void GOTO_MainMenu(ChatEngine*);
private:
	Registration();
};
class MainMenu : public State {
public:
	void Execute();
	void GOTO_StartMenu(ChatEngine*);
	void GOTO_ChangeProfileMenu(ChatEngine*);
	void GOTO_AllConversations(ChatEngine*);
private:
	MainMenu();
};
class ProfileSettings : public State {
public:
	void Execute();
	void GOTO_MainMenu(ChatEngine*);
private:
	ProfileSettings();
};
class ChatObserver : public State {
public:
	void Execute();
	void GOTO_StartMenu(ChatEngine*);
	void GOTO_StartChatting(ChatEngine*);
private:
	ChatObserver();
};
class Chatting : public State {
public:
	void Execute();
	void GOTO_StartMenu(ChatEngine*);
	void GOTO_AllConversations(ChatEngine*);
private:
	Chatting();
};