#include "Basket.h"

Basket::Basket(DataLogger* logger) {

	std::cout << "Building Basket......" << std::endl;
	std::cout << "\t Basket_position: (" << position_basket.x << " mm, " << position_basket.y << " mm, " << position_basket.z << " mm)" << std::endl;
	std::cout << "\t Basket_diameter: " << DIAMETER_BASKET << " mm" << std::endl;

	datalogger = logger;
}

Basket::~Basket() {

}

const Point& Basket::GetPosBasket() const {

	return position_basket;
}

bool Basket::CheckHit(const Ball* ball) const {

	double distance = get_distance(position_basket, ball->GetBallPos());

	bool isHit = false;

	//if (distance <= (double)(ball->GetBallDiameter() / 2 + DIAMETER_BASKET / 2))
	if (distance <= (double)(ball->GetBallDiameter() / 2))
		isHit = true;
	
	std::cout << "Basket Checking......" << std::endl;
	std::cout << "\t isHit: " << isHit << std::endl;

	if (datalogger != nullptr) {

		if (isHit)
			datalogger->InsertSlot(DataLogger::ShootSlot::IsHit, 1);
		else
			datalogger->InsertSlot(DataLogger::ShootSlot::IsHit, 0);
	}

	return isHit;
}

