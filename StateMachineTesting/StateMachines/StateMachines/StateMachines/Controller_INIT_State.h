#pragma once
class Controller_INIT_State : public CustomState
{
public:
	Controller_INIT_State(const char * name);
	Controller_INIT_State();
	~Controller_INIT_State();

	void Enter();
	void Exit();
	void Update();

};