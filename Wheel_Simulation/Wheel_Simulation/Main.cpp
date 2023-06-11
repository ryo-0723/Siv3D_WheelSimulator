#include <Siv3D.hpp> // OpenSiv3D v0.6.9
#include"Object.h"
#include"Steer.h"
#include"PS5Controller.h"
void Main()
{
	Window::SetStyle(WindowStyle::Sizable);
	Window::SetTitle(U"Wheel_Simulation");
	Color color = Palette::White;
	Object robot;
	Steer steer;
	PS5Controller ps;
	Vec2 LeftAxis{ 0,0 };
	double InputTurn = 0;
	double robotSpeed = 100;
	size_t controllerIndex = 0;
	size_t robotIndex = 0;
	while (System::Update())
	{
		ClearPrint();

		// "Licenses" ボタンが押されたら
		if (SimpleGUI::Button(U"Licenses", Vec2{ 10, 250 }))
		{
			// ライセンス情報を表示
			LicenseManager::ShowInBrowser();
		}
		switch (controllerIndex) {
		case 0:
			LeftAxis.y = KeyW.pressed() * 255 - KeyS.pressed() * 255;
			LeftAxis.x = KeyD.pressed() * 255 - KeyA.pressed() * 255;
			InputTurn = KeyRight.pressed() * 255 - KeyLeft.pressed() * 255;
			break;
		case 1:
			ps.Update(0);
			LeftAxis = ps.GetLeftAxis();
			InputTurn = ps.GetRightAxis().x;
			break;
		}

		//Print << Scene::DeltaTime() * 1000;


		if (robotIndex) {
			steer.Update(LeftAxis, InputTurn, 0);
			steer.Allow();
			std::array<double, 4>angle = { steer.GetPower(place::LF).x
				,steer.GetPower(place::RF).x
				,steer.GetPower(place::RB).x
				,steer.GetPower(place::LB).x };
			std::array<double, 4>length = { steer.GetPower(place::LF).y
				,steer.GetPower(place::RF).y
				,steer.GetPower(place::RB).y
				,steer.GetPower(place::LB).y
			};
			robot.SetPower(length, angle).draw(color);
		}
		else {
			std::array<double, 4>Wheel;
			Wheel[0] = LeftAxis.x + LeftAxis.y + InputTurn;
			Wheel[1] = LeftAxis.x - LeftAxis.y + InputTurn;
			Wheel[2] = -LeftAxis.x - LeftAxis.y + InputTurn;
			Wheel[3] = -LeftAxis.x + LeftAxis.y + InputTurn;
			const auto max = std::max(abs(*std::max_element(Wheel.begin(), Wheel.end()))
				, abs(*std::min_element(Wheel.begin(), Wheel.end())));
			double MAX = robotSpeed;
			if (max > MAX) {
				double maximum = MAX / max;
				for (int i = 0; i < 4; i++) {
					Wheel[i] *= maximum;
				}
			}
			/*オムニ用角度*/
			robot.SetPower(Wheel, { 45,135,225,315 }).draw(color);
		}
		SimpleGUI::RadioButtons(controllerIndex, { U"keybord",U"PS5" }, { 10,90 });
		SimpleGUI::RadioButtons(robotIndex, { U"Omni",U"Steering" }, { 10,170 });
		SimpleGUI::Slider(U"Speed{:.2f}"_fmt(robotSpeed), robotSpeed, 0, 255, Vec2{10, 50},130.0,150.0);
		steer.SetPower(robotSpeed);
	}
}
