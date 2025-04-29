#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> getNeed(std::vector<int>);
bool isSafe(std::vector<int>&, std::vector<int>, std::vector<int>);
void adjustAvailable(std::vector<int>&, std::vector<int>);
bool checkStates(std::vector<bool>);

int main(int argc, char* argv[]) {

	// Processes
	std::vector<int> p0, p1, p2, p3, p4;
	// Available resources
	std::vector<int> available;
	// Safe sequence
	std::vector<int> safeSequence;

	// Number is the variable that holds a number taken from the file
	int number = 0;
	int counter = 0;
	int process = 0;

	// takes the text file for input
	// std::fstream filein(argv[0]);
	// for testing purposes, im gonna just take banker.txt locally
	std::ifstream filein(argv[1]);
	if (filein.is_open()) {

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

		// contains the safe states
		std::vector<bool> states = { false, false, false, false, false };

		// Determines safe state sequence
		// goes 5 times, max number of iterations possible with 5 processes
		for (int i = 0; i < 10; i++) {
			// checks for if the process is able to be checked for safe state
			// if it already is (meaning states[x] == true), skip
			// P0
			if (states[0] == false) {
				// checks if safe
				if (isSafe(available, need0, p0)) {
					// pushes true for the process
					// adds the process number to the safe sequence
					states[0] = true;
					safeSequence.push_back(0);
				}
				else
					states[0] = false;
			}
			// P1
			if (states[1] == false) {
				if (isSafe(available, need1, p1)) {
					states[1] = true;
					safeSequence.push_back(1);
				}
				else
					states[1] = false;
			}
			// P2
			if (states[2] == false) {
				if (isSafe(available, need2, p2)) {
					states[2] = true;
					safeSequence.push_back(2);
				}
				else
					states[2] = false;
			}
			// P3
			if (states[3] == false) {
				if (isSafe(available, need3, p3)) {
					states[3] = true;
					safeSequence.push_back(3);
				}
				else
					states[3] = false;
			}
			// P4
			if (states[4] == false) {
				if (isSafe(available, need4, p4)) {
					states[4] = true;
					safeSequence.push_back(4);
				}
				else
					states[4] = false;
			}
			if (checkStates(states)) {
				break;
			}
		}

		if (!checkStates(states)) {
			std::cout << "The system is not in a safe state." << std::endl;
		}
		else {
			std::cout << "The system is in a safe state!" << std::endl;
			std::cout << "The safe state is: ";
			// loop for outputting safe state
			for (int i = 0; i < safeSequence.size(); i++) {
				std::cout << safeSequence[i] << " ";
			}
            std::cout << std::endl;
		}

		filein.close();
	}
	else {
		std::cout << "SOMETHIG WRONG....." << std::endl;
	}
}

// returns the need for a process
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

// Checks to see if the available resources are able to provide for the need
// if it is, send the available resources to adjustAvailable() with allocated resources
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

// Adjusts the amount available based on allocated amount
void adjustAvailable(std::vector<int>& avail, std::vector<int> allocation) {
	for (int i = 0; i < avail.size(); i++) {
		avail[i] += allocation[i];
	}
}

// checks to see if all the states are valid for a state sequence
bool checkStates(std::vector<bool> states) {
	for (int i = 0; i < states.size(); i++) {
		if (states[i] == false)
			return false;
	}
	return true;
}

