#pragma once
enum Squad_Member_Mission
{
	MISSION_NoMission,
	MISSION_GoToGoal,
	MISSION_KillEnemy
};
class AI_Squad_BlackBoard;
class AI_Squad_Controller : public StateMachine
{
	friend class PathfindingTests;

public:

	AI_Squad_Controller(GameObject & object)
		: StateMachine(object), m_moving(true)
	{
		mBB = new AI_Squad_BlackBoard();
	}
	~AI_Squad_Controller(void) 
	{
		delete mBB;
	}
	AI_Squad_Controller & Get_AI_Squad_Controller()
	{
		return (*this);
	}

	void CreateSquadMembers();
	void AddSquadMember();
private:

	virtual bool States(State_Machine_Event event, MSG_Object * msg, int state, int substate);

	//Put member variables or functions here
	int m_animStyle;	//0=walk, 1=jog
	int m_rowGoal;
	int m_colGoal;
	bool m_moving;
	int MAXSQUADMEMBERS = 4;
	AI_Squad_BlackBoard * mBB;
};
class AI_Squad_BlackBoard
{
public:
	//the goal cell that the Agents must go to
	Cell FinalGoalCell;
	//the cell where the enemy is
	Cell EnemyCell;
	//a vector containing the pointers of the sqad members
	std::vector<GameObject *> m_squad_members;
	//Missions to give to the squad
	Squad_Member_Mission m_main_squad_mission;
	Squad_Member_Mission m_current_squad_mission;
};