#include "C:\Users\Brennen\source\repos\IC25074_Project\IC25074_Project\utility.hpp"

std::array<std::string, 128> permitNames = { "17FAE", "18-19FAE", "19-20FAE", "4H", "A", "AA", "AE", "After Hours", "All Campus", "All Permits", "Alumni", "B", "BB", "Breaksgiving", "Bundle Pack-FS", "Bundle Pack-Student", "Bus Bundle Pack", "C", "Campus Meter", "Carpool", "CC", "Courier", "Daily Service Permit (Paper)", "DD", "E", "EE", "EMBA", "Emeritus", "ER", "Everyone", "F", "Faculty Staff Green Permit", "FAE", "FF", "FS Summer", "G", "Gate Card", "GG", "Golden ID", "Green Permit-Student", "H", "HC", "HH", "HP", "II", "J", "JJ", "K", "KK", "L", "LL", "Lot 1", "Lot 10", "Lot 11 Commuter", "Lot 15", "Lot 16", "Lot 19", "Lot 2", "Lot 3", "Lot 3 Commuter", "Lot 4", "Lot 6 Commuter", "Lot 6 Resident", "Lot 8", "Lot 9", "Lot V - Anacostia", "Lot V - Artemesia/Cypress", "M", "MC", "MD", "Medical-FS", "Medical-Student", "Micromobility", "MM", "Motorcycle", "N", "NN", "No Permits", "O", "OO", "Overnight Storage-Lot 11", "Overnight Storage-Lot 16", "Overnight Storage-Lot 17", "Overnight Storage-Lot 19", "P", "Paper Service", "PH", "PP", "Q", "QQ", "Quarantine", "R", "RR", "S", "SA", "Scooter/MC", "SDStar", "Service Permit", "Short Term Parking", "SLL", "SS", "Stadium Drive Garage", "Student Lot B", "Student Lot U", "Student Lot UU", "Student Lot XX", "Student TV", "Summer Commuter", "Summer Resident", "Surface Lot", "T", "Time and Materials", "TMP", "TT", "TV", "U", "UU", "V", "Visitor After Hours", "VM", "W", "WW", "X", "XX", "Y", "YC", "YY", "Z" };

bool isWeekend(int year, int month, int day) {
	std::tm timeStruct = {};
	timeStruct.tm_year = year - 1900; // Years since 1900
	timeStruct.tm_mon = month - 1;    // Months are 0-based
	timeStruct.tm_mday = day;         // Day of the month

	// Normalize the struct and compute the weekday
	std::mktime(&timeStruct);

	int weekday = timeStruct.tm_wday; // 0 = Sunday, 6 = Saturday

	return (weekday == 0 || weekday == 6); // True if Saturday or Sunday
}

int convertTime(std::string entry) {
	std::string hourTerm = entry.substr(0, entry.find(":"));
	entry = entry.substr(entry.find(":") + 1);
	std::string minuteTerm = entry.substr(0, entry.find(":"));
	entry = entry.substr(entry.find(":") + 1);
	std::string secondsTerm = entry;
	std::string newTime = hourTerm + minuteTerm + secondsTerm;
	int newTimeInt = std::stoi(newTime);
	return newTimeInt;
}

int deconstructTime(std::string time) {
	std::string firstHalf = time.substr(0, time.find(":"));
	std::string secondHalf = time.substr(time.find(":") + 1, 2);
	if (time.find("AM") != std::string::npos) {
		return std::stoi(firstHalf + secondHalf);
	}
	// if PM
	return 1200 + std::stoi(firstHalf + secondHalf);
}

std::array<int, 3> deconstructDate(std::string original) {
	int month = std::stoi(original.substr(0, original.find("/")));
	original = original.substr(original.find("/") + 1);
	int day = std::stoi(original.substr(0, original.find("/")));
	original = original.substr(original.find("/") + 1);
	int year = std::stoi(original);
	return { month, day, year };
}

std::vector<std::string> lineToVector(std::string line) {
	std::vector<std::string> lots;
	while (line.find(";") != std::string::npos) {
		lots.push_back(line.substr(0, line.find(";")));
		line = line.substr(line.find(";") + 1);
	}
	lots.push_back(line);
	return lots;
}