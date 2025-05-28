#include "Machine.h"
#include "Basket.h"

//	»·¾³
const double LENGTH_X = 10000;	//	mm
const double LENGTH_Y = 10000;	//	mm
const double HEIGHT = 2000;		//	mm

Point GenerateLaunchPosition();

int main() {
	 
	srand((int)time(NULL));

	Basket basket;
	Machine machine;

	static int LAUNCH_TIMES = 0;
	static int HIT_TIMES = 0;

	//Point pos = { 5500,5500,0 };
	//machine.Moving(pos);

	for (int i = 0; i < 5; i++) {

		//machine.LetsGo(GenerateLaunchPosition(), basket.GetPosBasket());
		machine.LetsGo_Dynamic(GenerateLaunchPosition(), basket.GetPosBasket());

		LAUNCH_TIMES++;

		if (basket.CheckHit(machine.GetBall()))
			HIT_TIMES++;
		std::cout << "*********************************************************************************" << std::endl;
	}

	std::cout << "Hit Chance: " << (double)HIT_TIMES / LAUNCH_TIMES << std::endl;

	/*machine.LetsGo_Dynamic(GenerateLaunchPosition(), basket.GetPosBasket());
	basket.CheckHit(machine.GetBall());*/

	return 0;
}

Point GenerateLaunchPosition() {

	double base_val_x = 0.1 * LENGTH_X;
	double base_val_y = 0.1 * LENGTH_Y;

	double delta_x = rand() % (int)base_val_x - 0.5 * base_val_x;
	double delta_y = rand() % (int)base_val_y - 0.5 * base_val_y;

	Point tar_pos = { 0.5 * LENGTH_X + delta_x,0.5 * LENGTH_Y + delta_y,0 };

	std::cout << "\n*********************************************************************************" << std::endl;
	std::cout << "LAUNCH_POINT: (" << tar_pos.x << " mm, " << tar_pos.y << " mm)" << std::endl;

	return tar_pos;
}