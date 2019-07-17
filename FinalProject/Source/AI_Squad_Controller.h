#pragma once
enum Squad_Member_Mission
{
	MISSION_NoMission,
	MISSION_GoToGoal,
	MISSION_KillEnemy
};
//forward declarations
class AI_Squad_BlackBoard;
class GameObject;
class AI_Squad_Member;

class AI_Squad_Controller : public StateMachine
{
	friend class PathfindingTests;
	friend class AI_Squad_Member;
public:

	AI_Squad_Controller(GameObject & object)
		: StateMachine(object), m_moving(true)
	{

	}
	~AI_Squad_Controller(void)
	{

	}
	AI_Squad_Controller & Get_AI_Squad_Controller()
	{
		return (*this);
	}
	//first we set the BB
	void CreateAndSetBB();
	//then we add the squad members to the BB, both its game object and its controller
	void AddSquadMember(GameObject * MemberGO, AI_Squad_Member * MemberSM);
	AI_Squad_BlackBoard * GetBlackBoardPointer()
	{
		return mBB;
	}
	void SettingInitialMission();
	void GiveCommandsToSquad();
	void SetAnimStyleBruteForce(int i)
	{
		m_animStyle = i;
	}
	void SquadMemberReachedGoal();
	void EnemySighted();
	
	AI_Squad_BlackBoard * mBB;
	void SetCurrentEnemy(GameObject * e)
	{
		mBB->SetBBEnemy(e);
	}
	bool found_enemy = false;
private:

	virtual bool States(State_Machine_Event event, MSG_Object * msg, int state, int substate);

	//Put member variables or functions here
	int m_animStyle;	//0=walk, 1=jog
	int m_rowGoal;
	int m_colGoal;
	bool m_moving;
	int MAXSQUADMEMBERS = 4;
	
};
class AI_Squad_BlackBoard
{
public:
	//the goal cell that the Agents must go to
	Cell FinalGoalCell;
	//the cell where the enemy is
	Cell EnemyCell;
	GameObject * CurrentEnemy;
	void SetBBEnemy(GameObject * e)
	{
		CurrentEnemy = e;
	}
	//a vector containing the pointers of the sqad members
	//in game object form
	std::vector<GameObject *> m_squad_members_objects;
	//in AI_Squad_Member form
	std::vector<AI_Squad_Member *> m_squad_members_sm;

	//Missions to give to the squad
	Squad_Member_Mission m_main_squad_mission;
	Squad_Member_Mission m_current_squad_mission;

	int max_squad_members;
	int current_squad_members_performing_mission;
	int squad_members_at_goal = 0;
	//a vector of enemy agents on the terrain
	std::vector<GameObject *> m_enemy_agents;
	std::vector<GameObject *> m_enemy_agents_visible;
	bool CheckForEnemyBB(float range, GameObject * checker, GameObject * EnemyFound)
	{
		for (std::vector<GameObject *>::iterator it = m_enemy_agents.begin(); it != m_enemy_agents.end(); it++)
		{
			auto check_pos = checker->GetBody().GetPos();
			auto enemy_pos = (*it)->GetBody().GetPos();

			float x_diff = abs(check_pos.x - enemy_pos.x);
			float z_diff = abs(check_pos.z - enemy_pos.z);
			float distance = sqrt((x_diff*x_diff) + (z_diff*z_diff));
			if (distance <= range)
			{
				m_enemy_agents_visible.push_back(EnemyFound);
				EnemyFound = (*it);
				return true;
			}
		}
		EnemyFound = NULL;
		return false;
	}
	
};