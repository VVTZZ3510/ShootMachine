#pragma once

#include "Ball.h"

extern const double LENGTH_X;
extern const double LENGTH_Y;
extern const double HEIGHT;

extern Ball* ball;

class Basket
{
public:

	Basket();

	~Basket();

	const Point GetPosBasket() const;
	
	bool CheckHit(const Ball* ball) const;

private:

	Point position_basket = { LENGTH_X,LENGTH_Y / 2,HEIGHT };	//mm

	int DIAMETER_BASKET = 264;	//mm
};

