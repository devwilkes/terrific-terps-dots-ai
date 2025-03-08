#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <utility>
#include <ctime>
#include <chrono>
#include <map>

#include "C:\Users\Brennen\source\repos\IC25074_Project\IC25074_Project\utility.hpp"
#include "C:\Users\Brennen\source\repos\IC25074_Project\IC25074_Project\ParkingLot.hpp"

/*Hierarchy:
* IC25074 <- Tests <- ParkingLot <- TimeBlock <- utility
*/

extern std::array<std::string, 128> permitNames;
void processRow(std::string line);
void loadTestCases();
void runTestCases();

struct Test {
	std::string customer;
	std::string permit;
	std::string season;
	std::string permissions;
	std::string personnelType;
	std::string date;
	std::string time;
	std::string eligibleLots;
};

std::map<std::string, ParkingLot*> defaultParkingLots; 
std::vector<Test> tests;
constexpr bool yesVerbose = true;
constexpr bool noVerbose = false;

std::vector<std::string> testCase(std::string season, std::string permit, std::string personnelType, std::string date, std::string time, bool verbose) { 
	if (verbose) {
		std::cout << "=========================================\n";
	}
	
	if (permit == "") {
		permit = "No Permits";
	}
	std::array<int, 3> deconstructedDate = deconstructDate(date);
	int deconstructedTime = 100 * deconstructTime(time);
	bool dayIsWeekend = isWeekend(deconstructedDate[2], deconstructedDate[0], deconstructedDate[1]);

	std::cout << "Allowed parking spots on " << date << " at " << deconstructedTime << " with Permit " << permit << "\n";

	std::vector<std::string> allowedSpots;

	for (auto it = defaultParkingLots.begin(); it != defaultParkingLots.end(); ++it) {
		bool checkPermitResult = it->second->checkPermits(dayIsWeekend, permit, deconstructedTime, verbose);
		if (checkPermitResult == true) {
			allowedSpots.push_back(it->first);
			if (verbose) {
				std::cout << it->first << "\n";
			}
			
		}
	}

	
	std::cout << "Summary: ";
	for (std::string lot : allowedSpots) {
		std::cout << lot << ", ";
	}
	std::cout << "\n";
	
	return allowedSpots;
}

int main()
{
	std::time_t startTime = std::time(0);
	std::ifstream MyFile("C:/Users/Brennen/source/repos/IC25074_Project/IC25074_Project/data.txt");
	if (!MyFile.is_open()) {
		std::cout << "Not open\n";
		return 1;
	} 

	std::cout << "Opened!\n";
	std::string line;

	// Column names
	getline(MyFile, line);
	// Get row entries
	while (getline(MyFile, line)) {
		processRow(line);
	}

	loadTestCases();
	runTestCases();

	// Manual test cases
	// testCase("Semester", "A", "Faculty/Staff", "11/06/2024", "3:55 PM", yesVerbose);
	//testCase("Semester", "", "Visitor", "09/19/2024", "12:00 PM", yesVerbose);
	// testCase("Semester", "A", "Faculty/Staff", "02/19/2024", "7:35 AM", yesVerbose);
	
	

	//std::cout << "Size of defaultParkingLots: " << defaultParkingLots.size() << "\n";
	std::time_t endTime = std::time(0);
	// For (simple) benchmarking program time
	//std::cout << "Total time: " << endTime - startTime << "\n";
}

