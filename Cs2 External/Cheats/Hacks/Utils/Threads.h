#pragma once
#include <Hacks/Glow.h>
#include <Hacks/Triggerbot.h>

namespace Threaded_Cheats
{
    std::thread glow_thread([] {
        while (Flags::isRunning) {
            if (Flags::enableGlowHack)
            {
                GlowHack(Config::GlowHack::GlowColor::CurrentGlowColor);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        });

    std::thread triggerbot_thread([] {
        while (Flags::isRunning) {
            if (Flags::enableTriggerbot && Config::TriggerBot::enableHotKey)
            {
                if (GetAsyncKeyState(Config::TriggerBot::TB_KEYCODE))
                    TriggerBot();
            }
            else if (Flags::enableTriggerbot)
            {
                TriggerBot();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        });

    void JoinThreads()
    {
        if (glow_thread.joinable())
        {
            glow_thread.join();
            triggerbot_thread.join();
        }
    }
}
