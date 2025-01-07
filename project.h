#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sense.h"
#include <time.h>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>

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

void checkJoyInput(void (*callback)(unsigned int code), int delay);

void interrupt_handler(int sig);

void handler(unsigned int code);

int randNum(void);

void getPosition(coord_t coords);
