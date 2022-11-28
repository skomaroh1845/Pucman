#include "Coin.h"

Coin::Coin(const T& center, float R, bool up) : center(center), R(R), 
		y0(center.y), y_max(center.y + R / 4), y_min(center.y - R / 4),  move_up(up)
{
	C[0] = circle(center, R, 0.6, 0.7, 0);
	C[1] = circle(center, R * 0.7, 0.5, 0.4, 0);
	setCenter(center);
}

void Coin::print() const
{
	C[0].print();
	C[1].print();
}

void Coin::animate(float speed)
{
	float shift = speed * 0.06 * cos( (center.y - y0)/(y_max - y_min) * 2 );
	
	if (move_up) {
		C[0].moveBy(0, shift);
		C[1].moveBy(0, shift);
		center.y += shift;
		if (center.y > y_max) move_up = false;
	} else {
		C[0].moveBy(0, -shift);
		C[1].moveBy(0, -shift);
		center.y -= shift;
		if (center.y < y_min) move_up = true;
	}
}