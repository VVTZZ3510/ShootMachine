#include "Machine.h"

Machine::Machine(DataLogger* logger) {

	std::cout << "Building Machine......" << std::endl;

	position_machine = { 0,0,0 };

	std::cout << "\t Machine_position: (" << position_machine.x << " mm, " << position_machine.y << " mm, " << "0 mm)" << std::endl;

	ball = new Ball(position_machine);

	alpha = 0;
	theta = 0;
	shoot_velocity = 0;

	datalogger = logger;
}

Machine::~Machine() {

	delete ball;
}

const Ball* Machine::GetBall() const {

	return ball;
}


//	Static

void Machine::Moving(const Point& pos_mach) {

	std::cout << "Machine Moving......" << std::endl;

	position_machine = pos_mach;
	datalogger->InsertSlot(DataLogger::ShootSlot::Machine_X, position_machine.x);
	datalogger->InsertSlot(DataLogger::ShootSlot::Machine_Y, position_machine.y);
	std::cout << "\t Machine_position: ( " << position_machine.x << " mm, " << position_machine.y << " mm, " << position_machine.z << " mm)" << std::endl;

	ball->SetBallPos(position_machine);
}

void Machine::Aiming(const Point& pos_tar) {

	std::cout << "Machine Aiming......" << std::endl;

	alpha = figure_out_alpha(position_machine, pos_tar);
	datalogger->InsertSlot(DataLogger::ShootSlot::Alpha_Ideal, alpha);
	std::cout << "\t alpha: " << alpha << std::endl;

	double distance = get_distance_xoy(position_machine, pos_tar);

	double velocity_mini = figure_out_velocity_mini(distance, pos_tar.z);

	shoot_velocity = (VELOCITY_MAX + velocity_mini) / 2;
	datalogger->InsertSlot(DataLogger::ShootSlot::ShootVelocity_Ideal, shoot_velocity);
	std::cout << "\t shoot_velocity: " << shoot_velocity << std::endl;

	theta = figure_out_theta(distance, pos_tar.z, shoot_velocity);
	datalogger->InsertSlot(DataLogger::ShootSlot::Theta_Ideal, theta);
	std::cout << "\t theta: " << theta << std::endl;
}

void Machine::Shooting() {

	std::cout << "Machine Shooting......" << std::endl;

	Shaking();

	double vel_x = shoot_velocity * cos(theta) * sin(alpha);
	double vel_y = shoot_velocity * cos(theta) * cos(alpha);
	double vel_z = shoot_velocity * sin(theta);

	std::cout << "\t Machine Pushing......" << std::endl;

	ball->SetBallVelocity((Ball::Direction)0, vel_x);
	ball->SetBallVelocity((Ball::Direction)1, vel_y);
	ball->SetBallVelocity((Ball::Direction)2, vel_z);


}

void Machine::Shaking() {

	std::cout << "\t Machine Shaking......" << std::endl;

	int time_len = DELAY2 - DELAY1;
	
	double delta_t = (double)(DELAY1 + DELAY2) / 2 + ((double)(rand() % time_len) - (double)(time_len / 2));
	delta_t *= 1e-03;
	datalogger->InsertSlot(DataLogger::ShootSlot::Shaked_Time, delta_t);
	std::cout << "\t\t shaked_time: " << delta_t << std::endl;

	double delta_alpha = generate_gaussian(0.0, 1.0);
	alpha += delta_alpha * delta_t;
	//alpha = alpha;
	datalogger->InsertSlot(DataLogger::ShootSlot::Alpha_Shaked, alpha);
	std::cout << "\t\t shaked_alpha: " << alpha << std::endl;

	double delta_theta = generate_gaussian(0.0, 0.5);
	theta += delta_theta * delta_t;
	//theta = theta;
	datalogger->InsertSlot(DataLogger::ShootSlot::Theta_Shaked, theta);
	std::cout << "\t\t shaked_theta: " << theta << std::endl;

	double delta_velocity = generate_gaussian(0, (delta_t - (DELAY1 * 1e-03)));
	shoot_velocity = shoot_velocity * (1 + delta_velocity);
	//shoot_velocity = shoot_velocity;
	datalogger->InsertSlot(DataLogger::ShootSlot::ShootVelocity_Shaked, shoot_velocity);
	std::cout << "\t\t shaked_shoot_velocity: " << shoot_velocity << std::endl;
}	//	Noise && Not completed	

void Machine::LetsGo(const Point& pos_mach, const Point& pos_tar) {

	Moving(pos_mach);

	Aiming(pos_tar);

	Shooting();

	ball->BallFlyDown(pos_tar.x);
}