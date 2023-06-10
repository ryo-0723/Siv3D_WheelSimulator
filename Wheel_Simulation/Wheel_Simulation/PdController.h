#pragma once
class PdController
{
private:
	double kp;				//比例定数
	double kd;				//微分定数

	double power;			//操作量
	double lastDeviation;	//過去の偏差

	double proPower;		//比例量
	double difPower;		//微分量

public:
	/*      コンストラクタ
	 *      @param  kp            比例係数
	 *      @param  kd            微分係数
	 *      @param  callInterval_us Update()の呼び出し周期
	 */
	PdController(double kp, double kd)
		:kp(kp), kd(kd), power(0), lastDeviation(0), proPower(0), difPower(0)
	{}

	/*デストラクタ
	*/
	~PdController() {}

	/*     データ更新
	 *      @param  controlValue    制御量
	 *      @param  targetValue     目標値
	 */
	void Update(double controlValue, double targetValue);

	/*		操作量の取得
	 *		@return power 操作量
	 */
	double GetPower();

	/*		操作量のクリア
	 *		データをすべて０にする
	 */
	void ClearPower();

	/*     比例係数の設定
	 *     @param kp    比例係数の値
	 */
	void SetParamPro(double kp);

	/*     微分係数の設定
	 *     @param kd    微分係数の値
	 */
	void SetParamDif(double kd);


	/*     比例量の取得
	 *     @return proPower 比例量
	 */
	double GetProPower();

	/*     微分量の取得
	 *     @return difPower 微分量
	 */
	double GetDifPower();

}; 

