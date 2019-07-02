#pragma once
enum AI_Main_States
{
	STATE_INIT = 0,
	STATE_GET_SQUAD_INFO = 1,
	STATE_CALCULATE = 2,
	STATE_GIVE_COMMANDS = 3,
	STATE_IDLE_WAIT = 4,
	STATE_EXIT = 5
};
enum Squad_Mission
{
	MISSION_NONE,
	MISSON_GOAL,
	MISSION_KILL_ENEMY
};
//forward declaration of a squadmemeber agent
class Squad_Member;

//a class that contains Info that the SquadController might need
class ReportData
{
	ReportData() {}
	~ReportData() {}

};
class AI_Squad_Controller
{
public:
	//constructor and destructor
	AI_Squad_Controller(GameObject & object);
	~AI_Squad_Controller();

	//Should only be called by GameObject
	void Update(void);
	void Reset(void);

	void ChangeState(AI_Main_States);
	void ReceiveReportFromSquadMember(GameObject & sender, ReportData message);
private:
	//owner of the statemachine
	GameObject * m_owner;
	std::vector<Squad_Member> m_squad_members;
	AI_Main_States m_current_state;
};
//the balckboard will store mission critcal details to be set in the INIT state of tyhe statemachine
//controller and squad members can access this
class SquadBlackboard
{
	SquadBlackboard() {}
	~SquadBlackboard() {}
	//the main mission the AI will always try to accomplish
	Squad_Mission m_main_mission;
	//the current mission the AI has to accomplsh before going back to main mission
	Squad_Mission m_current_mission;
	//where we store the goal position where we want the squad members to go to
	Cell GoalCell;
};