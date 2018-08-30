#pragma once

class Location {
public:
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}
	bool operator==(const Location& rhs) const;
	int x;
	int y;
};