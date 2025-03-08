#ifndef PARKINGLOT_HPP
#define PARKINGLOT_HPP

#include <string>
#include <array>
#include <iostream>
#include <vector>

#include "C:\Users\Brennen\source\repos\IC25074_Project\IC25074_Project\utility.hpp"

extern std::array<std::string, 128> permitNames;

class TimeBlock {
public:
	TimeBlock(int startTime, int endTime, std::string postedRestriction, std::string enforcementDays);
	bool checkTime(bool dateIsWeekend, int time, bool verbose);
	bool checkBounds(int time);

	int startTime;
	int endTime;
	std::string enforcementDays;
	std::string postedRestriction;
	std::array<bool, 128> permits;
};

class ParkingLot {
public:
	ParkingLot(std::string name);

	bool checkPermits(bool isWeekend, std::string permit, int time, bool verbose);

	std::string name;
	std::vector<TimeBlock> timeBlocks;
	std::string enforcementDays;
};

#endif