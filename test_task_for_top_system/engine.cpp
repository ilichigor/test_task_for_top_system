#include "engine.h"

using namespace std::chrono_literals;

constexpr std::chrono::nanoseconds timestep(3000ms);

Engine::Engine(QObject *parent)
    : QObject{parent}
    , quit(false)
{

}

void Engine::doWork()
{
    using clock = std::chrono::high_resolution_clock;

    auto time_start = clock::now();

    while (!quit) {
        auto delta_time = clock::now() - time_start;
        if (delta_time >= timestep) {
            emit update();
            time_start = clock::now();
        }
    }
    emit workFinished();
}
