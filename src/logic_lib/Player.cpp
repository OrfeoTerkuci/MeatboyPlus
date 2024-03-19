#include "Player.h"
#include "Stopwatch.h"
#include <cmath>

namespace LSTD {

void Player::accelerate(double acceleration) {
    // Calculate speed
    horizontal_velocity += acceleration;
    // Max speed check
    if(horizontal_velocity > MAX_VELOCITY){
        horizontal_velocity = MAX_VELOCITY;
    }
    else if(horizontal_velocity < -MAX_VELOCITY){
        horizontal_velocity = -MAX_VELOCITY;
    }
}

void Player::move_left() {
    double delta_t = Stopwatch::getInstance().getDeltaT();
    // Blocked to the left = can't move to the left
    if(leftBlocked){
        return;
    }
    // On the air
    if(vertical_velocity != 0 && !jumping){
        accelerate(-AIR_ACCELERATION * delta_t);
    }
    // On the ground , not blocked on the left
    else {
        accelerate(-ACCELERATION * delta_t);
    }
    rightBlocked = false;
}

void Player::move_right() {
    double delta_t = Stopwatch::getInstance().getDeltaT();
    // Blocked on the right = can't move on the right
    if(rightBlocked){
        return;
    }
    // On the air
    if(vertical_velocity != 0 && !jumping){
        accelerate(AIR_ACCELERATION * delta_t);
    }
    // On the ground , not blocked on the right
    else {
        accelerate(ACCELERATION * delta_t);
    }
    leftBlocked = false;
}

void Player::jump() {
    if(jumping){
        return;
    }
    // Check for wall jump
    if(rightBlocked && !floorBlocked){
        vertical_velocity =     cos(M_PI / 4) * MAX_VERTICAL;
        horizontal_velocity =   -cos(M_PI / 4) * MAX_VERTICAL;
        rightBlocked = false;
        jumping = true;
    }
    else if(leftBlocked && !floorBlocked){
        vertical_velocity =     cos(M_PI / 4) * MAX_VERTICAL;
        horizontal_velocity =   cos(M_PI / 4) * MAX_VERTICAL;
        leftBlocked = false;
        jumping = true;
    }
    // Set vertical velocity to a fixed value for normal jump
    if(!jumping){
        vertical_velocity = MAX_VERTICAL;
        jumping = true;
        leftBlocked = false;
        rightBlocked = false;
        floorBlocked = false;
    }
}

void Player::fall() {
    double posY = 0;
    double delta_t = Stopwatch::getInstance().getDeltaT();
    // Calculate new fall speed
    if(floorBlocked && !jumping){
        vertical_velocity = 0;
    }
    // Not against a wall and going down
    else if(!leftBlocked && !rightBlocked){
        vertical_velocity -= GRAVITY_COEFFICIENT * delta_t;
    }
    // Against a wall
    else if(vertical_velocity <= 0){
        vertical_velocity -= DRAG_COEFFICIENT * delta_t;
    }
    // Limit max fall speed
    if(vertical_velocity < -MAX_VERTICAL){
        vertical_velocity = -MAX_VERTICAL;
    }
    // Calculate new position
    if(!floorBlocked){
        posY = (-GRAVITY_COEFFICIENT * delta_t * delta_t / 2 ) + vertical_velocity * delta_t;
    }
    // Save old positions
    if(posY != 0){
        setOldYCoord(getPositionY());
        setPositionY(getPositionY() + posY);
    }
}

void Player::drag() {
    // Calculate new position
    double posX = 0;
    double delta_t = Stopwatch::getInstance().getDeltaT();
    if(horizontal_velocity > 0){
        // Decelerate
        if(vertical_velocity != 0){
            accelerate(-AIR_RESISTANCE * delta_t);
        }
        else{
            accelerate(-DRAG_COEFFICIENT * delta_t);
        }
        // Check if stopped
        if(horizontal_velocity < 0){
            horizontal_velocity = 0;
        }
        if(!rightBlocked && !floorBlocked && vertical_velocity != 0){
            posX = (AIR_ACCELERATION * delta_t * delta_t / 2 ) + horizontal_velocity * delta_t;
        }
        else if(!rightBlocked){
            posX = (ACCELERATION * delta_t * delta_t / 2 ) + horizontal_velocity * delta_t;
        }
    }
    else if(horizontal_velocity < 0){
        // Decelerate
        if(vertical_velocity != 0){
            accelerate(AIR_RESISTANCE * delta_t);
        }
        else{
            accelerate(DRAG_COEFFICIENT * delta_t);
        }
        // Check if stopped
        if(horizontal_velocity > 0){
            horizontal_velocity = 0;
        }
        if(!leftBlocked && !floorBlocked && vertical_velocity != 0){
            posX = (-AIR_ACCELERATION * delta_t * delta_t / 2 ) + horizontal_velocity * delta_t;
        }
        else if(!leftBlocked){
            posX = (-ACCELERATION * delta_t * delta_t / 2 ) + horizontal_velocity * delta_t;
        }
    }
    if(posX != 0){
        // Save old position
        setOldXCoord(getPositionX());
        // Set position
        setPositionX(getPositionX() + posX);
    }
}

} // namespace LSTD