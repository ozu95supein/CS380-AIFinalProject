#pragma once

class AI_Squad_Member : public StateMachine
{
	friend class PathfindingTests;

public:

	AI_Squad_Member(GameObject & object, AI_Squad_Controller * cont) : StateMachine(object), m_moving(true)
	{
		SetSquadController(cont);
	}
	~AI_Squad_Member(void) {}

	void SetSquadController(AI_Squad_Controller * aisc);
	bool GoToGoalCell();
	bool moving_newRequest = true;
	void SetAnimStyleBruteForce(int i)
	{
		m_animStyle = i;
	}
private:

	virtual bool States(State_Machine_Event event, MSG_Object * msg, int state, int substate);

	//Put member variables or functions here
	int m_animStyle;	//0=walk, 1=jog
	int m_rowGoal;
	int m_colGoal;
	bool m_moving;
	AI_Squad_Controller * m_suqad_controller;

};
