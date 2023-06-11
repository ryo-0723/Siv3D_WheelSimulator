#include "stdafx.h"
#include "Steer.h"

void Steer::Update(Vec2 Axis, double z, double gyro) {
	/*とりあえずジャイロのことは加味せずに計算していく*/
	/*z（旋回のベクトル）を(0,z)とすることでy軸と同じ方向になるベクトルが作れる*/
	//LFから時計回りにタイヤの計算
	/*
	[0]LF　  ↑	     [1]RF
	   |￣￣￣￣￣￣|
	   |	   		| 
	   |			|
	   |			|
	   |			|
	   |____________|
	[3]LB			 [2]RB
	*/
	std::array<Vec2, 4> data{};//計算結果一時保存場所

	for (int i = 0; i < 4; i++) {//タイヤの出力計算
		data[i] = Axis + Vec2{ 0,z }.rotate((i * -0.5 - 0.25) * Math::Pi);/*Vec2*/
		//Tire[i].Update(ToDegrees(data[i].yx().rotated(-0.5 * Math::Pi).getAngle()),
		//(double)data[i].length());

		Tire[i].UpdateRev(ToDegrees(data[i].yx().rotated(-0.5 * Math::Pi).getAngle()),
			(double)data[i].length());
	}

	/*PWMの最大値をとる*/
	const auto max = (*std::max_element(Tire.begin(), Tire.end(), [](const Wheel& lhs, const Wheel& rhs) {
		return abs(lhs.length) < abs(rhs.length);})).length;
	if (max > MAX) {
		double maximum = MAX / max;
		for (int i = 0; i < 4; i++) {
			Tire[i].length *= maximum;
		}
	}
}

void Steer::Show() {
	//for(int i=0;i<4;++i)
	//Print << U"angle  :"<< Tire[i].GetAngle();
	//for(int i=0;i<4;++i)
	//Print << U"length :"<< Tire[i].GetLength();
}

void Steer::Stop() {
	for (int i = 0; i < 4;++i) {
		Tire[i].Stop();
	}
}
void Steer::Allow() {
	for (int i = 0; i < 4; ++i) {
		Tire[i].Allow();
	}
}

Vec2 Steer::GetPower(place unit) {
	return { Tire[static_cast<int>(unit)].GetAngle(),Tire[static_cast<int>(unit)].GetLength() };
}

void Steer::Culibration() {

}

void Steer::SetPower(double power) {
	MAX = power;
}
