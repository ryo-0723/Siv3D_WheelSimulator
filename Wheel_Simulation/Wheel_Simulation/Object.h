#pragma once

#include"PdController.h"
class Object
{
private:
	bool moveMode = true;
	Vec2 pos  = { 400,300 };
	Vec2 size = { 200,200 };
	RectF Robot{ pos,size };
	std::array<RectF, 4> Rectframe{};
	std::array<double, 4> old_angle{};
	std::array<Vec2, 4>Vector{};
	Vec3 Robot_Vec={};/*移動変化量の保存変数*/

public:
	std::array<PdController, 4>anglePd
		 = {PdController(0.1,0.004),
			PdController(0.1,0.004) ,
			PdController(0.1,0.004) ,
			PdController(0.1,0.004) };

	Object()	
	{}

	~Object(){}

	Object& draw(const Color& Framecolor);

	Object& SetPower(std::array<double, 4>length, std::array<double, 4>angle);

};

