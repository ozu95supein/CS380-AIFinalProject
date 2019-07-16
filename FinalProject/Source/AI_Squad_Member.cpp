#include <Stdafx.h>

extern D3DXVECTOR3 g_click3D;


//Add new states here
enum StateName{
	STATE_MemberInitialize,			//Note: the first enum is the starting state
	STATE_MemberDoNothing,			//do noting wait for orders
	STATE_MemberKillEnemy,			//Go to pos near enemy, wait for backup, kill enemy
	STATE_MemberGoToGoal,				//go to designated position
	STATE_MemberReportToController,	//report information to AI_Controller
	State_MemberHelpCalculate,		//go to BB and assist in planning
	STATE_MemberMissionComplete		//Current or main mission Complete
};

//Add new substates here
enum SubstateName {
	//empty
};
void AI_Squad_Member::SetSquadController(AI_Squad_Controller * aisc)
{
	m_suqad_controller = aisc;
}
void AI_Squad_Member::ChangeToCalculate()
{
	ChangeState(State_MemberHelpCalculate);
}
bool AI_Squad_Member::GoToGoalCell()
{
	//bool Movement::ComputePath(int r, int c, bool newRequest)
	//bool Movement::ComputePathWithTiming(int r, int c, bool newRequest)
	auto BB = this->m_suqad_controller->GetBlackBoardPointer();
	bool m;
	if (moving_newRequest)
	{
		std::cout << "MEMBER: new request run astar" << std::endl;
		m = m_owner->GetMovement().ComputePathWithTiming(BB->FinalGoalCell.Gety(), BB->FinalGoalCell.Getx(), true);
		moving_newRequest = false;
	}
	else
	{
		std::cout << "MEMBER: run astar" << std::endl;
		m = m_owner->GetMovement().ComputePathWithTiming(BB->FinalGoalCell.Gety(), BB->FinalGoalCell.Getx(), false);
	}
	return m;
}
bool AI_Squad_Member::GoToEnemyCell()
{
	//bool Movement::ComputePath(int r, int c, bool newRequest)
	//bool Movement::ComputePathWithTiming(int r, int c, bool newRequest)
	auto BB = this->m_suqad_controller->GetBlackBoardPointer();
	bool m;
	if (moving_newRequest)
	{
		std::cout << "MEMBER: new request run astar" << std::endl;
		m = m_owner->GetMovement().ComputePathWithTiming(BB->EnemyCell.Gety(), BB->EnemyCell.Getx(), true);
		moving_newRequest = false;
	}
	else
	{
		std::cout << "MEMBER: run astar" << std::endl;
		m = m_owner->GetMovement().ComputePathWithTiming(BB->EnemyCell.Gety(), BB->EnemyCell.Getx(), false);
	}
	return m;
}
void AI_Squad_Member::ProcessTheGoToGoalResult(bool path)
{
	if (path == true)
	{
		std::cout << "MEMBER Reached Goal" << std::endl;
		g_database.SendMsgFromSystem(MSG_SquadToController_ReachedGoal);
		m_suqad_controller->GetBlackBoardPointer()->squad_members_at_goal++;
		if (m_suqad_controller->GetBlackBoardPointer()->squad_members_at_goal == m_suqad_controller->GetBlackBoardPointer()->max_squad_members)
		{
			std::cout << "MEMBER ALL MEMBERS HAVE REACHED GOAL" << std::endl;

		}
		ChangeState(STATE_MemberDoNothing);
	}
}
void AI_Squad_Member::KillEnemyFirstCall()
{
	moving_newRequest = true;
	GoToEnemyCell();
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
	DeclareState(STATE_MemberInitialize)

	OnEnter
		std::cout << "MEMBER INIT ENTER" << std::endl;
	OnUpdate
		std::cout << "MEMBER INIT UPDATE" << std::endl;
		ChangeState(STATE_MemberDoNothing);
	OnExit
		std::cout << "MEMBER INIT EXIT" << std::endl;
	///////////////////////////////////////////////////////////////
	DeclareState(State_MemberHelpCalculate)

		OnEnter
		std::cout << "MEMBER Calculate ENTER" << std::endl;
	OnUpdate
		OnMsg(MSG_ControllerToSquad_KillEnemy);
			KillEnemyFirstCall();
	OnExit
		std::cout << "MEMBER Calculate EXIT" << std::endl;
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_MemberDoNothing)
	OnEnter
		//create squad members
		std::cout << "MEMBER IDLE ENTER" << std::endl;
	OnUpdate
		//controller tells squad to go to goal
	OnMsg(MSG_ControllerToSquad_GoToGoal);
	{
		//squad member says "copy that" back to 
		g_database.SendMsgFromSystem(MSG_SquadToController_CopyThat);
		moving_newRequest = true;
		GoToGoalCell();
		ChangeState(STATE_MemberGoToGoal);
	}
		
	OnExit
		std::cout << "MEMBER IDLE EXIT" << std::endl;

	///////////////////////////////////////////////////////////////
	DeclareState(STATE_MemberKillEnemy)
	OnEnter
		//create squad members
		std::cout << "MEMBER KILL ENTER" << std::endl;
	OnUpdate
	OnExit
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_MemberGoToGoal)
	OnEnter
		//create squad members
		std::cout << "MEMBER GOTO ENTER" << std::endl;
	OnUpdate
	{
		std::cout << "MEMBER GoToCell" << std::endl;

		//check for enemies in nearby cells
		GameObject * temp = NULL;
		bool enemy = CheckForEnemy(0.2f, temp);
		if (enemy)
		{
			m_suqad_controller->SetCurrentEnemy(temp);
			//REGISTER_MESSAGE_NAME(MSG_SquadToController_CopyThat)
			g_database.SendMsgFromSystem(MSG_SquadToController_EnemySighted);
			break;
		}
		bool result = false;
		result = GoToGoalCell();
		ProcessTheGoToGoalResult(result);
		
	}
	OnExit
		std::cout << "" << std::endl;
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_MemberReportToController)
		OnEnter
		//create squad members
		std::cout << "MEMBER REPORT ENTER" << std::endl;
	OnUpdate
		std::cout << "" << std::endl;

	OnExit
		std::cout << "" << std::endl;
	///////////////////////////////////////////////////////////////
	DeclareState(STATE_MemberMissionComplete)
		OnEnter
		//create squad members
		std::cout << "MEMBER MISSIONACCOMPLISHED ENTER" << std::endl;
	OnUpdate
		std::cout << "" << std::endl;

	OnExit
		std::cout << "" << std::endl;

	EndStateMachine
}
bool AI_Squad_Member::CheckForEnemy(float range, GameObject * EnemyFound)
{
	bool result = m_suqad_controller->GetBlackBoardPointer()->CheckForEnemyBB(range, (this->GetManager()->GetOwner()), EnemyFound);
	if (result)
	{
		return true;
	}
	else
	{
		return false;
	}
}
