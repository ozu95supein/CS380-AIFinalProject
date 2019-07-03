#include <Stdafx.h>

Controller_INIT_State::Controller_INIT_State(const char * name)
{

}
Controller_INIT_State::Controller_INIT_State()
{

}
Controller_INIT_State::~Controller_INIT_State()
{

}

void Controller_INIT_State::Enter()
{
	//create agents
	std::cout << "Controller_INIT_State : Creating Agents " << std::endl;
}
void Controller_INIT_State::Exit()
{

}
void Controller_INIT_State::Update()
{
	std::cout << "Controller_INIT_State : Changing State " << std::endl;
	m_owner->ChangeState("Give_Commands");
}