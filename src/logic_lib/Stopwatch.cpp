#include "Stopwatch.h"

namespace LSTD {

//std::chrono::steady_clock::time_point Stopwatch::last_tick = std::chrono::steady_clock::now();
//std::chrono::steady_clock::time_point Stopwatch::current_tick = std::chrono::steady_clock::now();

Stopwatch::Stopwatch() {
    // Start timer on instance call
    current_tick = std::chrono::steady_clock::now();
}

void Stopwatch::update() {
    // Save last tick
    last_tick = current_tick;
    // Save current tick
    current_tick = std::chrono::steady_clock::now() ;
    // Update tick speed
    std::chrono::duration<double> delta = current_tick - last_tick;
    delta_t = delta.count();
    // My laptop is fast as fuck so... always in here
    if(delta_t < TICK_SPEED){
        delta_t = TICK_SPEED;
    }

}
double Stopwatch::getDeltaT() const {
    return delta_t;
}
void Stopwatch::reset() {
    current_tick = std::chrono::steady_clock::now();
}

Stopwatch::~Stopwatch() = default;
} // namespace LSTD