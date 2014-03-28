/*
 ============================================================================
 Name        : PiMotor.cpp
 Author      : David O'Mahony
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C++,
 ============================================================================
 */

#include <iostream>
#include <wiringPi.h>
#include <ncurses/ncurses.h>

using namespace std;

int main(void) {

	int in1 = 0;
	int in2 = 7;

	wiringPiSetup();
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(1, PWM_OUTPUT);

	int speed = 10;
	bool e1 = false;
	bool e2 = false;

	initscr();
	clear();
	cbreak();
	noecho();

	printw("Stopped: %i", speed);
	bool done = false;
	while (!done) {

		int c;

		c = getch();

		move(0,0);
		clear();
		switch (c) {
		case 'u':
			speed += 50;
			pwmWrite(1, speed);
			printw("Speed: %i", speed);
			break;
		case 'd':
			speed -= 50;
			pwmWrite(1, speed);
			printw("Speed: %i", speed);
			break;
		case '0':
			e1 = false;
			e2 = false;
			digitalWrite(in1, e1);
			digitalWrite(in2, e2);
			printw("Stop (%i)", speed);
			break;
		case '1':
			e1 = true;
			e2 = false;
			digitalWrite(in1, e1);
			digitalWrite(in2, e2);
			printw("Start (%i)", speed);
			break;
		case 'r':
			e1 = !e1;
			e2 = !e2;
			printw("Reverse");
			digitalWrite(in1, e1);
			digitalWrite(in2, e2);
			break;
		case 'q':
			pwmWrite(1, 0);
			digitalWrite(in1, false);
			digitalWrite(in2, false);
			endwin();
			done = true;
		}

	}

}
