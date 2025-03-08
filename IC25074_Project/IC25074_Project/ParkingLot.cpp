#include "C:\Users\Brennen\source\repos\IC25074_Project\IC25074_Project\ParkingLot.hpp"


TimeBlock::TimeBlock(int startTime, int endTime, std::string postedRestriction, std::string enforcementDays) {
	this->startTime = startTime;
	this->endTime = endTime;
	permits = {};
	this->postedRestriction = postedRestriction;
	this->enforcementDays = enforcementDays;
}

bool TimeBlock::checkTime(bool dateIsWeekend, int time, bool verbose) {
	if (dateIsWeekend) {
		if (enforcementDays == "Weekdays") {
			// Free parking on Saturdays and Sundays
			if (this->postedRestriction == "Unrestricted after 4PM") {
				if (time < 700 || time > 1600) {
					return true;
				}
			}
		} else {
			return checkBounds(time);
		}
	} else {
		// If date is a weekday
		if (enforcementDays == "Weekends") {
			if (this->postedRestriction == "Unrestricted after 4PM") {
				if (time > 160000) {
					return true;
				}
			} else if (this->postedRestriction == "Special Restrictions") {
				return false;
			}
		} else {
			return checkBounds(time);
		}
	}
	if (verbose) {
		std::cout << "Case not caught! \n";
	}
	return false;
}

bool TimeBlock::checkBounds(int time) {
	return startTime <= time && endTime >= time;
}


ParkingLot::ParkingLot(std::string name) {
	this->name = name;
	timeBlocks = {};
	enforcementDays = "";
}

bool ParkingLot::checkPermits(bool isWeekend, std::string permit, int time, bool verbose) {
	if (verbose) {
		std::cout << "		Parking lot " << this->name << " timeBlocks num: " << timeBlocks.size() << "\n";
	}
	
	for (TimeBlock timeBlock : timeBlocks) {
		for (int i = 0; i < 128; i++) {
			if (timeBlock.permits[i] == true && permitNames[i] == permit) {
				bool checkTimeResult = timeBlock.checkTime(isWeekend, time, verbose);
				if (verbose) {
					std::cout << "		Start: " << timeBlock.startTime << "; End: " << timeBlock.endTime << "; Result: " << checkTimeResult << "\n";
				}
				
				if (checkTimeResult) {
					return true;
				}
			}
		}
	}
	return false;
}