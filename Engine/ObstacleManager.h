#pragma once
#include "Location.h"
#include "Colors.h"
#include "Board.h"
#include "Snake.h"
#include <random>

class Goal;

class ObstacleManager
{
private:
	class Obstacle
	{
	public:
		void Init(Location loc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
		void SetLocation(const Location& l);
	private:
		Location loc;
		static constexpr Color c = { 130, 130, 130 };
	};
public:
	void Draw(Board& brd) const;
	void AddObstacle(std::mt19937& rng, const Board& brd, const Snake& snake, const Goal& goal);
	bool ObstacleInTile(const Location& loc) const;
private:
	static constexpr int maxObstacles = 50;
	Obstacle obstacles[maxObstacles];
	int nObstacles = 0;
};
