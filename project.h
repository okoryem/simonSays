#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
//#include "sense.h"
#include <linux/i2c-dev.h>
#include <time.h>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>

typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
} coord_t;

void openDisplay(void);

void countDown(void);

void closeDisplay(void);

void clearDisplay(void);

void drawSymbol(int nextMove);

int checkChoice(int nextMove);

int checkTilt(int nextMove);

int checkCorrect(int isCorrect);

void openTilt(void);

void openInput(void);

void closeTilt(void);

void closeInput(void);

void checkJoyInput(void);

void interrupt_handler(int sig);

void handler(unsigned int code);

int randNum(void);

void getPosition(coord_t *coords);
/*
typedef struct {
        int16_t x;
        int16_t y;
        int16_t z;
} coord_t;
*/
