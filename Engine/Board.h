#pragma once
#include "Graphics.h"
#include "Location.h"
#include "Colors.h"

class Board {
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder();
	static int GetWidth();
	static int GetHeight();
	bool IsInsideBoard(const Location& loc) const;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 35;
	static constexpr int height = 26;
	static const int cellPadding = Graphics::ScreenWidth / 400;
	static const int xPadding = (Graphics::ScreenWidth - dimension * width - cellPadding * width) / 2;
	static const int yPadding = (Graphics::ScreenHeight - dimension * height - cellPadding * height) / 2;
	const Color borderColor;
	Graphics& gfx;
};