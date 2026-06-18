#include "Timer.hpp"
#include <stdexcept>

Timer::Timer():
startTime(),
endTime(),
running(false),
accumulated(0.0)
{}

void Timer::start()
{
    running = true;
    accumulated = 0.0;
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
    if (!running)
        throw std::logic_error("Timer::stop() called when not running");
    endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    accumulated += duration.count();
    running = false;
}

double Timer::elapsedMilliseconds() const
{
    double micros = accumulated;
    if (running)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::microseconds>(now - startTime);
        micros += dur.count();
    }
    return micros / 1000.0;
}

double Timer::elapsedMicroseconds() const
{
    double micros = accumulated;
    if (running)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::microseconds>(now - startTime);
        micros += dur.count();
    }
    return micros;
}

void Timer::reset()
{
    running = false;
    accumulated = 0.0;
    startTime = std::chrono::high_resolution_clock::now();
}
