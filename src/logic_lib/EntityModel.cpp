#include "EntityModel.h"

namespace LSTD {

EntityModel::EntityModel(double positionX , double positionY) : position_x(positionX) , position_y(positionY) {}

void EntityModel::setPositionX(double positionX) {
    if(position_x <= -1){
        position_x = -1 + width;
    }
    else if(position_x >= 1){
        position_x = 1 - width;
    }
    else{
        position_x = positionX;
    }
}

void EntityModel::setPositionY(double positionY) {
    if(position_y <= -1.0){
        position_y = -1 + height * 1.5;
    }
    else{
        position_y = positionY;
    }
}

} // namespace LSTD