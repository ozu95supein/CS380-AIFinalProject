#include <Stdafx.h>

CustomStateMachine::CustomStateMachine()
{
	m_actor = nullptr;                                     //set actor to NULL
	mCurrentState = mNextState = mCurrentState = mPreviousState = nullptr; //set states to NULL
}
CustomStateMachine::CustomStateMachine(GameObject * actor)
{
	actor = actor;                                    //set actor
	mCurrentState = mNextState = mCurrentState = mPreviousState = NULL; //set states to NULL
}
CustomStateMachine::~CustomStateMachine()
{
	for (auto it = mStates.begin(); it != mStates.end(); it++) {
		CustomState * temp = (*it);
		delete temp;
	}
	mStates.clear();
}

void CustomStateMachine::Initialize() {}
void CustomStateMachine::Update() {}
void CustomStateMachine::Terminate() {}

void CustomStateMachine::AddState(CustomState * state)
{
	bool same = false; //to check for a name which is the same
	if (state != NULL) //Sanity check 1
	{
		for (std::vector<CustomState*>::iterator it = mStates.begin(); it != mStates.end(); it++) //Sanity check 2
		{
			if ((*it)->m_name == state->m_name) //if the name was already taken
				same = true; //same name detected
		}
		if (!same) //if the same name is not encuntered
		{
			state->m_actor = m_actor;           //specify the actor
			state->m_owner = this; //specify this states staemchine
			mStates.push_back(state);         //push the new state
		}
	}
}

void CustomStateMachine::RemoveState(CustomState * state)
{
	if (state != NULL) //Sanity check 1
	{
		for (unsigned i = 0; i < mStates.size(); i++) //iterate through the states
		{
			if (mStates[i] == state) //if the name was already taken
				mStates.erase(mStates.begin() + i); //erase
		}
	}
}

void CustomStateMachine::Clear()
{
	while (!mStates.empty()) //while there are states
	{
		delete(mStates.back()->m_owner); //delete the last states owner pointer

		mStates.pop_back(); //delete the last state
	}

	mCurrentState = mNextState = mCurrentState = mPreviousState = NULL; //set state pointers to NULL
}

CustomState* CustomStateMachine::GetState(const char * stateName)
{
	for (std::vector<CustomState*>::iterator it = mStates.begin(); it != mStates.end(); it++) //iterate through states
	{
		if ((*it)->m_name == stateName) //if the name was found
		{
			return (*it); //return pointer to the state
		}
	}
	return NULL; //name not found
}

void CustomStateMachine::SetInitState(CustomState * state)
{
	for (std::vector<CustomState*>::iterator it = mStates.begin(); it != mStates.end(); it++) //iterate through states
	{
		if ((*it) == state) //if the state was found
			mInitialState = state; //modify initial state
								   //mCurrentState = state;
	}
}

void CustomStateMachine::SetInitState(const char * stateName)
{
	mInitialState = CustomStateMachine::GetState(stateName); //reuse
													   //mCurrentState = StateMachine::GetState(stateName);
}

void CustomStateMachine::ChangeState(CustomState * state)
{
	if (state != NULL) //Sanity check 1
	{
		for (std::vector<CustomState*>::iterator it = mStates.begin(); it != mStates.end(); it++) //iterate through states
		{
			if ((*it) == state) //if the state was found
				mNextState = state; //modify next state
		}
	}
}

void CustomStateMachine::ChangeState(const char * stateName)
{
	mNextState = CustomStateMachine::GetState(stateName); //reuse
}

void CustomStateMachine::StatusUpdate()
{
	if (mCurrentState) //sanity check
		mCurrentState->InternalUpdate(); //this won't be called the first time we enter

	else //not original code
	{
		mNextState = mCurrentState = mInitialState;
	}

	if (mCurrentState != mNextState) //first time update is called it will enter here and set all the states
	{
		mPreviousState = mCurrentState;

		//std::cout << "Change state" << std::endl;
		if (mCurrentState) //sanity check
			mCurrentState->InternalExit();  //aply exit code

		mCurrentState = mNextState; //change the state

		if (mCurrentState) //sanity check
			mCurrentState->InternalEnter(); //apply enter code
	}

	/*
	//Update the current
	if(mCurrentState)
	mCurrentState->InternalUpdate();

	//If there have been changes, update the Current state with next
	if (mCurrentState != mNextState)
	{
	if (mCurrentState)
	mCurrentState->InternalExit(); // Before doing anything, exit

	mCurrentState = mNextState;

	if (mCurrentState)
	mCurrentState->InternalEnter(); // Before doing anything, enter
	}
	*/
}

void CustomStateMachine::Reset()
{
	ChangeState(mCurrentState); //ok
}

CustomState::CustomState(const char * name)
{
	m_name = name; // set name
	m_owner = nullptr;
	m_actor = nullptr; // NULL init
}

void CustomState::InternalEnter()
{
	m_time_in_state = 0.0f; //start countig when entering
	Enter();             //call enter (I guess we will say what happens in enter)
}

void CustomState::InternalExit()
{
	Exit(); //call exit
}

void CustomState::InternalUpdate()
{
	//m_time_in_state += (float)ImGui::GetIO().DeltaTime; // increment timer
	Update();										  // update
}
