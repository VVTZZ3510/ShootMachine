#include "Machine.h"

Machine::Machine() : Machine(nullptr) {

}

Machine::Machine(DataLogger* logger) : datalogger(logger) {

	std::cout << "Building Machine......" << std::endl;

	position_machine = { 0,0,0 };

	std::cout << "\t Machine_position: (" << position_machine.x << " mm, " << position_machine.y << " mm, " << "0 mm)" << std::endl;

	ball = new Ball(position_machine);

	alpha = 0;
	theta = 0;
	shoot_velocity = 0;

	//	Dynamic
	beta = 0;
}

Machine::~Machine() {

	if(ball!=nullptr)
		delete ball;
}

//	Static

	//	tool

const Point& Machine::GetPosition() const {

	return position_machine;
}

const Ball* Machine::GetBall() const {

	return ball;
}

double Machine::GetAlpha() const {

	return alpha;
}

double Machine::GetTheta() const {

	return theta;
}

double Machine::GetShootVelocity() const {

	return shoot_velocity;
}

	//	process

void Machine::Moving(const Point& pos_mach) {

	std::cout << "Machine Moving......" << std::endl;

	position_machine = pos_mach;
	std::cout << "\t Machine_position: ( " << position_machine.x << " mm, " << position_machine.y << " mm, " << position_machine.z << " mm)" << std::endl;

	ball->SetBallPos(position_machine);

	if (datalogger != nullptr) {

		datalogger->InsertSlot(DataLogger::ShootSlot::Machine_X, position_machine.x);
		datalogger->InsertSlot(DataLogger::ShootSlot::Machine_Y, position_machine.y);
	}
}

void Machine::Aiming(const Point& pos_tar) {

	std::cout << "Machine Aiming......" << std::endl;

	alpha = figure_out_alpha(position_machine, pos_tar);
	std::cout << "\t alpha: " << alpha << std::endl;

	double distance = get_distance_xoy(position_machine, pos_tar);

	double velocity_mini = figure_out_velocity_mini(distance, pos_tar.z);

	shoot_velocity = (VELOCITY_MAX + velocity_mini) / 2;
	std::cout << "\t shoot_velocity: " << shoot_velocity << std::endl;

	theta = figure_out_theta(distance, pos_tar.z, shoot_velocity);
	std::cout << "\t theta: " << theta << std::endl;

	if (datalogger != nullptr) {

		datalogger->InsertSlot(DataLogger::ShootSlot::Alpha_Ideal, alpha);
		datalogger->InsertSlot(DataLogger::ShootSlot::ShootVelocity_Ideal, shoot_velocity);
		datalogger->InsertSlot(DataLogger::ShootSlot::Theta_Ideal, theta);
	}
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
	
	double delta_t = (double)(DELAY1 + DELAY2) / 2 + ((double)(rand() % time_len) - ((double)time_len / 2));
	delta_t *= 1e-03;
	std::cout << "\t\t shaked_time: " << delta_t << std::endl;

	double delta_alpha = generate_gaussian(0.0, 1.0);
	alpha += delta_alpha * delta_t;
	//alpha = alpha;
	std::cout << "\t\t shaked_alpha: " << alpha << std::endl;

	double delta_theta = generate_gaussian(0.0, 0.5);
	theta += delta_theta * delta_t;
	//theta = theta;
	std::cout << "\t\t shaked_theta: " << theta << std::endl;

	double delta_velocity = generate_gaussian(0, (delta_t - (DELAY1 * 1e-03)));
	shoot_velocity = shoot_velocity * (1 + delta_velocity);
	//shoot_velocity = shoot_velocity;
	std::cout << "\t\t shaked_shoot_velocity: " << shoot_velocity << std::endl;

	if (datalogger != nullptr) {

		datalogger->InsertSlot(DataLogger::ShootSlot::Shaked_Time, delta_t);
		datalogger->InsertSlot(DataLogger::ShootSlot::Alpha_Shaked, alpha);
		datalogger->InsertSlot(DataLogger::ShootSlot::Theta_Shaked, theta);
		datalogger->InsertSlot(DataLogger::ShootSlot::ShootVelocity_Shaked, shoot_velocity);
	}
}	//	Noise && Not completed	

void Machine::LetsGo(const Point& pos_mach, const Point& pos_tar) {

	Moving(pos_mach);

	Aiming(pos_tar);

	Shooting();

	ball->BallFlyDown(pos_tar.x);
}


//	Dynamic

	//	tool

