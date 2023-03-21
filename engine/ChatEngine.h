//state and singleton patterns
#pragma once
#include <iostream>
#include "../conversation/ConversationBase.h"
#include "../user/UserBase.h"
class State;
class ChatEngine {
public:
	ChatEngine(ChatEngine&) = delete;
	void operator=(const ChatEngine&) = delete;
	static ChatEngine* GetChatEngine();
	void SetEngineState(State*);
	void GOTO_StartMenu();
	void GOTO_RegistrationMenu();
	void GOTO_MainMenu();
	void GOTO_ChangeProfileMenu();
	void GOTO_AllConversations();
	void GOTO_StartChatting();
private:
	class State* _curent_state;
	static ChatEngine* _chat_engine;
	ChatEngine();
};

class State {
	virtual void Execute();
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
	Unautorised();
	void Execute();
private:
	void GOTO_RegistrationMenu(ChatEngine*, User*);
	void GOTO_MainMenu(ChatEngine*, User*);
};
class Registration : public State {
public:
	Registration();
	void Execute(User*);
private:
	void GOTO_StartMenu(ChatEngine*);
	void GOTO_MainMenu(ChatEngine*, User*);
private:
	User* _curent_user;
};
class MainMenu : public State {
public:
	MainMenu();
	void Execute(User*);
private:
	void GOTO_StartMenu(ChatEngine*);
	void GOTO_ChangeProfileMenu(ChatEngine*, User*);
	void GOTO_AllConversations(ChatEngine*, User*);
private:
	User* _curent_user;
};
class ProfileSettings : public State {
public:
	void Execute(User*);
	ProfileSettings();
private:
	void GOTO_MainMenu(ChatEngine*, User*);
private:
	User* _curent_user;
};
class ChatObserver : public State {
public:
	ChatObserver();
	void Execute(User*);
private:
	void GOTO_StartMenu(ChatEngine*, User*);
	void GOTO_StartChatting(ChatEngine*, User*);
private:
	User* _curent_user;
};
class Chatting : public State {
public:
	Chatting(User*);
	void Execute();
private:
	void GOTO_StartMenu(ChatEngine*, User*);
	void GOTO_AllConversations(ChatEngine*, User*);
private:
	User* _curent_user;
};