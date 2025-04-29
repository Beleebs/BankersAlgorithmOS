#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> getNeed(std::vector<int>);
bool isSafe(std::vector<int>&, std::vector<int>, std::vector<int>);
void adjustAvailable(std::vector<int>&, std::vector<int>);

int main(int argc, char* argv[]) {

	// Processes
	std::vector<int> p0, p1, p2, p3, p4;
	// Available resources
	std::vector<int> available;

	// Number is the variable that holds a number taken from the file
	int number = 0;
	int counter = 0;
	int process = 0;

	// takes the text file for input
	// std::fstream filein(argv[0]);
	// for testing purposes, im gonna just take banker.txt locally
	std::ifstream filein("bankerInfo.txt");
	if (filein.is_open()) {
		std::cout << "Opened file :)" << std::endl;
		
		// takes the integer input
		while (filein >> number) {

			// std::cout << number << "." << counter << " ";

			// This selects which process is being fed numbers
			switch (counter / 6) {
			case 0:
				process = 0;
				break;
			case 1:
				process = 1;
				break;
			case 2:
				process = 2;
				break;
			case 3:
				process = 3;
				break;
			case 4:
				process = 4;
				break;
			}

			// this feeds the numbers in
			if (process == 0) {
				p0.push_back(number);
			}
			else if (process == 1) {
				p1.push_back(number);
			}
			else if (process == 2) {
				p2.push_back(number);
			}
			else if (process == 3) {
				p3.push_back(number);
			}
			// we dont want to pull in the available items at the end
			else if (process == 4 && p4.size() < 6) {
				p4.push_back(number);
			}
			// pull into available vector
			else {
				available.push_back(number);
			}

			counter++;
		}

		// Gets the needs for each process.
		std::vector<int> need0 = getNeed(p0);
		std::vector<int> need1 = getNeed(p1);
		std::vector<int> need2 = getNeed(p2);
		std::vector<int> need3 = getNeed(p3);
		std::vector<int> need4 = getNeed(p4);

		filein.close();
	}
	else {
		std::cout << "SOMETHIG WRONG....." << std::endl;
	}
}

std::vector<int> getNeed(std::vector<int> input) {
	// return variable
	std::vector<int> result;

	// Max - Allocated = Need
	// in each process vector indexes 0-2 are the max, and 3-5 are the allocated.
	result.push_back(input[3] - input[0]);
	result.push_back(input[4] - input[1]);
	result.push_back(input[5] - input[2]);

	return result;
}

bool isSafe(std::vector<int>& avail, std::vector<int> need, std::vector<int> allocation) {
	// avail = [#, #, #]
	// need  = [#, #, #]
	// if need[i] is > avail[i]
	//	return false
	// else adjustAvailable

	for (int i = 0; i < avail.size(); i++) {
		if (need[i] > avail[i]) {
			// not a safe state for the current need
			return false;
		}
	}
	adjustAvailable(avail, allocation);
	return true;
}

void adjustAvailable(std::vector<int>& avail, std::vector<int> allocation) {
	for (int i = 0; i < avail.size(); i++) {
		avail[i] += allocation[i];
	}
}