double Machine::GetMoveVelocity(int Flag) const {

	switch (Flag) {

	case 0:
		//	move_velocity_x
		//std::cout << "\t\t machine_move_velocity_x: " << MOVE_VELOCITY * sin(beta) << std::endl;
		return MOVE_VELOCITY * sin(beta);

	case 1:
		//	move_velocity_y
		//std::cout << "\t\t machine_move_velocity_y: " << MOVE_VELOCITY * cos(beta) << std::endl;
		return MOVE_VELOCITY * cos(beta);

	default:
		break;
	}

	return 0;
}

double Machine::GetBeta() const {

	return beta;
}

	//	process

void Machine::Moving_Dynamic(const Point& pos_mach) {

	std::cout << "Machine Moving......" << std::endl;

	beta = figure_out_alpha(position_machine, pos_mach);
	std::cout << "\t Machine_move_beta: " << beta << std::endl;

	position_machine = pos_mach;
	std::cout << "\t Machine_position: ( " << position_machine.x << " mm, " << position_machine.y << " mm, " << position_machine.z << " mm)" << std::endl;

	ball->SetBallPos(position_machine);
	//ball->SetBallVelocity((Ball::Direction)0, MOVE_VELOCITY * sin(beta));
	//ball->SetBallVelocity((Ball::Direction)1, MOVE_VELOCITY * cos(beta));

	if (datalogger != nullptr) {

		datalogger->InsertSlot(DataLogger::ShootSlot::Beta, beta);
		datalogger->InsertSlot(DataLogger::ShootSlot::Machine_X, position_machine.x);
		datalogger->InsertSlot(DataLogger::ShootSlot::Machine_Y, position_machine.y);
	}
}

const Point Machine::Move_Predicting_Dynamic() const {

	std::cout << "\t Machine Predicting......" << std::endl;

	Point machine_predict_pos = position_machine;

	double Base_Delay = (double)(DELAY1 + DELAY2) / 2 * 1e-03;	//	ms;

	double move_velocity_x = GetMoveVelocity(0);
	double move_velocity_y = GetMoveVelocity(1);
	std::cout << "\t\t machine_move_velocity_x: " << move_velocity_x << std::endl;
	std::cout << "\t\t machine_move_velocity_y: " << move_velocity_y << std::endl;

	machine_predict_pos.x += Base_Delay * move_velocity_x;
	machine_predict_pos.y += Base_Delay * move_velocity_y;
	std::cout << "\t\t Machine_predict_position: ( " << machine_predict_pos.x << " mm, " << machine_predict_pos.y << " mm, " << machine_predict_pos.z << " mm)" << std::endl;

	if (datalogger != nullptr) {

		datalogger->InsertSlot(DataLogger::ShootSlot::MoveVelocity_X, move_velocity_x);
		datalogger->InsertSlot(DataLogger::ShootSlot::MoveVelocity_Y, move_velocity_y);
	}

	return machine_predict_pos;
}

void Machine::Aiming_Dynamic(const Point& pos_tar) {

	std::cout << "Machine Aiming......" << std::endl;

	Point machine_predict_pos = Move_Predicting_Dynamic();	//	预测位置

	Point vec_move_velocity = vector_subtract_xoy(position_machine, machine_predict_pos);	//	移动速度方向向量
	Point vec_ball_track_xoy = vector_subtract_xoy(machine_predict_pos, pos_tar);	//	球理想轨迹方向向量（xoy）（合成轨迹）
	
	double ideal_distance = get_distance_xoy(machine_predict_pos, pos_tar);
	double ideal_shoot_velocity = (VELOCITY_MAX + figure_out_velocity_mini(ideal_distance, pos_tar.z)) / 2;	//	理想发射速度 (xyz)（合成速度）
	double ideal_theta = figure_out_theta(ideal_distance, pos_tar.z, ideal_shoot_velocity);
	
	double ideal_shoot_velocity_xoy = ideal_shoot_velocity * cos(ideal_theta);	//	xoy上的速度分类（合成速度）
	double shoot_velocity_z = ideal_shoot_velocity * sin(ideal_theta);	//	z方向的速度分量
	//std::cout << "\t shoot_velocity_z: " << shoot_velocity_z << std::endl;

	vector_reshape(vec_move_velocity, MOVE_VELOCITY);
	vector_reshape(vec_ball_track_xoy, ideal_shoot_velocity_xoy);
	
	alpha = figure_out_alpha(vec_move_velocity, vec_ball_track_xoy);
	std::cout << "\t alpha: " << alpha << std::endl;

	double shoot_velocity_xoy = get_distance_xoy(vec_move_velocity, vec_ball_track_xoy);
	//std::cout << "\t shoot_velocity_xoy: " << shoot_velocity_xoy << std::endl;

	shoot_velocity = sqrt(shoot_velocity_xoy * shoot_velocity_xoy + shoot_velocity_z * shoot_velocity_z);
	std::cout << "\t shoot_velocity: " << shoot_velocity << std::endl;
	
	theta = atan(shoot_velocity_z / shoot_velocity_xoy);
	std::cout << "\t theta: " << theta << std::endl;

	if (datalogger != nullptr) {

		datalogger->InsertSlot(DataLogger::ShootSlot::Alpha_Ideal, alpha);
		datalogger->InsertSlot(DataLogger::ShootSlot::ShootVelocity_Ideal, shoot_velocity);
		datalogger->InsertSlot(DataLogger::ShootSlot::Theta_Ideal, ideal_theta);
	}
}

