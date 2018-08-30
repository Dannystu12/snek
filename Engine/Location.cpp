#include "Location.h"

bool Location::operator==(const Location & rhs) const
{
	return x == rhs.x && y == rhs.y;
}
