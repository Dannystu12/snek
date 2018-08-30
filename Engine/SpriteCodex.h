#pragma once

#include "Graphics.h"

class SpriteCodex
{
public:
	static constexpr int GameOverWidth = 84;
	static constexpr int GameOverHeight = 64;
	static constexpr int TitleWidth = 220;
	static constexpr int TitleHeight = 150;
	static void DrawGameOver( int x,int y,Graphics& gfx );
	static void DrawTitle( int x,int y,Graphics& gfx );
};