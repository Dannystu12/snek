/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"
#include <algorithm>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	rng(std::random_device()()),
	snake({ 2, 2}),
	om(),
	goal(rng, brd, snake, om)
{
}

int Game::snakeMovePeriod = 20;

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (gameIsOver) return;

	if (!gameHasStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameHasStarted = true;
		}
		return;
	}


	if(wnd.kbd.KeyIsPressed(VK_UP))
	{
		if(lastDeltaLoc.y == 0)
			deltaLoc = { 0, -1 };
	}
	else if(wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (lastDeltaLoc.y == 0)
			deltaLoc = { 0, 1 };
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (lastDeltaLoc.x == 0)
			deltaLoc = { -1, 0 };
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (lastDeltaLoc.x == 0)
			deltaLoc = { 1, 0 };
	}

	snakeMoveCounter++;

	if (snakeMoveCounter >= snakeMovePeriod)
	{
		const Location nextLoc = snake.GetNextHeadLocation(deltaLoc);
		if (!brd.IsInsideBoard(nextLoc) ||
			snake.IsInTileExceptEnd(nextLoc) ||
			om.ObstacleInTile(nextLoc))
		{
			gameIsOver = true;
		}
		else
		{
			bool eating = nextLoc == goal.GetLocation();
			if (eating)
			{
				snake.Grow();
				snakeMovePeriod = std::max(snakeMovePeriod - 1, minMovePeriod);
			}
			lastDeltaLoc = deltaLoc;
			snake.MoveBy(deltaLoc);
			snakeMoveCounter = 0;
			if (eating)
			{
				goal.Respawn(rng, brd, snake, om);
				om.AddObstacle(rng, brd, snake, goal);
			}
		}
	}
}

void Game::ComposeFrame()
{
	if (!gameHasStarted)
	{
		SpriteCodex::DrawTitle(Graphics::ScreenWidth / 2 - SpriteCodex::TitleWidth / 2, Graphics::ScreenHeight / 2 - SpriteCodex::TitleHeight / 2, gfx);
	}
	else
	{
		om.Draw(brd);
		goal.Draw(brd);
		snake.Draw(brd);
		brd.DrawBorder();
		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(Graphics::ScreenWidth / 2 - SpriteCodex::GameOverWidth / 2, Graphics::ScreenHeight / 2 - SpriteCodex::GameOverHeight / 2, gfx);
		}
	}
}
