#include "Camera.h"
#include "StandardValues.h"

namespace LSTD {

void Camera::calculateVisible(const std::vector<std::shared_ptr<EntityModel>>& models) const {
    for(const auto& e : models){
        update(e);
    }
}

bool Camera::isVisible(const std::shared_ptr<EntityModel>& entity) const {
    return (entity->getPositionY() >= currentHeight - 1 && entity->getPositionY() <= currentHeight + 11);
}

void Camera::update(const std::shared_ptr<EntityModel>& entity) const {
    double newY = entity->getPositionY() - currentHeight - 1;
    entity->notifyObservers(entity->getPositionX() , newY , entity->getWidth() , entity->getHeight());
}

bool Camera::playerCheck(const std::shared_ptr<EntityModel>& player, int maxHeight) {
    if(player->getPositionY() < currentHeight){
        return false;
    }
    if(maxed){
        return true;
    }
    if(player->getPositionY() > (currentHeight + 10) * 0.8){
        currentHeight += player->getPositionY() - (currentHeight + 10) * 0.8;
    }
    if(currentHeight + 10 > maxHeight){
        currentHeight = maxHeight - 10;
        maxed = true;
    }
    return true;
}

void Camera::reset() {
    currentHeight = -1.0;
    maxed = false;
}

void Camera::scroll() {
    if(!maxed){
        currentHeight += TICK_SPEED / 5;
    }
}

} // namespace LSTD