void Machine::Slipping_Dynamic(double shaked_time) {

	std::cout << "\t\t Machine Slipping......" << std::endl;

	//	Dynamic
	std::cout << "\t\t\t Machine_slip_beta: " << beta << std::endl;

	Point machine_slip_pos = position_machine;

	machine_slip_pos.x += GetMoveVelocity(0) * shaked_time;
	machine_slip_pos.y += GetMoveVelocity(1) * shaked_time;

	position_machine = machine_slip_pos;
	std::cout << "\t\t\t Machine_slip_position: ( " << position_machine.x << " mm, " << position_machine.y << " mm, " << position_machine.z << " mm)" << std::endl;

	std::cout << "\t\t";
	ball->SetBallPos(position_machine);

	if (datalogger != nullptr) {

		datalogger->InsertSlot(DataLogger::ShootSlot::Machine_X_Slipped, position_machine.x);
		datalogger->InsertSlot(DataLogger::ShootSlot::Machine_Y_Slipped, position_machine.y);
	}
}

void Machine::Shaking_Dynamic() {

	std::cout << "\t Machine Shaking......" << std::endl;

	int time_len = DELAY2 - DELAY1;

	double delta_t = (double)(DELAY1 + DELAY2) / 2 + ((double)(rand() % time_len) - ((double)time_len / 2));
	delta_t *= 1e-03;
	std::cout << "\t\t shaked_time: " << delta_t << std::endl;

	Slipping_Dynamic(delta_t);
	//Slipping_Dynamic((double)(DELAY1 + DELAY2) / 2 * 1e-03);

	double delta_alpha = generate_gaussian(0.0, 1.0);
	alpha += delta_alpha * delta_t;
	//alpha = alpha;
	std::cout << "\t\t shaked_alpha: " << alpha << std::endl;

	double delta_theta = generate_gaussian(0.0, 0.5);
	theta += delta_theta * delta_t;
	//theta = theta;
	std::cout << "\t\t shaked_theta: " << theta << std::endl;

	double delta_velocity = generate_gaussian(0, (delta_t - (DELAY1 * 1e-03)));
	shoot_velocity = shoot_velocity * (1 + delta_velocity);
	//shoot_velocity = shoot_velocity;
	std::cout << "\t\t shaked_shoot_velocity: " << shoot_velocity << std::endl;

	if (datalogger != nullptr) {

		datalogger->InsertSlot(DataLogger::ShootSlot::Shaked_Time, delta_t);
		datalogger->InsertSlot(DataLogger::ShootSlot::Alpha_Shaked, alpha);
		datalogger->InsertSlot(DataLogger::ShootSlot::Theta_Shaked, theta);
		datalogger->InsertSlot(DataLogger::ShootSlot::ShootVelocity_Shaked, shoot_velocity);
	}
}

void Machine::Shooting_Dynamic() {

	std::cout << "Machine Shooting......" << std::endl;

	//Slipping_Dynamic((double)(DELAY1 + DELAY2) / 2 * 1e-03);
	Shaking_Dynamic();

	double vel_x = shoot_velocity * cos(theta) * sin(alpha) + GetMoveVelocity(0);
	double vel_y = shoot_velocity * cos(theta) * cos(alpha) + GetMoveVelocity(1);
	double vel_z = shoot_velocity * sin(theta);

	std::cout << "\t Machine Pushing......" << std::endl;

	ball->SetBallVelocity((Ball::Direction)0, vel_x);
	ball->SetBallVelocity((Ball::Direction)1, vel_y);
	ball->SetBallVelocity((Ball::Direction)2, vel_z);
}

void Machine::LetsGo_Dynamic(const Point& pos_mach, const Point& pos_tar) {

	Moving_Dynamic(pos_mach);

	Aiming_Dynamic(pos_tar);

	Shooting_Dynamic();

	ball->BallFlyDown(pos_tar.x);
}