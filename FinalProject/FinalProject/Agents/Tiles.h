#pragma once
enum TileType
{
	Open,
	PartialCover,
	FullCover,
};
enum TileStatus
{
	Occupied,
	Unoccupied
};
struct Tile
{
	int xpos;
	int ypos;
	TileType t;
	TileStatus s;
};
