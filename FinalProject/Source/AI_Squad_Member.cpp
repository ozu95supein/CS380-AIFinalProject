#include <Stdafx.h>

extern D3DXVECTOR3 g_click3D;


//Add new states here
enum StateName {
	STATE_Initialize,			//Note: the first enum is the starting state
	STATE_DoNothing,			//do noting wait for orders
	STATE_KillEnemy,			//Go to pos near enemy, wait for backup, kill enemy
	STATE_GoToGoal,				//go to designated position
	STATE_ReportToController,	//report information to AI_Controller
	STATE_MissionComplete		//Current or main mission Complete
};

//Add new substates here
enum SubstateName {
	//empty
};
void AI_Squad_Member::SetSquadController(AI_Squad_Controller * aisc)
{
	m_suqad_controller = aisc;
}
bool AI_Squad_Member::States(State_Machine_Event event, MSG_Object * msg, int state, int substate)
{
	BeginStateMachine

		//Global message responses

		OnMsg(MSG_MapChange)
		//////////////////////////////////////
		// Add code here to handle map changes
		//////////////////////////////////////
		
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
		

	///////////////////////////////////////////////////////////////
	DeclareState(STATE_Initialize)

	OnEnter
		//create squad members
		std::cout << "MEMBER INIT ENTER" << std::endl;
	OnUpdate
		std::cout << "MEMBER INIT UPDATE" << std::endl;
		std::cout << "" << std::endl;
		ChangeState(STATE_DoNothing);
	OnExit
		std::cout << "MEMBER INIT EXIT" << std::endl;
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_DoNothing)
	OnEnter
		//create squad members
		std::cout << "MEMBER IDLE ENTER" << std::endl;
	OnUpdate
		
	OnExit
		std::cout << "MEMBER IDLE EXIT" << std::endl;

	///////////////////////////////////////////////////////////////
	DeclareState(STATE_KillEnemy)
	OnEnter
		//create squad members
		std::cout << "MEMBER KILL ENTER" << std::endl;
	OnUpdate
		std::cout << "" << std::endl;
	OnExit
		std::cout << "" << std::endl;
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_GoToGoal)
	OnEnter
		//create squad members
		std::cout << "MEMBER GOTO ENTER" << std::endl;
	OnUpdate
		std::cout << "" << std::endl;
		
	OnExit
		std::cout << "" << std::endl;
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_ReportToController)
		OnEnter
		//create squad members
		std::cout << "MEMBER REPORT ENTER" << std::endl;
	OnUpdate
		std::cout << "" << std::endl;

	OnExit
		std::cout << "" << std::endl;
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_MissionComplete)
		OnEnter
		//create squad members
		std::cout << "MEMBER MISSIONACCOMPLISHED ENTER" << std::endl;
	OnUpdate
		std::cout << "" << std::endl;

	OnExit
		std::cout << "" << std::endl;

	EndStateMachine
}

