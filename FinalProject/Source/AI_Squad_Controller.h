#pragma once

class AI_Squad_Controller : public StateMachine
{
	friend class PathfindingTests;

public:

	AI_Squad_Controller(GameObject & object)
		: StateMachine(object), m_moving(true) {}
	~AI_Squad_Controller(void) {}


private:

	virtual bool States(State_Machine_Event event, MSG_Object * msg, int state, int substate);

	//Put member variables or functions here
	int m_animStyle;	//0=walk, 1=jog
	int m_rowGoal;
	int m_colGoal;
	bool m_moving;
};
