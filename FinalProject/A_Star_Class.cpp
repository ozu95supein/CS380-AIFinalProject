#include <Stdafx.h>

A_Star_Class::A_Star_Class(): FinalNode(Cell())
{
	SetMinMaxCell(0, g_terrain.GetWidth());
}
//constructor
A_Star_Class::A_Star_Class(Cell start, Cell goal): FinalNode(goal)
{
	SetStartAndGoal(start, goal);
	SetMinMaxCell(0, g_terrain.GetWidth());
}
//functions to set start and goal nodes
void A_Star_Class::SetStart(Cell start)
{
	mStartCell = start;
}
void A_Star_Class::SetGoal(Cell goal)
{
	mGoalCell = goal;
}
void A_Star_Class::SetStartAndGoal(Cell start, Cell goal)
{
	SetStart(start);
	SetGoal(goal);
	SetMinMaxCell(0, g_terrain.GetWidth());
}

//will take a priority_q reference and a copy of the found cell if it exists
bool FindInOPEN(std::priority_queue<Cell> & q, Cell & return_cell, Cell & TargetCell)
{
	std::priority_queue<Cell> temp_q = q;
	while (temp_q.empty() != true)
	{
		Cell c = temp_q.top();
		return_cell = c;
		temp_q.pop();
		//check if its the same as the target cell in x y coordinates
		if (return_cell.Getx() == TargetCell.Getx())
		{
			if (return_cell.Gety() == TargetCell.Gety())
			{
				return true;
			}
		}
	}
	return false;
}
bool FindInCLOSED(std::list<Cell> & l, Cell * return_cell, Cell & Target_Cell)
{
	std::list<Cell>::iterator it = l.begin();
	while (it != l.end())
	{
		if (it->Getx() == Target_Cell.Getx())
		{
			if (it->Gety() == Target_Cell.Gety())
			{
				return_cell = &(*it);
				return true;
			}
		}
		it++;
	}
	return false;
}
Cell & A_Star_Class::POP_cheapest_from_OPEN()
{
	std::list<Cell>::iterator it = OPEN_LIST.begin();
	Cell * cellToReturn = &(*it);
	float min_cost = it->GetFCost();
	while (it != OPEN_LIST.end())
	{
		if (it->GetFCost() < min_cost)
		{
			min_cost = it->GetFCost();
			cellToReturn = &(*it);
		}
		it++;
	}
	Cell c = *cellToReturn;
	//pop
	OPEN_LIST.remove(*cellToReturn);
	return c;
}
bool A_Star_Class::Check_If_Goal(Cell & c)
{
	if (c.Getx() == GetGoal().Getx())
	{
		if (c.Gety() == GetGoal().Gety())
		{
			return true;
		}
	}
	return false;
}
void A_Star_Class::Compute_And_Set_Costs(float & hcost, float & fcost, Cell & c)
{
	if ((c.Getx() == 4) && (c.Gety() == 7))
	{
		//up
		char y;
		auto f = c.GetFCost();
	}
	if ((c.Getx() == 3) && (c.Gety() == 7))
	{
		//up left
		char y;
		auto f = c.GetFCost();
	}
	if ((c.Getx() == 5) && (c.Gety() == 7))
	{
		//up
		char y;
		auto f = c.GetFCost();
	}
	hcost = GetHeuristicWeight() * CalculateHeuristic(c);
	fcost = c.GetGCost() + hcost;
	c.SetFCost(fcost);
}
bool A_Star_Class::FindInList(std::list<Cell> l, Cell CellToFind, Cell & CellToReturn)
{
	//iterate through the list
	std::list<Cell>::iterator iter = l.begin();
	while (iter != l.end())
	{
		//check if it has the same coordinates
		if (iter->Getx() == CellToFind.Getx())
		{
			if (iter->Gety() == CellToFind.Gety())
			{
				//if so, save the contents of iter and return true using the cell to return
				Cell c = *iter;
				CellToReturn = c;
				return true;
			}
		}
		iter++;
	}
	//if we get here return false
	return false;
}
void A_Star_Class::ConstructPath(Cell & goal)
{
	full_path.clear();
	Cell * parent = goal.GetParent();
	full_path.push_front(goal);
	while (parent != NULL)
	{
		full_path.push_front(*parent);
		parent = parent->GetParent();
	}
}
void A_Star_Class::SetFinalNode(Cell c)
{
	FinalNode = c;
}
void A_Star_Class::BeginAstar()
{
	path_found = false;
	//push start node to OPEN LIST
	OPEN_LIST.clear();
	CLOSED_LIST.clear();
	OPEN_LIST.push_back(GetStart());
}

