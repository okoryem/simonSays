#include "project.h"

int main(void) {
	int gamePlayLoop = 1;
	int num;
	openDisplay();
	openInput();
	openTilt();

	while (gamePlayLoop == 1) {
		num = randNum();

		if (num <= 3) {
			drawSymbol(num);
			gamePlayLoop = checkCorrect(checkTilt(num));
			clearDisplay();
		} else {
			drawSymbol(num);
			gamePlayLoop = checkCorrect(checkChoice(num));
			clearDisplay();
		}

		sleep(1);
	}

	closeTilt();
	closeInput();
	clearDisplay();
	closeDisplay();
	return 1;
}
