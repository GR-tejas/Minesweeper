#include "../../header/Time/TimeManager.h"

namespace Time
{
    // Static variable definitions
    std::chrono::time_point<std::chrono::steady_clock> TimeManager::previous_time;
    float TimeManager::delta_time = 0.0f;

    void TimeManager::initialize()
    {
        previous_time = std::chrono::steady_clock::now();
        delta_time = 0.0f;
    }

    void TimeManager::update() { updateDeltaTime(); }

    float TimeManager::getDeltaTime() { return delta_time; }

    void TimeManager::updateDeltaTime()
    {
        delta_time = calculateDeltaTime();
        updatePreviousTime();
    }

    float TimeManager::calculateDeltaTime()
    {
        // Calculate time difference in microseconds between the current and previous frame.
        int delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

        // Convert delta time from microseconds to seconds.
        return static_cast<float>(delta) / 1000000.0f;
    }

    void TimeManager::updatePreviousTime() { previous_time = std::chrono::steady_clock::now(); }
}