//D3DXVECTOR3 position = g_terrain.GetCoordinates(c.Gety(), c.Getx());
//g_terrain.SetColor(c.Gety(), c.Getx(), DEBUG_COLOR_YELLOW);

//funtion to get a path from the start to the goal, returns false if no path is found,
//will return true if a path is found. It will store the optimal path in a list in this class
bool A_Star_Class::Iteration()
{	
	//POP CHEAPEST NODE OFF OPEN LIST
	Cell mCurrentPopedCell = POP_cheapest_from_OPEN();
	//check if it is the goal
	auto c = GetGoal();
	auto s = GetStart();
	//debug color yellow for closed list
	//D3DXVECTOR3 position = g_terrain.GetCoordinates(mCurrentPopedCell.Gety(), mCurrentPopedCell.Getx());
	g_terrain.SetColor(mCurrentPopedCell.Gety(), mCurrentPopedCell.Getx(), DEBUG_COLOR_YELLOW);
	if (Check_If_Goal(mCurrentPopedCell))
	{
		//do whatever you need to do
		ConstructPath(mCurrentPopedCell);
		auto c = GetGoal();
		auto s = GetStart();
		
		path_found = true;
		return true;
	}
	//get neighboring child cells
	//HERE
	std::list<Cell> neighbors = get_neighbors(mCurrentPopedCell);
	//premtively place mcurrentcell on the closed list so we can set the parent later
	CLOSED_LIST.push_back(mCurrentPopedCell);
	//iterate through the neighbors
	for (std::list<Cell>::iterator it = neighbors.begin(); it != neighbors.end(); it++)
	{
		//compute the cost and set it for the cell
		float hcost = 0.0f;
		float fcost = 0.0f;
		if (it->Getx() == 5)
		{
			if (it->Gety() == 7)
			{
				auto v = *it;
			}
		}
		Compute_And_Set_Costs(hcost, fcost, *it);

		//bool A_Star_Class::FindInList(std::list<Cell> l, Cell CellToFind, Cell & CellToReturn)
		Cell open_cell;
		bool open_found = FindInList(OPEN_LIST, *it, open_cell);
		Cell closed_cell;
		bool closed_found = FindInList(CLOSED_LIST, *it, closed_cell);

		//if child is not on open nor closed place it in OPEN LIST
		if ((open_found == false) && (closed_found == false))
		{
			//dont forget to set the parent from the closed list
			//find the reference to the parent in the closed list
			std::list<Cell>::iterator parent = std::find(CLOSED_LIST.begin(), CLOSED_LIST.end(), mCurrentPopedCell);
			//set the parent of the node you are about to push
			it->SetParent(&(*parent));
			//push to the open list
			OPEN_LIST.push_back(*it);
			//debug color blue for open list
			//D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
			g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_BLUE);
		}
		//if it is in at least one of those lists
		else
		{
			//find out which list it's in
			if (open_found == true)
			{
				//check if "it" is cheaper than the one in the list
				if (it->GetFCost() < open_cell.GetFCost())
				{
					//remove expensive one from both lists
					OPEN_LIST.remove(open_cell);
					CLOSED_LIST.remove(closed_cell);
					//dont forget to set the parent from the closed list
					//find the reference to the parent in the closed list
					std::list<Cell>::iterator parent = std::find(CLOSED_LIST.begin(), CLOSED_LIST.end(), mCurrentPopedCell);
					//set the parent of the node you are about to push
					it->SetParent(&(*parent));
					//place it on the open list
					OPEN_LIST.push_back(*it);
					//debug color blue for open list
					//D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
					g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_BLUE);
				}
			}
			else if (closed_found == true)
			{
				//check if "it" is cheaper than the one in the list
				if (it->GetFCost() < closed_cell.GetFCost())
				{
					//remove expensive one from both lists
					OPEN_LIST.remove(open_cell);
					CLOSED_LIST.remove(closed_cell);
					//dont forget to set the parent from the closed list
					//find the reference to the parent in the closed list
					std::list<Cell>::iterator parent = std::find(CLOSED_LIST.begin(), CLOSED_LIST.end(), mCurrentPopedCell);
					//set the parent of the node you are about to push
					it->SetParent(&(*parent));
					//place it on the open list
					OPEN_LIST.push_back(*it);
					//debug color blue for open list
					//D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
					g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_BLUE);
				}
			}
		}
	}
	mCurrentCellBeingAnalyzed = mCurrentPopedCell;
	return false;
}
//go backwards node from node until you can make a straightline
//will return end() if no straightline optimization is available
bool A_Star_Class::StraightLineOptimization(std::list<Cell> list, Cell & return_cell)
{
	if (list.size() < 3)
	{
		return false;
	}
	auto temp_list = list;
	//revese the contents of the list in the temp one
	temp_list.reverse();
	std::list<Cell>::iterator iter = temp_list.begin();
	std::list<Cell>::iterator next_iter = iter;
	bool slc_result = false;
	do
	{
		//increment next iter
		next_iter++;
		//exit condition
		if (next_iter == temp_list.end())
		{
			return true;
			break;
		}
		slc_result = StraightlineCheck(*iter, *next_iter, false);
		//if false we need to take the current iter and exit
		if (slc_result == false)
		{
			//check if it is the first iteration
			if (iter == temp_list.begin())
			{
				return false;
			}
			//take the current iter and exit
			else
			{
				return_cell = *iter;
				return true;
			}
			break;
		}
		else
		{
			//increment iter
			iter++;
		}	
	} while (true);
	return true;
}
bool A_Star_Class::RunAStar(bool single)
{
	if(single)
	{

		bool result = Iteration();
		if (result == true)
		{
			return true;
		}
		return false;
	}
	else
	{
		while (OPEN_LIST.empty() != true)
		{
			bool result = Iteration();
			if (result == true)
			{
				return true;
			}
		}
		path_found = false;
		return true;
	}
	
}

