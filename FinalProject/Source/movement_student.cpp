/* Copyright Steve Rabin, 2012. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright Steve Rabin, 2012"
 */

#include <Stdafx.h>

bool Movement::ComputePath( int r, int c, bool newRequest )
{
	m_goal = g_terrain.GetCoordinates( r, c );
	m_movementMode = MOVEMENT_WAYPOINT_LIST;
	auto o = GetMyOwner();
	// project 2: change this flag to true
	bool useAStar = true;
	
	if( useAStar )
	{
		if (!usingPesronalASTAR)
		{
			bool slc;
			///////////////////////////////////////////////////////////////////////////////////////////////////
			//INSERT YOUR A* CODE HERE
			//1. You should probably make your own A* class.
			//2. You will need to make this function remember the current progress if it preemptively exits.
			//3. Return "true" if the path is complete, otherwise "false".
			///////////////////////////////////////////////////////////////////////////////////////////////////
			if (newRequest)
			{
				int curR, curC;
				D3DXVECTOR3 cur = m_owner->GetBody().GetPos();
				g_terrain.GetRowColumn(&cur, &curR, &curC);
				m_waypointList.clear();
				//m_waypointList.push_back(cur);
				//create a start node and set cost to 0 
				curR;
				curC;
				Cell start(curC, curR, nullptr);
				start.SetFCost(0.0f);
				start.SetGCost(0.0f);

				//set goal debug
				//if (g_A_Star.debugcount == 0)
				//{
				//	c = 7;
				//	r = 10;
				//	g_A_Star.debugcount++;
				//}
				//else if (g_A_Star.debugcount == 1)
				//{
				//	c = 16;
				//	r = 30;
				//	g_A_Star.debugcount++;
				//}
				Cell goal(c, r, nullptr);
				g_A_Star.SetGoal(goal);
				g_A_Star.SetStart(start);
				int i = GetHeuristicCalc();
				switch (i)
				{
				case 0:
				{
					g_A_Star.SetHeuristicMethod(H_EUCLIDEAN);

				}
				break;
				case 1:
				{
					g_A_Star.SetHeuristicMethod(H_OCTILE);

				}
				break;
				case 2:
				{
					g_A_Star.SetHeuristicMethod(H_CHEBYSHEV);
				}
				break;
				case 3:
				{
					g_A_Star.SetHeuristicMethod(H_MANHATTAN);

				}

				default:
				{
					g_A_Star.SetHeuristicMethod(H_CHEBYSHEV);

				}
				break;
				}
				g_A_Star.SetHeuristicWeight(GetHeuristicWeight());

				//straigh line check
				if (GetStraightlinePath())
				{
					slc = g_A_Star.StraightlineCheck(start, goal, true);
				}
				g_A_Star.BeginAstar();
			}
			if (GetStraightlinePath())
			{
				if (!g_A_Star.mStraightLineCheck)
				{
					if (m_singleStep == true)
					{
						bool result = g_A_Star.RunAStar(true);
						auto c = g_A_Star.GetCurrentAnalyzed();
						D3DXVECTOR3 position = g_terrain.GetCoordinates(c.Gety(), c.Getx());
						//g_terrain.SetColor(c.Gety(), c.Getx(), DEBUG_COLOR_YELLOW);
						m_waypointList.push_back(position);
						if (g_A_Star.ispathfound())
						{
							if (GetRubberbandPath())
							{
								//HERE
								g_A_Star.Rubberbanding();
							}
							std::list<Cell> & path = g_A_Star.get_full_path();
							Cell c = Cell();
							bool slc_check = g_A_Star.StraightLineOptimization(path, c);
							//create waypoints with new path
							m_waypointList.clear();
							for (std::list<Cell>::iterator it = path.begin(); it != path.end(); it++)
							{

								D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
								g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_YELLOW);
								m_waypointList.push_back(position);
							}
						}
					}
					else
					{
						bool result = g_A_Star.RunAStar(false);
						//get the full path of A_star class
						if (GetRubberbandPath())
						{
							g_A_Star.Rubberbanding();
						}
						std::list<Cell> & path = g_A_Star.get_full_path();

						for (std::list<Cell>::iterator it = path.begin(); it != path.end(); it++)
						{

							D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
							g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_YELLOW);
							m_waypointList.push_back(position);
						}
					}

					return g_A_Star.ispathfound();
				}
				//full on straighline optimization for start and goal
				else
				{
					//push start and goal 
					m_waypointList.clear();
					D3DXVECTOR3 position1 = g_terrain.GetCoordinates(g_A_Star.GetStart().Gety(), g_A_Star.GetStart().Getx());
					D3DXVECTOR3 position2 = g_terrain.GetCoordinates(g_A_Star.GetGoal().Gety(), g_A_Star.GetGoal().Getx());
					m_waypointList.push_back(position1);
					m_waypointList.push_back(position2);
					return true;
				}

			}
			else
			{
				if (m_singleStep == true)
				{
					bool result = g_A_Star.RunAStar(true);
					auto c = g_A_Star.GetCurrentAnalyzed();
					D3DXVECTOR3 position = g_terrain.GetCoordinates(c.Gety(), c.Getx());
					//g_terrain.SetColor(c.Gety(), c.Getx(), DEBUG_COLOR_YELLOW);
					m_waypointList.push_back(position);
					if (g_A_Star.ispathfound())
					{
						if (GetRubberbandPath())
						{
							//HERE
							g_A_Star.Rubberbanding();
						}
						std::list<Cell> & path = g_A_Star.get_full_path();
						Cell c = Cell();
						bool slc_check = g_A_Star.StraightLineOptimization(path, c);
						//create waypoints with new path
						m_waypointList.clear();
						for (std::list<Cell>::iterator it = path.begin(); it != path.end(); it++)
						{

							D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
							g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_YELLOW);
							m_waypointList.push_back(position);
						}
					}
				}
				else
				{
					bool result = g_A_Star.RunAStar(false);
					//get the full path of A_star class
					if (GetRubberbandPath())
					{
						g_A_Star.Rubberbanding();
					}
					std::list<Cell> & path = g_A_Star.get_full_path();

					for (std::list<Cell>::iterator it = path.begin(); it != path.end(); it++)
					{

						D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
						g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_YELLOW);
						m_waypointList.push_back(position);
					}
				}

				return g_A_Star.ispathfound();
			}
		}
		else
		{
			bool slc;
			///////////////////////////////////////////////////////////////////////////////////////////////////
			//INSERT YOUR A* CODE HERE
			//1. You should probably make your own A* class.
			//2. You will need to make this function remember the current progress if it preemptively exits.
			//3. Return "true" if the path is complete, otherwise "false".
			///////////////////////////////////////////////////////////////////////////////////////////////////
			if (newRequest)
			{
				int curR, curC;
				D3DXVECTOR3 cur = m_owner->GetBody().GetPos();
				g_terrain.GetRowColumn(&cur, &curR, &curC);
				m_waypointList.clear();
				//m_waypointList.push_back(cur);
				//create a start node and set cost to 0 
				curR;
				curC;
				Cell start(curC, curR, nullptr);
				start.SetFCost(0.0f);
				start.SetGCost(0.0f);

				//set goal debug
				//if (g_A_Star.debugcount == 0)
				//{
				//	c = 7;
				//	r = 10;
				//	g_A_Star.debugcount++;
				//}
				//else if (g_A_Star.debugcount == 1)
				//{
				//	c = 16;
				//	r = 30;
				//	g_A_Star.debugcount++;
				//}
				Cell goal(c, r, nullptr);
				GetPersonalASTAR()->SetGoal(goal);
				GetPersonalASTAR()->SetStart(start);
				int i = GetHeuristicCalc();
				switch (i)
				{
				case 0:
				{
					GetPersonalASTAR()->SetHeuristicMethod(H_EUCLIDEAN);

				}
				break;
				case 1:
				{
					GetPersonalASTAR()->SetHeuristicMethod(H_OCTILE);

				}
				break;
				case 2:
				{
					GetPersonalASTAR()->SetHeuristicMethod(H_CHEBYSHEV);
				}
				break;
				case 3:
				{
					GetPersonalASTAR()->SetHeuristicMethod(H_MANHATTAN);

				}

				default:
				{
					GetPersonalASTAR()->SetHeuristicMethod(H_CHEBYSHEV);

				}
				break;
				}
				GetPersonalASTAR()->SetHeuristicWeight(GetHeuristicWeight());

				//straigh line check
				if (GetStraightlinePath())
				{
					slc = GetPersonalASTAR()->StraightlineCheck(start, goal, true);
				}
				GetPersonalASTAR()->BeginAstar();
			}
			if (GetStraightlinePath())
			{
				if (!GetPersonalASTAR()->mStraightLineCheck)
				{
					if (m_singleStep == true)
					{
						bool result = GetPersonalASTAR()->RunAStar(true);
						auto c = GetPersonalASTAR()->GetCurrentAnalyzed();
						D3DXVECTOR3 position = g_terrain.GetCoordinates(c.Gety(), c.Getx());
						//g_terrain.SetColor(c.Gety(), c.Getx(), DEBUG_COLOR_YELLOW);
						m_waypointList.push_back(position);
						if (GetPersonalASTAR()->ispathfound())
						{
							if (GetRubberbandPath())
							{
								//HERE
								GetPersonalASTAR()->Rubberbanding();
							}
							std::list<Cell> & path = GetPersonalASTAR()->get_full_path();
							Cell c = Cell();
							bool slc_check = GetPersonalASTAR()->StraightLineOptimization(path, c);
							//create waypoints with new path
							m_waypointList.clear();
							for (std::list<Cell>::iterator it = path.begin(); it != path.end(); it++)
							{

								D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
								g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_YELLOW);
								m_waypointList.push_back(position);
							}
						}
					}
					else
					{
						bool result = GetPersonalASTAR()->RunAStar(false);
						//get the full path of A_star class
						if (GetRubberbandPath())
						{
							GetPersonalASTAR()->Rubberbanding();
						}
						std::list<Cell> & path = GetPersonalASTAR()->get_full_path();

						for (std::list<Cell>::iterator it = path.begin(); it != path.end(); it++)
						{

							D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
							g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_YELLOW);
							m_waypointList.push_back(position);
						}
					}

					return g_A_Star.ispathfound();
				}
				//full on straighline optimization for start and goal
				else
				{
					//push start and goal 
					m_waypointList.clear();
					D3DXVECTOR3 position1 = g_terrain.GetCoordinates(GetPersonalASTAR()->GetStart().Gety(), GetPersonalASTAR()->GetStart().Getx());
					D3DXVECTOR3 position2 = g_terrain.GetCoordinates(GetPersonalASTAR()->GetGoal().Gety(), GetPersonalASTAR()->GetGoal().Getx());
					m_waypointList.push_back(position1);
					m_waypointList.push_back(position2);
					return true;
				}

			}
			else
			{
				if (m_singleStep == true)
				{
					bool result = GetPersonalASTAR()->RunAStar(true);
					auto c = GetPersonalASTAR()->GetCurrentAnalyzed();
					D3DXVECTOR3 position = g_terrain.GetCoordinates(c.Gety(), c.Getx());
					//g_terrain.SetColor(c.Gety(), c.Getx(), DEBUG_COLOR_YELLOW);
					m_waypointList.push_back(position);
					if (GetPersonalASTAR()->ispathfound())
					{
						if (GetRubberbandPath())
						{
							//HERE
							GetPersonalASTAR()->Rubberbanding();
						}
						std::list<Cell> & path = GetPersonalASTAR()->get_full_path();
						Cell c = Cell();
						bool slc_check = GetPersonalASTAR()->StraightLineOptimization(path, c);
						//create waypoints with new path
						m_waypointList.clear();
						for (std::list<Cell>::iterator it = path.begin(); it != path.end(); it++)
						{

							D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
							g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_YELLOW);
							m_waypointList.push_back(position);
						}
					}
				}
				else
				{
					bool result = GetPersonalASTAR()->RunAStar(false);
					//get the full path of A_star class
					if (GetRubberbandPath())
					{
						GetPersonalASTAR()->Rubberbanding();
					}
					std::list<Cell> & path = GetPersonalASTAR()->get_full_path();

					for (std::list<Cell>::iterator it = path.begin(); it != path.end(); it++)
					{

						D3DXVECTOR3 position = g_terrain.GetCoordinates(it->Gety(), it->Getx());
						g_terrain.SetColor(it->Gety(), it->Getx(), DEBUG_COLOR_YELLOW);
						m_waypointList.push_back(position);
					}
				}

				return GetPersonalASTAR()->ispathfound();
			}
		}
		
	}
	else
	{	
		//Randomly meander toward goal (might get stuck at wall)
		int curR, curC;
		D3DXVECTOR3 cur = m_owner->GetBody().GetPos();
		g_terrain.GetRowColumn( &cur, &curR, &curC );

		m_waypointList.clear();
		m_waypointList.push_back( cur );

		int countdown = 100;
		while( curR != r || curC != c )
		{
			if( countdown-- < 0 ) { break; }

			if( curC == c || (curR != r && rand()%2 == 0) )
			{	//Go in row direction
				int last = curR;
				if( curR < r ) { curR++; }
				else { curR--; }

				if( g_terrain.IsWall( curR, curC ) )
				{
					curR = last;
					continue;
				}
			}
			else
			{	//Go in column direction
				int last = curC;
				if( curC < c ) { curC++; }
				else { curC--; }

				if( g_terrain.IsWall( curR, curC ) )
				{
					curC = last;
					continue;
				}
			}

			D3DXVECTOR3 spot = g_terrain.GetCoordinates( curR, curC );
			m_waypointList.push_back( spot );
			g_terrain.SetColor( curR, curC, DEBUG_COLOR_YELLOW );
		}
		return true;
	}
}
