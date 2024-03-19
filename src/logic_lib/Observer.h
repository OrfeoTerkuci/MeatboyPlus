#ifndef INC_2022_PROJECT_ORFEOTERKUCI_OBSERVER_H
#define INC_2022_PROJECT_ORFEOTERKUCI_OBSERVER_H
#include <iostream>
#include <memory>

namespace LSTD {

class EntityModel;

class Observer {

public:

    /**
     * Constructor for object of Observer class
     */
    Observer() = default;

    /**
     * Update the subscriber
     * @param posX The x-coordinate of the observed object
     * @param posY The y-coordinate of the observed object
     * @param width The width of the observed object
     * @param height The height of the observed object
     */
    virtual void update(double posX , double posY , double width , double height) = 0;

    /**
     * Do something with the received information from the update
     */
    virtual void handle() = 0;

    virtual ~Observer() = default;

};

} // namespace LSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_OBSERVER_H
