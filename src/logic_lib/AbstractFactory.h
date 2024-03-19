#ifndef INC_2022_PROJECT_ORFEOTERKUCI_ABSTRACTFACTORY_H
#define INC_2022_PROJECT_ORFEOTERKUCI_ABSTRACTFACTORY_H

#include "EntityModel.h"
#include <memory>

namespace LSTD {

class AbstractFactory {

public:

    //== Constructor ==//
    AbstractFactory() = default;

    //== Entity creation functions ==//

    /**
     * Creates a new player entity
     * @return A shared_ptr containing the newly created player
     */
    virtual std::shared_ptr<EntityModel> createPlayer() = 0;

    /**
     * Creates a new wall entity
     * @return A shared_ptr containing the newly created wall
     */
    virtual std::shared_ptr<EntityModel> createWall() = 0;

    /**
     * Creates a new goal entity
     * @return A shared_ptr containing the newly created goal
     */
    virtual std::shared_ptr<EntityModel> createGoal() = 0;

    //== Destructor ==/

    virtual ~AbstractFactory() = default;
};

} // namespace LSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_ABSTRACTFACTORY_H
