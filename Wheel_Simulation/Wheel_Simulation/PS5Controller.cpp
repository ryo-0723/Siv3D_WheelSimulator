#include "stdafx.h"
#include "PS5Controller.h"

void PS5Controller::Update(size_t playerIndex) {
	if (playerIndex == 0) {
		if (const auto gamepad = Gamepad(playerIndex)) {
			/*ps5だったらGamepad(0)*/
			/*ps4だったらGamepad(1)*/
			//const auto& info = gamepad.getInfo();
			leftAxis.x = gamepad.axes.at(0) * 255.00;
			leftAxis.y = -gamepad.axes.at(1) * 255.00;
			rightAxis.x = gamepad.axes.at(2) * 255.00;
			/*ps5だったらat(2)*/
			/*ps4だったらat(3)*/
		}
	}
	else if (playerIndex == 1) {
		if (const auto gamepad = Gamepad(playerIndex)) {
			leftAxis.x = gamepad.axes.at(0) * 255.00;
			leftAxis.y = -gamepad.axes.at(1) * 255.00;
			rightAxis.x = gamepad.axes.at(3) * 255.00;
		}
	}

	if (leftAxis.x > cutValue) {
		leftAxis.x = map(leftAxis.x, cutValue, 255, 0, 255);
	}else if (leftAxis.x < -cutValue) {
		leftAxis.x = map(leftAxis.x, -cutValue, -255, 0, -255);
	}
	else {
		leftAxis.x = 0;
	}

	if (leftAxis.y > cutValue) {
		leftAxis.y = map(leftAxis.y, cutValue, 255, 0, 255);
	}
	else if (leftAxis.y < -cutValue) {
		leftAxis.y = map(leftAxis.y, -cutValue, -255, 0, -255);
	}
	else {
		leftAxis.y = 0;
	}


	if (rightAxis.x > cutValue) {
		rightAxis.x = map(rightAxis.x, cutValue, 255, 0, 255);
	}
	else if (rightAxis.x < -cutValue) {
		rightAxis.x = map(rightAxis.x, -cutValue, -255, 0, -255);
	}
	else {
		rightAxis.x = 0;
	}

	if (rightAxis.y > cutValue) {
		rightAxis.y = map(rightAxis.y, cutValue, 255, 0, 255);
	}
	else if (rightAxis.y < -cutValue) {
		rightAxis.y = map(rightAxis.y, -cutValue, -255, 0, -255);
	}
	else {
		rightAxis.y = 0;
	}
}



Vec2 PS5Controller::GetLeftAxis() {
	return leftAxis;
}

Vec2 PS5Controller::GetRightAxis() {
	return rightAxis;
}

