#pragma once

#include "Ball.h"
#include "DataLogger.h"

const double VELOCITY_MAX = 15000;	//	mm/s
const int DELAY1 = 22;	//	22ms
const int DELAY2 = 35;	//	35ms

class Machine {

public:

	Machine(DataLogger* logger);

	~Machine();

	const Ball* GetBall() const;

	//	Static

	void Moving(const Point& pos_mach);

	void Aiming(const Point& pos_tar);

	void Shooting();
	
	void Shaking();	//	Noise && Not completed

	void LetsGo(const Point& pos_mach, const Point& pos_tar);

	//	Dynamic

	void Moving_Dynamic(const Point& pos_mach);

	const Point Move_Predicting_Dynamic() const;

	void Aiming_Dynamic(const Point& pos_tar);

	void Slipping_Dynamic(double shaked_time);

	void Shooting_Dynamic();

	void Shaking_Dynamic();

	void LetsGo_Dynamic(const Point& pos_mach, const Point& pos_tar);

private:

	Point position_machine;		//	mm
	Ball* ball;

	double alpha;		//	Radian
	double theta;		//	Radian
	double shoot_velocity;	//	mm/s

	DataLogger* datalogger;

	//	Dynamic
	double MOVE_VELOCITY = 1000;	//	mm/s
	double beta;		//	Radian

	double Get_Move_Velocity(int Flag) const;
};