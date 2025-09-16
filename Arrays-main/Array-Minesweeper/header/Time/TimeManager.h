#pragma once
#include <chrono>

namespace Time
{
    class TimeManager
    {
    private:
        static std::chrono::time_point<std::chrono::steady_clock> previous_time;
        static float delta_time;

        static void updateDeltaTime();
        static float calculateDeltaTime();
        static void updatePreviousTime();

    public:
        static void initialize();
        static void update();

        static float getDeltaTime();
    };
}