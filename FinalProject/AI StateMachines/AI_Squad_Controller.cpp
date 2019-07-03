#include <Stdafx.h>

AI_Squad_Controller::AI_Squad_Controller()
{

}
AI_Squad_Controller::AI_Squad_Controller(GameObject * actor) : CustomStateMachine(actor)
{

}
void AI_Squad_Controller::Initialize()
{
	std::cout <<"AI_Squad_Controller : Initialize"<< std::endl;
	//creating a new state, must delete in the end
	this->AddState(new Controller_INIT_State("Controller_INIT_State"));
	this->AddState(new Controller_Commands_State("Controller_Commands_State"));
	//set the initial state to play
	this->SetInitState("Controller_INIT_State");
}
void AI_Squad_Controller::Update()
{
	StatusUpdate();
}
void AI_Squad_Controller::Terminate()
{

}