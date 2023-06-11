#pragma once
class PS5Controller
{
private:
	int cutValue=20;
	Vec2 leftAxis = {};
	Vec2 rightAxis = {};

public:
	PS5Controller() {}


	void Update(size_t playerIndex);

	Vec2 GetLeftAxis();

	Vec2 GetRightAxis();

	double map(double x, double in_min, double in_max, double out_min, double out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
};

