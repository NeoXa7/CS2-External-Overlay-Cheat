#pragma once
#include "Hacks.h"

namespace Threaded_Cheats
{
    std::thread glow_thread([] {
        while (Flags::isRunning) {
            if (Flags::enableGlowHack)
            {
                CHEATS::MEMORY_CHEATS::GlowHack(Config::GlowHack::GlowColor::CurrentGlowColor);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        });

    void JoinThreads()
    {
        if (glow_thread.joinable())
        {
            glow_thread.join();
        }
    }
}
