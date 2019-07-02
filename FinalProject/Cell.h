#pragma once
struct Cell
{
	Cell()
	{
		x = -1;
		y = -1;
		mParent = nullptr;
		f_cost = 0.0f;
		g_cost = 0.0f;
	}
	Cell(int X, int Y, Cell* p)
	{
		x = X;
		y = Y;
		mParent = p;
		f_cost = 0.0f;
		g_cost = 0.0f;
	}
	Cell * mParent;
	int x;
	int y;
	float f_cost;
	float g_cost;

	Cell * GetParent()
	{
		return mParent;
	}
	int Getx()const
	{
		return x;
	}
	int Gety()const
	{
		return y;
	}
	float GetFCost()
	{
		return f_cost;
	}
	void SetFCost(float f)
	{
		f_cost = f;
	}
	float GetGCost()
	{
		return g_cost;
	}
	void SetGCost(float f)
	{
		g_cost = f;
	}
	void Setx(int X)
	{
		x = X;
	}
	void Sety(int Y)
	{
		y = Y;
	}
	bool operator<(const Cell & a)const 
	{
		return this->f_cost > a.f_cost;
	}
	bool operator==(const Cell & a)const
	{
		if (Getx() == a.Getx())
		{
			if (Gety() == a.Gety())
			{
				return true;
			}
		}
		return false;
	}
	void SetParent(Cell * p)
	{
		mParent = p;
	}
};
