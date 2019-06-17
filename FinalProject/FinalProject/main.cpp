#include "Common.h"

void QuitCheck(bool & b);
int main()
{
	bool running = true;
	char c;
	//while window is running
	while (running)
	{
		//get player input
		std::cout << "Player Input: ";
		std::cin >> c;
		switch (c)
		{
		//quit game
		case 'q':
		{
			QuitCheck(running);
		}
		break;
		//create agent
		case 'c':
		{
			std::cout << "Create Agent" << std::endl;
		}
		break;
		//run scenario
		case 'r':
		{
			std::cout << "Running Scenario" << std::endl;

		}
		break;
		default:
			break;
		}
		//update agent statemachines
		//	Agents choose goals
		//	Agents Choose actions
		//	Agents Perform Actions
		//	Wait for finish or interuption

	}
	return 0;
}
void QuitCheck(bool & b)
{
	std::cout << "Are you sure you want to quit? y/n: ";
	char c;
	std::cin >> c;
	if (c == 'y')
	{
		b = false;
	}
	else
	{
		b = true;
	}
}
