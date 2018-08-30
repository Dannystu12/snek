#include "Goal.h"
#include "ObstacleManager.h"
#include <random>

Goal::Goal(std::mt19937 & rng, const Board & brd, const Snake & snake, const ObstacleManager& om)
{
	Respawn(rng, brd, snake, om);
}

void Goal::Respawn(std::mt19937 & rng, const Board & brd, const Snake & snake, const ObstacleManager& om)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() -1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);
	Location l = { xDist(rng), yDist(rng) };
	while(snake.IsInTile(l) || om.ObstacleInTile(l))
	{
		l = { xDist(rng), yDist(rng) };
	}
	loc = l;
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location & Goal::GetLocation() const
{
	return loc;
}
