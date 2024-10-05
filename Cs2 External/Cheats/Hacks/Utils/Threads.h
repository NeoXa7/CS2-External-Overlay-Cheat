#pragma once
#include <Hacks/Glow.h>
#include <Hacks/Triggerbot.h>

namespace Threaded_Cheats
{
    std::thread triggerbot_thread([] {
        while (Flags::isRunning) {
            if (Flags::enableTriggerbot && Config::TriggerBot::enableHotKey)
            {
                if (GetAsyncKeyState(Config::TriggerBot::currentKey))
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
        if (triggerbot_thread.joinable())
        {
            triggerbot_thread.join();
        }       
    }
}
