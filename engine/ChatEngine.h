//state and singleton patterns
#pragma once
#include <iostream>
#include "../conversation/ConversationBase.h"
#include "../user/UserBase.h"
class State;
class ChatEngine {
public:
	ChatEngine(ChatEngine&) = delete;//singleton
	void operator=(const ChatEngine&) = delete;//singleton
	static ChatEngine* GetChatEngine();//singleton
	void SetEngineState(State*);
	void GOTO_StartMenu();
	void GOTO_RegistrationMenu();
	void GOTO_MainMenu();
	void GOTO_ChangeProfileMenu();
	void GOTO_AllConversations();
	void GOTO_StartChatting();
private:
	class State* _current_state;
	static ChatEngine* _chat_engine;//singleton
	ChatEngine();//singleton
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
//function "Execute" runs interface of class (in perfect case it starts
//automaticaly in GOTO_... functions) 
class Unauthorized : public State {
public:
	//quite from program
	//sign in
	//awoke RegistrationMenu
	Unauthorized();
	void Execute() {
		//
/*		while (true) {
			char sw;
			std::cin >> sw;
			switch (sw)
				case 'l':
				case 'r':
					ChatEngine::GOTO_RegistrationMenu();
				case 'q':
			{
			default:
				break;
			}
		}*/			
	};
private:
	void GOTO_RegistrationMenu(ChatEngine*, User*);
	void GOTO_MainMenu(ChatEngine*, User*);
};
class Registration : public State {
public:
	//create new user
	Registration();
	void Execute();
private:
	void GOTO_StartMenu(ChatEngine*);
	void GOTO_MainMenu(ChatEngine*, User*);
};
class MainMenu : public State {
public:
	//awoke ProfileSettings
	//awoke ChatObserver

	MainMenu();
	void Execute(User*);
private:
	void GOTO_StartMenu(ChatEngine*);
	void GOTO_ChangeProfileMenu(ChatEngine*, User*);
	void GOTO_AllConversations(ChatEngine*, User*);
private:
	User* _current_user;
};
class ProfileSettings : public State {
public:
	void Execute(User*);
	ProfileSettings();
private:
	void GOTO_MainMenu(ChatEngine*, User*);
private:
	User* _current_user;
};
class ChatObserver : public State {
public:
	//show new messages senders
	//contacts list
	//go to dialog
	ChatObserver();
	void Execute(User*);
private:
	void GOTO_StartMenu(ChatEngine*, User*);
	void GOTO_StartChatting(ChatEngine*, User*);
private:
	User* _current_user;
};
class Chatting : public State {
public:
	Chatting(User*);
	void Execute();
private:
	void GOTO_StartMenu(ChatEngine*, User*);
	void GOTO_AllConversations(ChatEngine*, User*);
private:
	User* _current_user;
};