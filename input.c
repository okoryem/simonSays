#include "project.h"
#define THRESHOLD 10000

int js;
int tilt;
unsigned char reg = 0x28;
unsigned char data[6];

coord_t initialData = {0, 0, 0};
int16_t initialX, initialY, initialZ;

int checkingVar = -1;

void openInput(void) {
	js = open("/dev/input/event4", O_RDONLY | O_NONBLOCK);
	if (js < 0) {
		perror("Error opening joystick device");
	}
}

void closeInput(void) {
	if (js >= 0) {
		close(js);
		js = -1;
	}
}

void openTilt() {
	tilt = open("/dev/i2c-1", O_RDWR);
	if (tilt < 0) {
		perror("Failed to poen I2C device");
	}

	if (ioctl(tilt, I2C_SLAVE, 0x6A) < 0) {
		perror("Failed to set I2C address");
		close(tilt);
	}

	unsigned char config[] = {0x10, 0x60};
	if (write(tilt, config, 2) != 2) {
		perror("Failed to configure gyroscope");
		close(tilt);
	}
}

void closeTilt(void) {
	if (tilt >= 0) {
		close(tilt);
	}
}

void checkJoyInput(void) {
	struct input_event ev;
	if (read(js, &ev, sizeof(struct input_event)) > 0) {
		if (ev.type == EV_KEY && ev.value == 1) {
			switch (ev.code) {
				case KEY_RIGHT:
					// this is for down
					checkingVar = 7;
					break;
				case KEY_LEFT:
					// this if for up
					checkingVar = 6;
					break;
				case KEY_UP:
					// this is for right
					checkingVar = 4;
					break;
				case KEY_DOWN:
					// this is for left
					checkingVar = 5;
					break;
				case KEY_ENTER:
					checkingVar = 8;
					break;
				default:
					checkingVar = -1;
					break;
			}
		}
	}
}

void getPosition(coord_t *coords) {
	if (write(tilt, &reg, 1) != 1) {
		perror("Failed to write to I2C device");
		return;
	}

	if (read(tilt, data, 6) != 6) {
		perror("Failed to read from I2C device");
		return;
	}

	coords->x = (data[1] << 8) | data[0];
	coords->y = (data[3] << 8) | data[2];
	coords->z = (data[5] << 8) | data[4];
}

int checkTilt(int nextMove) {
	int cnt = 0;

	getPosition(&initialData);
	// printf("tilt: %d\n", initialData.x);
	initialX = initialData.x;
	initialY = initialData.y;
	initialZ = initialData.z;

	//////////
	while (tilt >= 0 && cnt < 2500) {
		printf("%d\n", cnt);
		checkJoyInput();
		getPosition(&initialData);
		int16_t xDifference = initialData.x - initialX;
		int16_t yDifference = initialData.y - initialY;
		// printf("X: %d | Y: %d\n", xDifference, yDifference);
		if (nextMove == 2 && xDifference >= THRESHOLD) {
			return 1;
		} else if (nextMove == 2 && checkingVar != -1) {
			return 0;
		} else if ((xDifference <= -THRESHOLD || yDifference >= THRESHOLD || yDifference <= -THRESHOLD) && nextMove == 2) {
			return 0;
		}


		if (nextMove == 3 && xDifference <= -THRESHOLD) {
			return 1;
		} else if (nextMove == 3 && checkingVar != -1) {
			return 0;
		} else if ((xDifference >= THRESHOLD || yDifference >= THRESHOLD || yDifference <= -THRESHOLD) && nextMove == 3) {
			return 0;
		}


		if (nextMove == 0 && yDifference >= THRESHOLD) {
			return 1;
		} else if (nextMove == 0 && checkingVar != -1) {
			return 0;
		} else if ((xDifference <= -THRESHOLD || xDifference >= THRESHOLD || yDifference <= -THRESHOLD) && nextMove == 0) {
			return 0;
		}


		if (nextMove == 1 && yDifference <= -THRESHOLD) {
			return 1;
		} else if (nextMove == 1 && checkingVar != -1) {
			return 0;
		} else if ((xDifference <= -THRESHOLD || yDifference >= THRESHOLD || xDifference >= THRESHOLD) && nextMove == 1) {
			return 0;
		}
		cnt++;
	}
	return 0;
}

int checkChoice(int nextMove) {
	getPosition(&initialData);

	initialX = initialData.x;
	initialY = initialData.y;
	initialZ = initialData.z;

	int cnt = 0;

	while (cnt < 2500) {
		printf("%d\n", cnt);
		getPosition(&initialData);
		int16_t xDifference = initialData.x - initialX;
		int16_t yDifference = initialData.y - initialY;
		// printf("X: %d | Y: %d\n", xDifference, yDifference);
		checkJoyInput();

		if (checkingVar == nextMove) {
			checkingVar = -1;
			return 1;
		}

		if (xDifference >= THRESHOLD || xDifference <= -THRESHOLD || yDifference >= THRESHOLD || yDifference <= -THRESHOLD) {
			return 0;
		}

		if (nextMove == 4 && checkingVar != -1 && checkingVar != 4) {
			checkingVar = -1;
			return 0;
		}

		if (nextMove == 5 && checkingVar != -1 && checkingVar != 5) {
			checkingVar = -1;
			return 0;
		}

		if (nextMove == 6 && checkingVar != -1 && checkingVar != 6) {
			checkingVar = -1;
			return 0;
		}

		if (nextMove == 7 && checkingVar != -1 && checkingVar != 7) {
			checkingVar = -1;
			return 0;
		}

		if (nextMove == 8 && checkingVar != -1 && checkingVar != 8) {
			checkingVar = -1;
			return 0;
		}

		cnt++;
	}
	return 0;
}

int randNum() {
	return time(NULL) % 9;
}

