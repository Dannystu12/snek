#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx):
	gfx(gfx),
	borderColor( 90, 90, 159 )
{
}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(loc.x * dimension + loc.x * cellPadding + xPadding, loc.y * dimension + loc.y * cellPadding + yPadding, dimension, dimension,c);
}

void Board::DrawBorder()
{
	for (int x = xPadding; x < Graphics::ScreenWidth - xPadding; x++) {
		gfx.PutPixel(x, yPadding, borderColor);
		gfx.PutPixel(x, Graphics::ScreenHeight - yPadding, borderColor);
	}

	for (int y = yPadding; y < Graphics::ScreenHeight - yPadding; y++) {
		gfx.PutPixel(xPadding, y, borderColor);
		gfx.PutPixel(Graphics::ScreenWidth - xPadding, y, borderColor);
	}

}

int Board::GetWidth()
{
	return width;
}

int Board::GetHeight()
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width && 
		loc.y >= 0 && loc.y < height;
}
