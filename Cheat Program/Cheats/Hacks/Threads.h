#pragma once
#include "Hacks.h"

namespace Threaded_Cheats
{
	thread glow_thread([] {
		while (Flags::isRunning) {
			if (Flags::enableGlowHack)
			{
				CHEATS::MEMORY_CHEATS::GlowHack(Config::GlowHack::GlowColor::CurrentGlowColor);
			}
		}
		});

	/*thread aimbot_thread([] {
		while (Flags::isRunning) {
			if (Flags::enableAimbot && Config::Aimbot::enableHotKey)
			{
				if (GetAsyncKeyState(Config::Aimbot::AB_KEYCODE))
					CHEATS::MEMORY_CHEATS::Aimbot();
			}
			else if (Flags::enableAimbot)
			{
				CHEATS::MEMORY_CHEATS::Aimbot();
			}
		}
		});*/

	void JoinThreads()
	{
		glow_thread.join();
		//aimbot_thread.join();
	}
}