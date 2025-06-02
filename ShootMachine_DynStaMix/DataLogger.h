#pragma once

#include <string>
#include <fstream>
#include <map>

class DataLogger {

public:

	DataLogger(std::string& filename, bool sport_status);
	
	~DataLogger();

	enum class ShootSlot {

		Machine_X = 0,
		Machine_Y,
		Alpha_Ideal,
		Theta_Ideal,
		ShootVelocity_Ideal,
		Shaked_Time,
		Alpha_Shaked,
		Theta_Shaked,
		ShootVelocity_Shaked,
		IsHit,
		Beta,
		MoveVelocity_X,
		MoveVelocity_Y,
		Machine_X_Slipped,
		Machine_Y_Slipped
	};

	void InsertSlot(ShootSlot slot, double vel);

	void LogData();

private:

	std::ofstream logFile;

	std::map<ShootSlot, double> data;
};

