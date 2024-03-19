#include "ConcreteFactory.h"
#include "GoalView.h"
#include "PlayerView.h"
#include "WallView.h"
#include <memory>

namespace GSTD {


std::shared_ptr<LSTD::EntityModel> ConcreteFactory::createPlayer() {
    std::shared_ptr<LSTD::Player> player(new LSTD::Player());
    player->addObserver(std::shared_ptr<LSTD::Observer>(new PlayerView()));
    return player;
}
std::shared_ptr<LSTD::EntityModel> ConcreteFactory::createWall() {
    std::shared_ptr<LSTD::Wall> wall(new LSTD::Wall());
    wall->addObserver(std::shared_ptr<LSTD::Observer>(new WallView()));
    return wall;
}
std::shared_ptr<LSTD::EntityModel> ConcreteFactory::createGoal() {
    std::shared_ptr<LSTD::Goal> goal(new LSTD::Goal());
    goal->addObserver(std::shared_ptr<LSTD::Observer>(new GoalView()));
    return goal;
}


} // namespace GSTD

