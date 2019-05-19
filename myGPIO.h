#pragma once
#include <string>
#define INPUT 0
#define OUTPUT 1

class GPIO
{
private:
	//static const std::string ROOTPATH;
	int pinNumber;
	int direction;
	bool on;

public:
	GPIO(int );
	GPIO(int, int );
	~GPIO();
	int initGPIO(int);
	int terminateGPIO();
	int setDirection(int);
	int setValue(int);

};

