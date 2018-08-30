#pragma once
#include "Snake.h"
#include "Board.h"
#include <random>

class ObstacleManager;

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snake, const ObstacleManager& om);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake, const ObstacleManager& om );
	void Draw(Board& brd) const;
	const Location& GetLocation() const;
private:
	static constexpr Color c = Colors::Red;
	Location loc;
};