void processRow(std::string line) {
	TimeBlock* timeBlock = nullptr;
	int column = 0;
	std::string currentParkingLot = "";
	std::string postedRestriction = "";
	std::string enforcementDays = "";
	int startTime = 0;

	while (line.find(",") != std::string::npos) {
		int commaIndex = line.find(",");
		std::string entry = line.substr(0, commaIndex);
		switch (column) {
			case 0: { // Parking lot
				// If parking lot has not yet been entered, create an element for it
				if (defaultParkingLots.find(entry) == defaultParkingLots.end()) {
					defaultParkingLots[entry] = new ParkingLot(entry);
				}
				currentParkingLot = entry;
				break;
			}
			case 1: { // Posted Restriction
				postedRestriction = entry; 
				break;
			}
			case 2: { // Enforcement Days
				enforcementDays = entry; 
				break;
			}
			case 3: { // Start Time
				startTime = convertTime(entry);
				break;
			}
			case 4: { // End Time
				int endTime = convertTime(entry);
				if (endTime == 0) {
					endTime = 240000;
				}
				timeBlock = new TimeBlock(startTime, endTime, postedRestriction, enforcementDays);
				break;
			}
			case 5: { // Total permits count
				// Do nothing
				break;
			}
			default: { // Parking lot statuses
				int parkingLotIndex = column - 6;
				timeBlock->permits[parkingLotIndex] = std::stoi(entry); 
			}
				
		}

		line = line.substr(commaIndex + 1);
		column++;
	}
	if (timeBlock == nullptr) {
		return;
	}

	defaultParkingLots[currentParkingLot]->timeBlocks.push_back(*timeBlock);
	delete timeBlock;
}

void loadTestCases() {
	std::ifstream MyFile("C:/Users/Brennen/source/repos/IC25074_Project/IC25074_Project/InfoChallenge_CustomerCases.csv");
	if (!MyFile.is_open()) {
		std::cout << "Could not open test cases file\n";
	}

	std::cout << "Test cases file opened!\n";
	std::string line;

	// Get rid of columns
	getline(MyFile, line);

	while (getline(MyFile, line)) {
		Test test;
		test.customer = line.substr(0, line.find(","));
		line = line.substr(line.find(",") + 1);
		test.permit = line.substr(0, line.find(","));
		line = line.substr(line.find(",") + 1);
		test.season = line.substr(0, line.find(","));
		line = line.substr(line.find(",") + 1);
		test.permissions = line.substr(0, line.find(","));
		line = line.substr(line.find(",") + 1);
		test.personnelType = line.substr(0, line.find(","));
		line = line.substr(line.find(",") + 1);
		test.date = line.substr(0, line.find(","));
		line = line.substr(line.find(",") + 1);
		test.time = line.substr(0, line.find(","));
		line = line.substr(line.find(",") + 1);
		test.eligibleLots = line;
		// Create copy of test and put it in vector
		tests.push_back(test); 
	}

}

void runTestCases() {
	int allFalsePositives = 0;
	int allEligibleCounts = 0;
	int allEligibleLotsFound = 0;

	for (Test test : tests) {
		int falsePositiveCount = 0;
		int totalEligibleCounts = 0;
		int eligibleLotsFound = 0;
		std::cout << test.customer << ": \n";
		std::vector<std::string> parkingLots = testCase(test.season, test.permissions, test.personnelType, test.date, test.time, noVerbose);
		for (std::string lot : parkingLots) {
			// If a lot is a false positive
			if (test.eligibleLots.find(lot) == std::string::npos) {
				falsePositiveCount++;
			}
		}
		std::vector<std::string> eligibleLotsVector = lineToVector(test.eligibleLots);
		for (std::string expectedLot : eligibleLotsVector) {
			totalEligibleCounts++;
			for (std::string lotFound : parkingLots) {
				if (expectedLot == lotFound) {
					eligibleLotsFound++;
				}
			}
		}
		std::cout << "False positives: " << falsePositiveCount << "\n";
		std::cout << "Total eligible counts: " << totalEligibleCounts << "\n";
		std::cout << "Eligible lots found: " << eligibleLotsFound << "\n";
		std::cout << "\n";

		allFalsePositives += falsePositiveCount;
		allEligibleCounts += totalEligibleCounts;
		allEligibleLotsFound += eligibleLotsFound;
	}
	std::cout << "Cumulative summary: ";
	std::cout << "All false positives we produced: " << allFalsePositives << "\n";
	std::cout << "Total eligible lots count (Parking lots we should have found): " << allEligibleCounts << "\n";
	std::cout << "Total eligible lots we found: " << allEligibleLotsFound << "\n";

}