#pragma once
#include "Cell.h"
#include <stack>
#include <list>	
#include <queue>
#include <vector>

//typedef std::list<D3DXVECTOR3> WaypointList;
//custom compare of two cells that will pick the one with the lowest cost

enum heuristic
{
	H_CHEBYSHEV = 1,
	H_MANHATTAN = 2,
	H_EUCLIDEAN = 3,
	H_OCTILE = 4
};
class A_Star_Class
{
public:
	//constructor
	A_Star_Class();
	A_Star_Class(Cell start, Cell goal);
	//functions to set start and goal nodes
	void SetStart(Cell start);
	void SetGoal(Cell goal);
	void SetStartAndGoal(Cell start, Cell goal);
	bool RunAStar(bool single);
	void SetHeuristicMethod(heuristic h);
	float GetHeuristicWeight();
	void SetHeuristicWeight(float h);
	float CalculateHeuristic(Cell & currentNode);
	Cell GetStart();
	Cell GetGoal();
	Cell & FinalNode;
	Cell * ReturnFinalNode()
	{
		return & FinalNode;
	}
	std::list<Cell> get_neighbors(Cell & current);
	std::list<Cell> get_full_path();
	Cell & POP_cheapest_from_OPEN();
	bool Check_If_Goal(Cell & c);
	void Compute_And_Set_Costs(float & hcost, float & fcost, Cell & c);
	bool FindInList(std::list<Cell> l, Cell CellToFind, Cell & CellToReturn);
	void ConstructPath(Cell & goal);
	void SetFinalNode(Cell c);
	void SetMinMaxCell(int m, int x)
	{
		min = m;
		max = x;
	}
	int min;
	int max;
	bool path_found;
	bool ispathfound()
	{
		return path_found;
	}
	void BeginAstar();
	bool Iteration();
	Cell & GetCurrentAnalyzed()
	{
		return mCurrentCellBeingAnalyzed;
	}
	bool StraightlineCheck(Cell start, Cell goal, bool modify_var);
	bool mStraightLineCheck;
	int debugcount = 0;
	bool StraightLineOptimization(std::list<Cell> list, Cell & return_cell);
	void Rubberbanding();
private:
	Cell mStartCell;
	Cell mGoalCell;
	Cell mCurrentCellBeingAnalyzed;
	float H_weight;
	std::list<Cell> OPEN_LIST;
	std::list<Cell> CLOSED_LIST;
	std::list<Cell> full_path;
	heuristic mCurrent_H_Method;
};