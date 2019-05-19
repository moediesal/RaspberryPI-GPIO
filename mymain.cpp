#include "myGPIO.h"
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

using namespace std;


int main() {
	GPIO gpio1(17, OUTPUT);
	for (int i=0; i<5; i++) {
		gpio1.setValue(1);
		usleep(1000000);
		gpio1.setValue(0);
		usleep(1000000);
	}
	std::cout << "Success!" << std::endl;
}