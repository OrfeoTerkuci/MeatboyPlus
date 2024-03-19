#ifndef INC_2022_PROJECT_ORFEOTERKUCI_SUBJECT_H
#define INC_2022_PROJECT_ORFEOTERKUCI_SUBJECT_H

#include "Observer.h"
#include <vector>
#include <memory>
#include <functional>

namespace LSTD {

class Subject {

private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    /**
     * Default constructor for Subject class object
     */
    Subject() = default;

    /**
     * Add observers to watch over this object
     * @param newObserver shared_ptr containing the new observer to be added
     */
    virtual void addObserver(std::shared_ptr<Observer> newObserver);

    /**
     * Remove the observer from the observers list
     * @param observer_rem The observer to be removed
     */
    virtual void removeObserver(std::shared_ptr<Observer> observer_rem);

    /**
     * Notify all observers about your parameters
     * @param newX Your new x-coordinate
     * @param newY Your new y-coordinate
     * @param width Your new width
     * @param height Your new height
     */
    virtual void notifyObservers(double newX , double newY , double width , double height) const;

    /**
     * Getter for the vector of observers
     * @return The observers
     */
    const std::vector<std::shared_ptr<Observer>>& getObservers() const { return observers; };

    virtual ~Subject();
};

} // namespace LSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_SUBJECT_H
