#pragma once

#include "Ball.h"

const double VELOCITY_MAX = 15000;	//	mm/s
const int DELAY1 = 22;	//	22ms
const int DELAY2 = 35;	//	35ms

class Machine {

public:

	Machine();

	Machine(DataLogger* logger);

	~Machine();

	//	Static

		// tool

	const Point& GetPosition() const;

	double GetAlpha() const;

	double GetTheta() const;

	double GetShootVelocity() const;

	const Ball* GetBall() const;

		//process

	void Moving(const Point& pos_mach);

	void Aiming(const Point& pos_tar);

	void Shooting();
	
	void Shaking();	//	Noise && Not completed

	void LetsGo(const Point& pos_mach, const Point& pos_tar);

	//	Dynamic

		// tool

	double GetMoveVelocity(int Flag) const;

	double GetBeta() const;

		//	process

	void Moving_Dynamic(const Point& pos_mach);

	const Point Move_Predicting_Dynamic() const;

	void Aiming_Dynamic(const Point& pos_tar);

	void Slipping_Dynamic(double shaked_time);

	void Shooting_Dynamic();

	void Shaking_Dynamic();

	void LetsGo_Dynamic(const Point& pos_mach, const Point& pos_tar);

private:

	DataLogger* datalogger;

	//	Static

	Point position_machine;		//	mm
	Ball* ball;

	double alpha;		//	Radian
	double theta;		//	Radian
	double shoot_velocity;	//	mm/s

	//	Dynamic

	double MOVE_VELOCITY = 1000;	//	mm/s
	double beta;		//	Radian
};