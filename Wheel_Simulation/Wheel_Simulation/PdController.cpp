#include "PdController.h"


void PdController::Update(double controlValue, double targetValue) {
	//偏差の計算
	double deviation = targetValue - controlValue;

	//比例量の計算
	proPower = kp * deviation;

	//微分量の計算
	difPower = (kd * (deviation - lastDeviation))/0.0167;

	//操作量の計算
	power = proPower + difPower;

	//偏差の保存
	lastDeviation = deviation;

}

double PdController::GetPower() {
	return power;
}

void PdController::ClearPower() {
	proPower = 0.0;
	difPower = 0.0;
	power = 0.0;
	lastDeviation = 0.0;

}

void PdController::SetParamPro(double kpro) {
	this->kp = kpro;
}

void PdController::SetParamDif(double kdif) {
	this->kd = kdif;
}

double PdController::GetProPower() {
	return proPower;
}

double PdController::GetDifPower() {
	return difPower;
}