void A_Star_Class::SetHeuristicMethod(heuristic h)
{
	mCurrent_H_Method = h;
}
Cell A_Star_Class::GetStart()
{
	return mStartCell;
}
Cell A_Star_Class::GetGoal()
{
	return mGoalCell;
}

std::list<Cell> A_Star_Class::get_neighbors(Cell & current)
{
	std::list<Cell> neighbors;
	float diag = (float)sqrt(2);
	Cell * Parent = &current;
	bool up_wall = false;
	bool down_wall = false;
	bool left_wall = false;
	bool right_wall = false;

	// extract cardinal neighbors and filter walls
	//up
	if ((current.Gety() + 1) < g_terrain.GetWidth())
	{
		if (g_terrain.IsWall((current.Gety() + 1), (current.Getx())) == false)
		{
			//Cell((centralNode->Gety() + 1), (centralNode->Getx()), centralNode);
			Cell c;
			c.Setx(current.Getx());
			c.Sety(current.Gety() + 1);
			if (current.GetParent() != NULL)
			{
				c.SetGCost(1.0f + current.GetGCost());
			}
			else
			{
				c.SetGCost(1.0f);
			}
			neighbors.push_back(c);
		}
		else
		{
			up_wall = true;
		}
	}
	//down
	if ((current.Gety() - 1) >= 0)
	{
		if (g_terrain.IsWall((current.Gety() - 1), (current.Getx())) == false)
		{
			//Cell((centralNode->Gety() + 1), (centralNode->Getx()), centralNode);
			Cell c;
			c.Setx(current.Getx());
			c.Sety(current.Gety() - 1);
			if (current.GetParent() != NULL)
			{
				c.SetGCost(1.0f + current.GetGCost());
			}
			else
			{
				c.SetGCost(1.0f);
			}
			neighbors.push_back(c);
		}
		else
		{
			down_wall = true;
		}
	}
	//left
	if ((current.Getx() - 1) >= 0)
	{
		if (g_terrain.IsWall(current.Gety(), (current.Getx() - 1)) == false)
		{
			//Cell((centralNode->Gety() + 1), (centralNode->Getx()), centralNode);
			Cell c;
			c.Setx(current.Getx() - 1);
			c.Sety(current.Gety());
			if (current.GetParent() != NULL)
			{
				c.SetGCost(1.0f + current.GetGCost());
			}
			else
			{
				c.SetGCost(1.0f);
			}
			neighbors.push_back(c);
		}
		else
		{
			left_wall = true;
		}
	}
	//right
	if ((current.Getx() + 1) < g_terrain.GetWidth())
	{
		if (g_terrain.IsWall(current.Gety(), (current.Getx() + 1)) == false)
		{
			//Cell((centralNode->Gety() + 1), (centralNode->Getx()), centralNode);
			Cell c;
			c.Setx(current.Getx() + 1);
			c.Sety(current.Gety());
			if (current.GetParent() != NULL)
			{
				c.SetGCost(1.0f + current.GetGCost());
			}
			else
			{
				c.SetGCost(1.0f);
			}
			neighbors.push_back(c);
		}
		else
		{
			right_wall = true;
		}
	}
	
	// extract diagonal neighbors and filter walls
	//up left
	if(((current.Gety() + 1) < g_terrain.GetWidth()) && ((current.Getx() - 1) >= 0))
	{
		if (g_terrain.IsWall((current.Gety() + 1), (current.Getx() - 1)) == false)
		{
			//check corners
			if ((up_wall == false) && (left_wall == false))
			{
				//Cell((centralNode->Gety() + 1), (centralNode->Getx()), centralNode);
				Cell c;
				c.Setx(current.Getx() - 1);
				c.Sety(current.Gety() + 1);
				if (current.GetParent() != NULL)
				{
					c.SetGCost(diag + current.GetGCost());
				}
				else
				{
					c.SetGCost(diag);
				}
				neighbors.push_back(c);
			}
			
		}
	}
	
	//up right
	if (((current.Gety() + 1) < g_terrain.GetWidth()) && ((current.Getx() + 1) < g_terrain.GetWidth()))
	{
		if (g_terrain.IsWall((current.Gety() + 1), (current.Getx() + 1)) == false)
		{
			//check corners
			if ((up_wall == false) && (right_wall == false))
			{
				//Cell((centralNode->Gety() + 1), (centralNode->Getx()), centralNode);
				Cell c;
				c.Setx(current.Getx() + 1);
				c.Sety(current.Gety() + 1);
				if (current.GetParent() != NULL)
				{
					c.SetGCost(diag + current.GetGCost());
				}
				else
				{
					c.SetGCost(diag);
				}
				neighbors.push_back(c);
			}
		}
	}
	
	//down left
	if (((current.Gety() - 1) >= 0) && ((current.Getx() - 1) >= 0))
	{
		//check corners
		if ((down_wall == false) && (left_wall == false))
		{
			if (g_terrain.IsWall(current.Gety() - 1, (current.Getx() - 1)) == false)
			{
				//Cell((centralNode->Gety() + 1), (centralNode->Getx()), centralNode);
				Cell c;
				c.Setx(current.Getx() - 1);
				c.Sety(current.Gety() - 1);
				if (current.GetParent() != NULL)
				{
					c.SetGCost(diag + current.GetGCost());
				}
				else
				{
					c.SetGCost(diag);
				}
				neighbors.push_back(c);
			}
		}
	}
	//down right
	if (((current.Gety() - 1) >= 0) && ((current.Getx() + 1) < g_terrain.GetWidth()))
	{
		//check corners
		if ((down_wall == false) && (right_wall == false))
		{
			if (g_terrain.IsWall(current.Gety() - 1, (current.Getx() + 1)) == false)
			{
				//Cell((centralNode->Gety() + 1), (centralNode->Getx()), centralNode);
				Cell c;
				c.Setx(current.Getx() + 1);
				c.Sety(current.Gety() - 1);
				if (current.GetParent() != NULL)
				{
					c.SetGCost(diag + current.GetGCost());
				}
				else
				{
					c.SetGCost(diag);
				}
				neighbors.push_back(c);
			}
		}
		
	}
	
	// filter current's parent
	//might want to optimize this
	//check if current actually has a parent
	if (current.GetParent() != NULL)
	{
		//go through the list and eliminate
		std::list<Cell>::iterator iter = neighbors.begin();
		//iterate
		while (iter != neighbors.end())
		{
			//if it has the same coordinates as the parent...
			if (iter->Getx() == current.GetParent()->Getx())
			{
				if (iter->Gety() == current.GetParent()->Gety())
				{
					//...we erase it
					neighbors.remove(*iter++);
					break;
				}
			}
			iter++;
		}
	}
	return neighbors;
}
float A_Star_Class::GetHeuristicWeight()
{
	if (mCurrent_H_Method == H_OCTILE)
		return 1.01;
	return H_weight;
}
void A_Star_Class::SetHeuristicWeight(float h)
{
	H_weight = h;
}
float A_Star_Class::CalculateHeuristic(Cell & currentNode)
{
	//manhattan
	//int xdiff = abs(GetGoal()->Getx() - currentNeighbourCell->Getx());
	//int ydiff = abs(GetGoal()->Gety() - currentNeighbourCell->Gety());
	//int result = xdiff + ydiff;
	float result;
	if (mCurrent_H_Method == H_MANHATTAN)
	{
		auto r = GetGoal().Getx();
		auto g = GetGoal().Gety();
		auto b = currentNode.Getx();
		auto a = currentNode.Gety();

		int xdiff = abs(GetGoal().Getx() - currentNode.Getx());
		int ydiff = abs(GetGoal().Gety() - currentNode.Gety());
		result = xdiff + ydiff;
	}
	else if (mCurrent_H_Method == H_CHEBYSHEV)
	{
		int xdiff = abs(GetGoal().Getx() - currentNode.Getx());
		int ydiff = abs(GetGoal().Gety() - currentNode.Gety());
		result = max(xdiff, ydiff);
	}
	else if (mCurrent_H_Method == H_EUCLIDEAN)
	{
		int xdiff = abs(GetGoal().Getx() - currentNode.Getx());
		int ydiff = abs(GetGoal().Gety() - currentNode.Gety());
		result = sqrt((xdiff*xdiff) + (ydiff*ydiff));
	}
	else if (mCurrent_H_Method == H_OCTILE)
	{
		int xdiff = abs(GetGoal().Getx() - currentNode.Getx());
		int ydiff = abs(GetGoal().Gety() - currentNode.Gety());
		result = ((min(xdiff, ydiff)*sqrt(2)) + (max(xdiff, ydiff)) - min(xdiff, ydiff));
	}
	auto g = GetGoal();
	return result;
}
std::list<Cell> A_Star_Class::get_full_path()
{
	return full_path;
}
//return true if there are no wall tiles
bool A_Star_Class::StraightlineCheck(Cell start, Cell goal, bool modify_var)
{
	int start_row = start.Gety();
	int start_col = start.Getx();
	int goal_row = goal.Gety();
	int goal_col = goal.Getx();
	//start by initializing the r and c
	int r = start_row;
	int c = start_col;
	//the things to add or subtract to
	int r_inc;
	int c_inc;
	//if negative
	if ((goal_row - start_row) < 0)
	{
		r_inc = -1;
	}
	else if((goal_row - start_row) > 0)
	{
		r_inc = 1;
	}
	else
	{
		r_inc = 0;
	}
	//if negative
	if ((goal_col - start_col) < 0)
	{
		c_inc = -1;
	}
	else if((goal_col - start_col) > 0)
	{
		c_inc = 1;
	}
	else
	{
		c_inc = 0;
	}
	//we do both loops
	if ((start_row != goal_row) && (start_col != goal_col))
	{
		for (r = start_row; r != goal_row; r += r_inc)
		{
			for (c = start_col; c != goal_col; c += c_inc)
			{
				if (g_terrain.IsWall(r, c) == true)
				{
					if (modify_var)
					{
						mStraightLineCheck = false;
					}
					return false;
				}
			}
			if (g_terrain.IsWall(r, c) == true)
			{
				if (modify_var)
				{
					mStraightLineCheck = false;
				}
				return false;
			}
		}
	}
	//rows are equal, only check columns
	else if (start_row == goal_row)
	{
		for (c = start_col; c != goal_col; c += c_inc)
		{
			if (g_terrain.IsWall(r, c) == true)
			{
				if (modify_var)
				{
					mStraightLineCheck = false;
				}
				return false;
			}
		}
		if (g_terrain.IsWall(r, c) == true)
		{
			if (modify_var)
			{
				mStraightLineCheck = false;
			}
			return false;
		}
	}
	//columns are equal check only rows
	else if (start_col == goal_col)
	{
		for (r = start_row; r != goal_row; r += r_inc)
		{
			if (g_terrain.IsWall(r, c) == true)
			{
				if (modify_var)
				{
					mStraightLineCheck = false;
				}
				return false;
			}
		}
		if (g_terrain.IsWall(r, c) == true)
		{
			if (modify_var)
			{
				mStraightLineCheck = false;
			}
			return false;
		}
	}
	if (g_terrain.IsWall(r, c) == true)
	{
		if (modify_var)
		{
			mStraightLineCheck = false;
		}
		return false;
	}
	if (modify_var)
	{
		mStraightLineCheck = true;
	}
	return true;
}

void A_Star_Class::Rubberbanding()
{
	if (full_path.size() > 2)
	{
		//take groups of three, eliminate the middle one if necessary
		//three reverse iterators
		std::list<Cell>::iterator left = full_path.begin();
		auto temp = left;
		std::list<Cell>::iterator middle = ++temp;
		temp = middle;
		std::list<Cell>::iterator right = ++temp;
		bool check;
		//move the tri to the left until the begining of the list
		while (right != full_path.end())
		{
			//make a straightline check between left and right
			//bool A_Star_Class::StraightlineCheck(Cell start, Cell goal, bool modify_var)
			check = StraightlineCheck(*left, *right, false);
			//no wall tiles
			if (check)
			{
				//we eliminate the middle cell and move left
				full_path.erase(middle);
				//move middle to right
				middle = right;
				right++;
			}
			//wall tile, no straight line
			else
			{
				left++;
				middle++;
				right++;
			}
		}
	}
}

