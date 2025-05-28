#include "Ball.h"

Ball::Ball() {

}

Ball::Ball(const Point pos) {

	position_ball = pos;

	std::cout << "Building Ball......" << std::endl;
	std::cout << "\t Ball_position: (" << position_ball.x << " mm, " << position_ball.y << " mm, " << position_ball.z << " mm)" << std::endl;
	std::cout << "\t Ball_diameter: " << DIAMETER_BALL << " mm" << std::endl;
}

Ball::~Ball() {

}

const Point Ball::GetBallPos() const {

	return position_ball;
}

int Ball::GetBallDiameter() const {

	return DIAMETER_BALL;
}

void Ball::SetBallPos(const Point new_pos) {

	position_ball = new_pos;

	std::cout << "\t Ball_position: (" << position_ball.x << " mm, " << position_ball.y << " mm, " << position_ball.z << " mm)" << std::endl;
}

void Ball::SetBallVelocity(const Ball::Direction dir, double vel) {
	
	velocity[dir] = vel;

	switch (dir) {

	case Direction::VELOCITY_X:
		std::cout << "\t\t ball_velocity_x: " << velocity[dir] << std::endl;
		break;
	case Direction::VELOCITY_Y:
		std::cout << "\t\t ball_velocity_y: " << velocity[dir] << std::endl;
		break;
	case Direction::VELOCITY_Z:
		std::cout << "\t\t ball_velocity_z: " << velocity[dir] << std::endl;
		break;
	default:
		break;
	}
}

void Ball::BallFlyDown(double x_tar) {

	std::cout << "Ball Flying......" << std::endl;

	double distance_x = x_tar - position_ball.x;

	double t = distance_x / velocity[Direction::VELOCITY_X];

	position_ball.x += t * velocity[Direction::VELOCITY_X];
	position_ball.y += t * velocity[Direction::VELOCITY_Y];
	position_ball.z += t * velocity[Direction::VELOCITY_Z] - 0.5 * G * t * t;

	std::cout << "\t ball_position_x: " << position_ball.x << std::endl;
	std::cout << "\t ball_position_y: " << position_ball.y << std::endl;
	std::cout << "\t ball_position_z: " << position_ball.z << std::endl;

	for (std::map<Direction, double>::iterator it = velocity.begin(); it != velocity.end(); ++it) {
	
		it->second = 0;
	}
}