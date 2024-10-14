#pragma once
#include <Hacks/Triggerbot.hpp>

namespace Threads
{
    std::thread triggerbot_thread([] {
        while(Flags::IsRunning) {
            if (Flags::enableTriggerbot && Config::TriggerBot::enableHotKey)
            {
                if (GetAsyncKeyState(Config::TriggerBot::currentKey))
                    TRIGGER_BOT();
            }
            else if (Flags::enableTriggerbot)
            {
                TRIGGER_BOT();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        });

    VOID JoinThreads()
    {
        if (triggerbot_thread.joinable())
        {
            triggerbot_thread.join();
        }
    }
}