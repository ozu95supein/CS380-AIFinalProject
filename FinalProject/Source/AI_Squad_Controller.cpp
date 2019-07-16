#include <Stdafx.h>

extern D3DXVECTOR3 g_click3D;

/*
//the goal cell that the Agents must go to
Cell FinalGoalCell;
//the cell where the enemy is
Cell EnemyCell;
//a vector containing the pointers of the sqad members
//in game object form
std::vector<GameObject *> m_squad_members_objects;
//in AI_Squad_Member form
std::vector<AI_Squad_Member *> m_squad_members_sm;

//Missions to give to the squad
Squad_Member_Mission m_main_squad_mission;
Squad_Member_Mission m_current_squad_mission;


*/
//Add new states here

enum StateName {
	STATE_Initialize,	//Note: the first enum is the starting state
	STATE_IdleWait,		//do nothing and wait for squad member report
	STATE_GiveCommands,	//give commands to the agents
	STATE_Calculate,		//use the blackboard to calculate the best option
	STATE_Pause			//pause until mouse click
};

//Add new substates here
enum SubstateName {
	//empty
};
//create and set the blackboard that both the controller and the members will use
void AI_Squad_Controller::CreateAndSetBB()
{
	this->mBB = new AI_Squad_BlackBoard();
}
void AI_Squad_Controller::AddSquadMember(GameObject * MemberGO, AI_Squad_Member * MemberSM)
{
	mBB->m_squad_members_objects.push_back(MemberGO);
	mBB->m_squad_members_sm.push_back(MemberSM);
}
void AI_Squad_Controller::SettingInitialMission()
{
	mBB->EnemyCell = Cell();
	mBB->FinalGoalCell = Cell(20, 39, nullptr);
	mBB->m_current_squad_mission = MISSION_GoToGoal;
	mBB->m_main_squad_mission = MISSION_GoToGoal;
	//this is for the squad members to report back
	mBB->max_squad_members = mBB->m_squad_members_sm.size();
	mBB->current_squad_members_performing_mission = 0;
}
void AI_Squad_Controller::GiveCommandsToSquad()
{
	//SendMessage();
	//MSG_ControllerToSquad_GoToGoal
	//
	//g_database.SendMsgFromSystem(MSG_SetHeuristicWeight, MSG_Data(g_heuristicWeight));
	if (mBB->m_current_squad_mission == MISSION_GoToGoal)
	{
		g_database.SendMsgFromSystem(MSG_ControllerToSquad_GoToGoal);
	}
	else if (mBB->m_current_squad_mission == MISSION_KillEnemy)
	{

	}
	else if (mBB->m_current_squad_mission == MISSION_NoMission)
	{

	}
	else
	{

	}
}
void AI_Squad_Controller::SquadMemberReachedGoal()
{

}
void AI_Squad_Controller::EnemySighted()
{
	found_enemy = true;
	//place every member in the calculate state
	std::vector<AI_Squad_Member *> vec = mBB->m_squad_members_sm;
	//iterate though the list of members and change their state
	for (std::vector<AI_Squad_Member *>::iterator it = mBB->m_squad_members_sm.begin(); it != mBB->m_squad_members_sm.end(); it++)
	{
		(*it)->ChangeToCalculate();
	}
	ChangeState(STATE_Calculate);
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
	DeclareState(STATE_Pause)
	
	OnEnter
	//create squad members
	std::cout << "CONTROLLER PAUSE" << std::endl;
	
	OnUpdate
		OnMsg(MSG_SetGoal)
		{
			ChangeState(STATE_GiveCommands);
		}
	OnExit
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_Initialize)

		OnEnter
		//create squad members
		std::cout << "CONTROLLER INIT" << std::endl;
		
	OnUpdate
		std::cout << " CONTROLLER Update : SettingInitialMission" << std::endl;
		this->SettingInitialMission();
		std::cout << " CONTROLLER Update : Changing State" << std::endl;
		ChangeState(STATE_Pause);
	OnExit
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_IdleWait)
		OnEnter
		//create squad members
		std::cout << "CONTROLLER Enter  :  WAIT" << std::endl;
	OnUpdate
	OnMsg(MSG_SquadToController_ReachedGoal)
		SquadMemberReachedGoal();
	OnMsg(MSG_SquadToController_EnemySighted)
		EnemySighted();
		
		//std::cout << " Update : WAIT" << std::endl;
	//OnMsg(MSG_SetGoal)
		//ChangeState(STATE_Calculate);
	OnExit
		std::cout << " Exit   : WAIT" << std::endl;

	///////////////////////////////////////////////////////////////
	DeclareState(STATE_Calculate)
		OnEnter
		//create squad members
		std::cout << "CONTROLLER  :  CALCULATE" << std::endl;
	OnUpdate
		std::cout << "CONTROLLER Update : CALCULATE" << std::endl;
	ChangeState(STATE_GiveCommands);
	OnExit
		
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_GiveCommands)
		OnEnter
		std::cout << "CONTROLLER Enter  :  COMMANDS" << std::endl;
	OnUpdate
		std::cout << "CONTROLLER Update : COMMANDS" << std::endl;
		std::cout << "CONTROLLER Update : COMMANDS Given" << std::endl;
		//keep sending messages untill all squad memebrs copy back
		GiveCommandsToSquad();
		//wait for all squad members to report in
		//OnMsg(MSG_SquadToController_CopyThat)
		//{
		//	mBB->current_squad_members_performing_mission++;
		//	//if the entire squad has copied back we change state
		//	if (mBB->current_squad_members_performing_mission >= mBB->max_squad_members)
		//	{
		//		ChangeState(STATE_IdleWait);
		//	}
		//}
		ChangeState(STATE_IdleWait);

	OnExit
		
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

