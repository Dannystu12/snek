#include "Snake.h"
#include <assert.h>

int Snake::nextBodyColor = 0;

Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & deltaLoc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}

	segments[0].MoveBy(deltaLoc);
}

Location Snake::GetNextHeadLocation(const Location & deltaLoc) const
{
	Location l(segments[0].GetLocation());
	l.Add(deltaLoc);
	return l;
}

void Snake::Grow()
{
	if (nSegments < maxSegments)
	{
		segments[nSegments].InitBody();
		nextBodyColor++;
		if (nextBodyColor >= numBodyColors)
		{
			nextBodyColor = 0;
		}
		nSegments++;
	}
}

void Snake::Draw(Board & brd)
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTileExceptEnd(const Location & tile) const
{
	for (int i = 0; i < nSegments - 1; i++)
	{
		if (segments[i].GetLocation() == tile)
			return true;
	}
	return false;
}

bool Snake::IsInTile(const Location & tile) const
{
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == tile)
			return true;
	}
	return false;
}

void Snake::Segment::InitHead(const Location & loc)
{
	this->loc = loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody()
{
	c = Snake::bodyColors[Snake::nextBodyColor];
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& deltaLoc)
{
	assert(abs(deltaLoc.x) + abs(deltaLoc.y) == 1);
	loc.Add(deltaLoc);
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
