#pragma once

//#include <iostream>
#include <map>
#include "utils.h"

class Ball
{

public:

	Ball();

	Ball(const Point pos);

	~Ball();

	const Point GetBallPos() const;
	int GetBallDiameter() const;

	enum class Direction {

		VELOCITY_X = 0,
		VELOCITY_Y,
		VELOCITY_Z
	};

	void SetBallPos(const Point new_pos);

	void SetBallVelocity(const Direction dir, double vel);

	void BallFlyDown(double x_tar);

private:

	Point position_ball = { 0,0,0 };	//	mm

	int DIAMETER_BALL = 264;	//	mm

	std::map<Direction, double> velocity;	//	mm/s^2
};