#include "myGPIO.h"
#include <fstream>
#include <iostream>
#include <unistd.h>  // for delay
#include <time.h>

//const std::string GPIO::ROOTPATH = "/sys/class/gpio";

GPIO::GPIO(int pin) : pinNumber(pin), on(false)
{
	initGPIO(INPUT);
}

GPIO::GPIO(int pin, int dir) : pinNumber(pin), on(false)
{
	initGPIO(dir);
}

GPIO::~GPIO() {
	terminateGPIO();
}

int GPIO::initGPIO(int direction)
{
	if (!on) {
		std::string export_str = "/sys/class/gpio/export";
		std::ofstream exportFile;
		exportFile.open(export_str.c_str());
		if (!exportFile.is_open()) {
			std::cout << "INITIALIZATION FAILED: Unable to init GPIO because file " << export_str << " could not be opened. Pin Number = " << pinNumber << std::endl;
			return -1;
		}
		exportFile << this->pinNumber;
		exportFile.close();
		on = true;
		usleep(1000000);
		setDirection(direction);

		return 0;
	}
	else { // already on
		return -1;
	}
	

}

int GPIO::terminateGPIO()
{
	if (on) {
		std::string unexport_str = "/sys/class/gpio/unexport";
		std::ofstream unexportFile;
		unexportFile.open(unexport_str.c_str());
		if (!unexportFile.is_open()) {
			std::cout << "TERMINATE FAILED: Unable to terminate GPIO because file " << unexport_str << 
					" could not be opened. Pin Number = " << pinNumber << std::endl;
			return -1;
		}
		unexportFile << this->pinNumber;
		unexportFile.close();
		on = false;
		return 0;
	}
	else { // already off
		return -1;
	}
}

int GPIO::setDirection(int dir)
{
	if (dir != INPUT && dir != OUTPUT) {
		std::cout << "Invalid direction ("<<dir<<"). Pin Number " << pinNumber << " direction not set." << std::endl;
		return -1;
	}

	this->direction = dir;
	std::string setdir_str = "/sys/class/gpio/gpio" + std::to_string(pinNumber) + "/direction";
	std::ofstream setdirFile;
	setdirFile.open(setdir_str.c_str());
	if (!setdirFile.is_open()) {
		std::cout << "SET DIRECTION FAILED: Unable to set direction because file " << setdir_str <<
			" could not be opened. Pin Number = " << pinNumber << std::endl;
		return -1;
	}

	if (dir == OUTPUT)
		setdirFile << "out";
	else if (dir == INPUT)
		setdirFile << "in";

	setdirFile.close();
	return 0;
}

int GPIO::setValue(int v)
{
	if (direction == INPUT) return -1;
	if (!on) return -1;
	std::string setval_str = "/sys/class/gpio/gpio" + std::to_string(this->pinNumber) + "/value";
	std::ofstream setvalFile;
	setvalFile.open(setval_str.c_str()); // open value file for gpio
	if (!setvalFile.is_open()) {
		std::cout << "SET VALUE FAILED: Unable to set the value of GPIO " << this->pinNumber << "." << std::endl;
		return -1;
	}

	setvalFile << v;//write value to value file
	setvalFile.close();// close value file

	return 0;
}
