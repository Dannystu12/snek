#include "ObstacleManager.h"
#include "Goal.h"

void ObstacleManager::Obstacle::Init(Location loc)
{
	this->loc = loc;
}

void ObstacleManager::Obstacle::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location & ObstacleManager::Obstacle::GetLocation() const
{
	return loc;
}

void ObstacleManager::Obstacle::SetLocation( const Location& l)
{
	loc = l;
}

void ObstacleManager::Draw(Board & brd) const
{
	for (int i = 0; i < nObstacles; i++)
	{
		obstacles[i].Draw(brd);
	}
}

void ObstacleManager::AddObstacle(std::mt19937 & rng, const Board & brd, const Snake & snake, const Goal & goal)
{
	std::uniform_int_distribution<int> xDist(0, Board::GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, Board::GetHeight() - 1);

	Location l;
	do
	{
		l = {xDist(rng), yDist(rng)};
	} while (snake.IsInTile(l) || goal.GetLocation() == l || ObstacleInTile(l));

	
	if (nObstacles < maxObstacles - 1)
	{
		obstacles[nObstacles].SetLocation(l);
		nObstacles++;
	}
}

bool ObstacleManager::ObstacleInTile(const Location & loc) const
{
	for (int i = 0; i < nObstacles; i++)
	{
		if (obstacles[i].GetLocation() == loc)
		{
			return true;
		}
	}
	return false;
}
