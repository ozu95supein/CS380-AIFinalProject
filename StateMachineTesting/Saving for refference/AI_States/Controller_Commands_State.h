#pragma once
class Controller_Commands_State : public CustomState
{
public:
	Controller_Commands_State(const char * name);
	Controller_Commands_State();
	~Controller_Commands_State();

	void Enter();
	void Exit();
	void Update();

};