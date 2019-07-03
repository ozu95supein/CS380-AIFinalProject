#pragma once
//NOTE, most of the frame work was taken and inspired by my team's GAM200 code

class CustomStateMachine;
class GameObject;

class CustomState
{
public:
	CustomState(const char * name);
	CustomState() {}

	virtual void Enter() {}
	virtual void Exit() {}
	virtual void Update() {}

	virtual void InternalEnter();
	virtual void InternalExit();
	virtual void InternalUpdate();

	CustomStateMachine * m_owner;
	std::string m_name;
	GameObject * m_actor;
	float m_time_in_state;
};
class CustomStateMachine
{
public:
	CustomStateMachine();
	CustomStateMachine(GameObject * actor);
	virtual ~CustomStateMachine();

	virtual void Initialize();
	virtual void Update();
	virtual void Terminate();

	void AddState(CustomState * state);
	void RemoveState(CustomState * state);
	void Clear();
	CustomState* GetState(const char * stateName);
	void SetInitState(CustomState * state);
	void SetInitState(const char * stateName);
	void ChangeState(CustomState * state);
	void ChangeState(const char * stateName);
	void StatusUpdate();
	void Reset();

	std::vector<CustomState*> mStates;
	GameObject * m_actor;
	CustomState * mPreviousState;
	CustomState * mCurrentState;
	CustomState * mNextState;
	CustomState * mInitialState;
};