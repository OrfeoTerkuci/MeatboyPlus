#ifndef INC_2022_PROJECT_ORFEOTERKUCI_STOPWATCH_H
#define INC_2022_PROJECT_ORFEOTERKUCI_STOPWATCH_H

#include "StandardValues.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
namespace LSTD {

class Stopwatch {

private:
    std::chrono::steady_clock::time_point last_tick;
    std::chrono::steady_clock::time_point current_tick;
    double delta_t {TICK_SPEED};
    //== Private constructors ==//
    Stopwatch();
    Stopwatch(Stopwatch const& ref); // Not implemented
    Stopwatch& operator=(Stopwatch const& ref); // Not implemented

public:

    /**
     * Getter function for the stopwatch instance
     * @return The static Stopwatch class type object. If it doesn't exist, it is created
     */
    static Stopwatch& getInstance(){
        static Stopwatch instance;
        return instance;
    }

    /**
     * Update the delta_t (time since last update)
     */
    void update();

    /**
     * Getter for the tick difference
     * @return The delta_t
     */
    double getDeltaT() const;

    /**
     * Reset the stopwatch
     */
    void reset();

    virtual ~Stopwatch();
};

} // namespace LSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_STOPWATCH_H
