#include <Siv3D.hpp> // OpenSiv3D v0.6.9
#include"Object.h"

void Main()
{
	Window::SetStyle(WindowStyle::Sizable);
	Color color = Palette::White;
	Object robot;

	Vec2 LeftAxis{ 0,0 };
	double InputTurn = 0;

	size_t controllerIndex = 0;
	bool stopped = true;
	for (const auto& info : System::EnumerateGamepads())
	{
		Print << U"[{}] {} ({:#x} {:#x})"_fmt(info.playerIndex, info.name, info.vendorID, info.productID);
	}
	while (System::Update())
	{
		SimpleGUI::RadioButtons(controllerIndex, { U"keybord",U"PS4 orPS5" },{10,100});
		ClearPrint();
		if (const auto gamepad = Gamepad(0)) {
			/*ps5だったらGamepad(0)*/
			/*ps4だったらGamepad(1)*/
			//const auto& info = gamepad.getInfo();
			if (controllerIndex) {
				LeftAxis.x = (int)(gamepad.axes.at(0) * 255);
				LeftAxis.y = -(int)(gamepad.axes.at(1) * 255);
				InputTurn = (int)(gamepad.axes.at(2) * 255);
				/*ps5だったらat(2)*/
				/*ps4だったらat(3)*/
			}
		}
		if(controllerIndex == 0){
			LeftAxis.y = KeyW.pressed() * 40 - KeyS.pressed() * 40;
			LeftAxis.x = KeyD.pressed() * 40 - KeyA.pressed() * 40;
			InputTurn = KeyRight.pressed() * 40 - KeyLeft.pressed() * 40;
		}

		Print << Scene::DeltaTime() * 1000;


		robot.SetPower({ 0,0,0,0 }, {0,0,0,0}).draw(color);

		//std::array<double, 4>Wheel;
		//Wheel[0] = LeftAxis.x + LeftAxis.y + InputTurn;
		//Wheel[1] = LeftAxis.x - LeftAxis.y + InputTurn;
		//Wheel[2] = -LeftAxis.x - LeftAxis.y + InputTurn;
		//Wheel[3] = -LeftAxis.x + LeftAxis.y + InputTurn;
		///*オムニ用角度*/
		//	robot.SetPower(Wheel, { 45,135,225,315 }).draw(color);
	}
}
