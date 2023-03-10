#pragma config(Sensor, dgtl1,  button3,        sensorTouch)
#pragma config(Sensor, dgtl2,  button2,        sensorTouch)
#pragma config(Sensor, dgtl3,  button1,        sensorTouch)
#pragma config(Sensor, dgtl5,  encoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl10, led3,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, led2,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, led1,           sensorLEDtoVCC)
#pragma config(Motor,  port2,           spinnerB,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           spinnerT,      tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int currentFlr = 1;
bool debounce = false;

void goTo(int flr) {
	int deg = 0;
	SensorValue(encoder) = 0;

	// ON FLOOR 1
	if(flr == 1) {
		if (currentFlr == 1) {
			deg = 0;
		}
	}
	if(flr == 2) {
		if(currentFlr == 1) {
			deg = 360;
		}
	}
	if(flr == 3) {
		if(currentFlr == 1) {
			deg = 720;
		}
	}

	// ON FLOOR 2
	if(flr == 1) {
		if(currentFlr == 2) {
			deg = 350;
		}
	}
	if(flr == 2) {
		if(currentFlr == 2) {
			deg = 0;
		}
	}
	if(flr == 3) {
		if(currentFlr == 2) {
			deg = 360;
		}
	}

	// ON FLOOR 3
	if(flr == 1) {
		if(currentFlr == 3) {
			deg = 710;
		}
	}
	if(flr == 2) {
		if(currentFlr == 3) {
			deg = 350;
		}
	}
	if(flr == 3) {
		if(currentFlr == 3) {
			deg = 0;
		}
	}

	// Choose motor based on the current floor and the desired floor
	string theMotor = "";
	if(currentFlr < flr && debounce == false) {
		debounce = true;
		theMotor = "top";
		SensorValue(encoder) = 0;
		} else {
		debounce = true;
		theMotor = "bottom";
		SensorValue(encoder) = 0;
	}

	// Start chosen motor
	if(theMotor == "top") {
		while(abs(SensorValue(encoder)) < deg) {
			startMotor(spinnerT, -50);
			startMotor(spinnerB, 25);
		}
	}
	if(theMotor == "bottom") {
		while(abs(SensorValue(encoder)) < deg) {
			startMotor(spinnerT, 25);
			startMotor(spinnerB, -50);
		}
	}

	stopMotor(spinnerT);
	stopMotor(spinnerB);
	currentFlr = flr;
	debounce = false;

	// Turn on light
	if(flr == 1) {
		turnLEDOn(led1);
		turnLEDOff(led2);
		turnLEDOff(led3);
	}
	if(flr == 2) {
		turnLEDOff(led1);
		turnLEDOn(led2);
		turnLEDOff(led3);
	}
	if(flr == 3) {
		turnLEDOff(led1);
		turnLEDOff(led2);
		turnLEDOn(led3);
	}
}

void reset() {
	SensorValue(encoder) = 0;
	turnLEDOff(led1);
	turnLEDOff(led2);
	turnLEDOff(led3);
	//startMotor(spinnerT, 25);
	//startMotor(spinnerB, -50);
	//waitUntil(SensorValue(encoder)=0
	//stopMotor(spinnerT);
	//stopMotor(spinnerB);
}

int counter = 0;

task main() {
	reset();
	turnLEDOn(led1);
	while(true) {
		if(SensorValue(button1)==1) {
			goTo(1);
			counter = 0;
		}
		if(SensorValue(button2)==1) {
			goTo(2);
			counter = 0;
		}
		if(SensorValue(button3)==1) {
			goTo(3);
			counter = 0;
		}
		wait(0.5);
		counter = counter + 1;
		if(counter > 20) {
			goTo(1);
		}
	}
}
