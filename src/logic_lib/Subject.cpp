#include "Subject.h"
#include <algorithm>

namespace LSTD {

void Subject::addObserver(std::shared_ptr<Observer> newObserver) {
    observers.push_back(std::move(newObserver));
}

void Subject::removeObserver(std::shared_ptr<Observer> observer_rem) {
    observers.erase(std::remove_if(observers.begin(),observers.end(),
                                    [&](const auto obs)-> bool { return obs == observer_rem; }),
                    observers.end());
}

void Subject::notifyObservers(double newX, double newY , double width , double height) const {
    for(const auto& obs : observers){
        obs->update(newX , newY , width , height);
    }
}

Subject::~Subject() {
    for (auto o : observers) {
        o.reset();
    }
    observers.clear();
}

} // namespace LSTD