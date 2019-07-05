#include <Stdafx.h>

extern D3DXVECTOR3 g_click3D;


//Add new states here
enum StateName {
	STATE_Initialize,	//Note: the first enum is the starting state
	STATE_IdleWait,		//do nothing and wait for squad member report
	STATE_GiveCommands,	//give commands to the agents
	STATE_Calculate		//use the blackboard to calculate the best option
};

//Add new substates here
enum SubstateName {
	//empty
};
//create all squad members
void AI_Squad_Controller::CreateSquadMembers()
{
	
}
void AI_Squad_Controller::AddSquadMember()
{
	World::CreateSquadMember();

}
bool AI_Squad_Controller::States(State_Machine_Event event, MSG_Object * msg, int state, int substate)
{
	BeginStateMachine

		//Global message responses

		OnMsg(MSG_MapChange)
		//////////////////////////////////////
		// Add code here to handle map changes
		//////////////////////////////////////
/*
	OnMsg(MSG_Reset)
		ResetStateMachine();

	OnMsg(MSG_SetHeuristicWeight)
		m_owner->GetMovement().SetHeuristicWeight(msg->GetFloatData());

	OnMsg(MSG_SetHeuristicCalc)
		m_owner->GetMovement().SetHeuristicCalc(msg->GetIntData());

	OnMsg(MSG_SetSmoothing)
		m_owner->GetMovement().SetSmoothPath(msg->GetBoolData());

	OnMsg(MSG_SetRubberbanding)
		m_owner->GetMovement().SetRubberbandPath(msg->GetBoolData());

	OnMsg(MSG_SetStraightline)
		m_owner->GetMovement().SetStraightlinePath(msg->GetBoolData());

	OnMsg(MSG_SetAgentSpeed)
		m_animStyle = msg->GetIntData();

	OnMsg(MSG_SetSingleStep)
		m_owner->GetMovement().SetSingleStep(msg->GetBoolData());

	OnMsg(MSG_ExtraCredit)
		m_owner->GetMovement().SetExtraCredit(msg->GetIntData());

	OnMsg(MSG_SetAStarDebugDraw)
		m_owner->GetMovement().SetDebugDraw(msg->GetBoolData());

	OnMsg(MSG_SetAStarUsesAnalysis)
		m_owner->GetMovement().AStarUsesAnalysis(msg->GetBoolData());

	OnMsg(MSG_SetMoving)
		m_moving = msg->GetBoolData();
*/

	///////////////////////////////////////////////////////////////
	DeclareState(STATE_Initialize)

		OnEnter
		//create squad members
		std::cout << " Enter  : Create Squad Members" << std::endl;
		
	OnUpdate
		std::cout << " Update : Create Squad Members" << std::endl;
		std::cout << " Update : Changing State" << std::endl;
		ChangeState(STATE_IdleWait);
	OnExit
		std::cout << " Exit   : Create Squad Members" << std::endl;
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_IdleWait)
		OnEnter
		//create squad members
		std::cout << " Enter  :  WAIT" << std::endl;
	OnUpdate
		//std::cout << " Update : WAIT" << std::endl;
	OnMsg(MSG_SetGoal)
		ChangeState(STATE_Calculate);
	OnExit
		std::cout << " Exit   : WAIT" << std::endl;

	///////////////////////////////////////////////////////////////
	DeclareState(STATE_Calculate)
		OnEnter
		//create squad members
		std::cout << " Enter  :  CALCULATE" << std::endl;
	OnUpdate
		std::cout << " Update : CALCULATE" << std::endl;
	ChangeState(STATE_GiveCommands);
	OnExit
		std::cout << " Exit   : CALCULATE" << std::endl;
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_GiveCommands)
		OnEnter
		//create squad members
		std::cout << " Enter  :  COMMANDS" << std::endl;
	OnUpdate
		std::cout << " Update : COMMANDS" << std::endl;
	ChangeState(STATE_IdleWait);

	OnExit
		std::cout << " Exit   : COMMANDS" << std::endl;

	/*
	DeclareState(STATE_CalcPath)

		OnEnter
		m_owner->GetMovement().SetIdleSpeed();

	OnUpdate
		Movement& move = m_owner->GetMovement();
	bool foundPath = m_owner->GetMovement().ComputePathWithTiming(m_rowGoal, m_colGoal, false);
	if (foundPath)
	{
		ChangeState(STATE_MoveToGoal);
	}


	///////////////////////////////////////////////////////////////
	DeclareState(STATE_MoveToGoal)

		OnEnter
		if (!m_moving) { ChangeState(STATE_Idle); }
	if (m_animStyle == 0) { m_owner->GetMovement().SetWalkSpeed(); }
	else if (m_animStyle == 1) { m_owner->GetMovement().SetJogSpeed(); }
	else { m_owner->GetMovement().SetWalkSpeed(); }

	OnMsg(MSG_Arrived)
		ChangeState(STATE_Idle);

	OnMsg(MSG_SetAgentSpeed)
		m_animStyle = msg->GetIntData();
	if (m_animStyle == 0) { m_owner->GetMovement().SetWalkSpeed(); }
	else if (m_animStyle == 1) { m_owner->GetMovement().SetJogSpeed(); }
	else { m_owner->GetMovement().SetWalkSpeed(); }


	///////////////////////////////////////////////////////////////
	DeclareState(STATE_Idle)

		OnEnter
		m_owner->GetMovement().SetIdleSpeed();

*/
	EndStateMachine
}

