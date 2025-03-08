#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <array>
#include <ctime>
#include <vector>

bool isWeekend(int year, int month, int day);

/* Converts a time's string representation to an int (Version 1)
* First two decimals -> hour, next two decimals -> min, last two -> seconds
* 14:00:00 -> 140000
* Used when loading the database with information
*/
int convertTime(std::string entry);

/* Converts a time's string representation to an int (Version 2)
* First two decimals -> hour, next two decimals -> min, last two -> seconds
* 3:55 pm -> 155500
* Used when taking user input/test cases
*/
int deconstructTime(std::string time);


/* Converts a date from mm/dd/yy format to an array {month day year}
*/
std::array<int, 3> deconstructDate(std::string original);


/* Converts "Lot 1b; Lot 1c; Lot 1d; Lot 1e; Lot 1f" to
*			{Lot 1b, Lot 1c, Lot 1d, Lot 1e, Lot 1f}
*/
std::vector<std::string> lineToVector(std::string line);

#endif