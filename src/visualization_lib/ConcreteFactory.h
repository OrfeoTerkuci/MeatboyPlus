#ifndef INC_2022_PROJECT_ORFEOTERKUCI_CONCRETEFACTORY_H
#define INC_2022_PROJECT_ORFEOTERKUCI_CONCRETEFACTORY_H
#include "../logic_lib/AbstractFactory.h"
#include "../logic_lib/Player.h"
#include "../logic_lib/Goal.h"
#include "../logic_lib/Wall.h"


namespace GSTD {

class ConcreteFactory : public LSTD::AbstractFactory {
public:

    ConcreteFactory() = default;

    std::shared_ptr<LSTD::EntityModel> createPlayer() override;
    std::shared_ptr<LSTD::EntityModel> createWall() override;
    std::shared_ptr<LSTD::EntityModel> createGoal() override;

    ~ConcreteFactory() override = default;
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_CONCRETEFACTORY_H
