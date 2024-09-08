#pragma once
#include "Hacks.h"

namespace Threaded_Cheats
{
	thread glow_thread([] {
		while (Flags::isRunning) {
			if (Flags::enableGlowHack)
			{
				Cheats::Risky_Cheats::GlowHack(Config::GlowHack::GlowColor::CurrentGlowColor);
			}
		}
		});

	thread aimbot_thread([] {
		while (Flags::isRunning) {
			if (Flags::enableAimbot && Config::Aimbot::enableHotKey)
			{
				if (GetAsyncKeyState(Config::Aimbot::AB_KEYCODE))
					Cheats::Risky_Cheats::Aimbot();
			}
			else if (Flags::enableAimbot)
			{
				Cheats::Risky_Cheats::Aimbot();
			}
		}
		});

	void JoinThreads()
	{
		glow_thread.join();
		aimbot_thread.join();
	}
}