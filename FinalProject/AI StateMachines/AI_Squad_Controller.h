#pragma once
class SquadBlackboard
{
public:

};
class AI_Squad_Controller : public CustomStateMachine
{
public:
	AI_Squad_Controller();
	AI_Squad_Controller(GameObject * actor);
	void Initialize();
	void Update();
	void Terminate();
	SquadBlackboard m_current_blackboard;
};
