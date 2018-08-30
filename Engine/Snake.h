#pragma once
#include "Board.h"


class Snake 
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody();
		void Follow(const Segment& next);
		void MoveBy(const Location& deltaLoc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& deltaLoc);
	Location GetNextHeadLocation(const Location& deltaLoc) const;
	void Grow();
	void Draw(Board& brd);
	bool IsInTileExceptEnd(const Location& tile) const;
	bool IsInTile(const Location& tile) const;
private:
	static constexpr Color headColor = {169, 167, 6};
	static constexpr Color bodyColors[4] = { {0, 97, 18}, {0, 133, 39}, {0,167,40}, { 0, 133, 39 } };
	static constexpr int numBodyColors = 4;
	static int nextBodyColor;
	static constexpr int maxSegments = 100;
	Segment segments[maxSegments];
	int nSegments = 1;
};