#pragma once

enum class  place {
	LF,
	RF,
	RB,
	LB
};

class Steer
{
private:
	/*ベクトルの計算後のデータ保存場所*/
	struct Wheel {
		double length, angle, oldAngle, newOffset,oldOffset;
		int newRevLength = 1, oldRevLength = 1;/*モーターの値を反転するかの変数*/
		bool stopFlag = false;

		/// @brief -double--+doubleの範囲に変更する関数
		void  Update(double newAngle, double newLength) {
			angle = newAngle;
			length = newLength;
			/*nanのままいったん計算*/
			/*無限増加を防ぐために違う変数を作る*/
			double overAngle = angle + 180.00;
			double oldOverAngle = oldAngle + 180.00;

			/*nanとの比較演算子は常にfalseが出るらしい*/
			/*nan判定の前にこれを行うことでバグはなくなるのでは？*/
			if (oldOverAngle - overAngle > 330 && oldOverAngle - overAngle <= 360)
				/*変化量がほぼ一周分になるときは一周したと判定する*/
				newOffset += 360;
			if (oldOverAngle - overAngle < -330 && oldOverAngle - overAngle >= -360)
				/*変化量がほぼ一周分になるときは一周したと判定する*/
				newOffset -= 360;

			/*nanをなくす*/
			if (IsNaN(angle))/*角度がnanのときは前周期の角度のままにする*/
				angle = oldAngle;

			/*最初はタイヤの回転角度は0から359までの範囲にする*/
			/*最大の許容値を400としておいて、回転量が少ないときは小さく回転し、回転量が多いときにタイヤを反転して許容値から離す*/
			if (GetAngle() >= 350) {
				if (GetAngle() > 400)/*絶対反転角---個の角度になったときは必ず反転をする*/
					newOffset -= 360.00;
				if (angle - oldAngle > 20)/*指定量より動く回転の量が多いときタイヤをあるときのみ360回転させる*/
					newOffset -= 360.00;
			}
			if (GetAngle() <= 10) {
				if (GetAngle() < -40) /*絶対反転角---個の角度になったときは必ず反転をする*/
					newOffset += 360.00;
				if (angle - oldAngle < -20)/*指定量より動く回転の量が多いときタイヤをあるときのみ360回転させる*/
					newOffset += 360.00;
			}
		}
		void UpdateRev(double newAngle,double newLength) {/*ステアの最適化制御*/
			oldAngle = angle;
			oldOffset = newOffset;
			oldRevLength = newRevLength;
			if (stopFlag) {
				angle = newAngle;
				length = newLength;
				double overAngle = angle + 180.00;
				double oldOverAngle = oldAngle + 180.00;

				/*nanとの比較演算子は常にfalseが出るらしい*/
				/*nan判定の前にこれを行うことでバグはなくなるのでは？*/
				if (oldOverAngle - overAngle > 330.00 && oldOverAngle - overAngle <= 360.00)
					/*変化量がほぼ一周分になるときは一周したと判定する*/
					newOffset += 360.00;
				if (oldOverAngle - overAngle < -330.00 && oldOverAngle - overAngle >= -360.00)
					/*変化量がほぼ一周分になるときは一周したと判定する*/
					newOffset -= 360.00;

				/*nanをなくす*/
				if (IsNaN(angle))/*角度がnanのときは前周期の角度のままにする*/
					angle = oldAngle;

				/*回転量を最小にするための計算
				　どっち回転が速いかの判定後計算する
				*/
				if (GetAngle() - GetOldAngle() > GetOldAngle() - GetAngle()) {
					if (GetAngle() - GetOldAngle() > 90.00 && GetAngle() - GetOldAngle() <= 270.00) {
						newOffset -= 180.00;
						newRevLength *= -1;
					}
					else if (GetAngle() - GetOldAngle() > 270.00 && GetAngle() - GetOldAngle() <= 360.00) {
						newOffset -= 360;
					}
				}
				else {
					if (GetAngle() - GetOldAngle() < -90.00 && GetAngle() - GetOldAngle() >= -270.00) {
						newOffset += 180.00;
						newRevLength *= -1;
					}
					else if (GetAngle() - GetOldAngle() < -270.00 && GetAngle() - GetOldAngle() >= -360.00) {
						newOffset += 360;
					}
				}
			}
			else {
				angle = oldAngle;
				newOffset =oldOffset;
				length = 0;
				newRevLength =oldRevLength;
			}
		}
		/// @brief タイヤの現在角度を返す関数
		/// @return タイヤの現在角度
		double GetAngle() {
			return angle + newOffset;
		}
		/// @brief タイヤの全周期の角度を返す関数
		/// @return 前周期の角度
		double GetOldAngle() {
			return oldAngle + oldOffset;
		}
		/// @brief モータのPWMを返す関数 
		/// @return 回転モーターの出力値
		double GetLength() {
			return length * newRevLength;
		}
		void Stop() {
			stopFlag = false;
		}
		void Allow() {
			stopFlag = true;
		}

		/*タイヤの角度はゼロ点を取った瞬間は５０度*/
		void SetAngle(double sets) {
			newOffset = sets-angle;
		}
	};

	std::array<Wheel, 4> Tire{};
	double MAX = 0;
public:
	Steer() = default;

	void Update(Vec2 Axis, double z, double gyro);

	void Stop();

	void Allow();

	void Show();

	Vec2 GetPower(place unit);

	void Culibration();

	void SetPower(double power);
};

