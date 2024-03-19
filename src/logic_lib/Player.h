#ifndef INC_2022_PROJECT_ORFEOTERKUCI_PLAYER_H
#define INC_2022_PROJECT_ORFEOTERKUCI_PLAYER_H

#include "EntityModel.h"
#include "StandardValues.h"

namespace LSTD {

class Player final : public EntityModel {

private:
    double horizontal_velocity {0};
    double vertical_velocity {0};
    bool jumping {false};
    bool rightBlocked {false};
    bool leftBlocked {false};
    bool floorBlocked {false};

public:

    /**
     * Constructor for object of player class
     */
    Player() = default;

    void accelerate(double acceleration) final;
    void move_left() final;
    void move_right() final;
    void jump() final;
    void fall() final;
    void drag() final;

    void resetHorizontalSpeed() final {horizontal_velocity = 0;}
    
    void resetVerticalSpeed() final { vertical_velocity = 0; }

    void resetJumping() final { jumping = false; }

    double getHorizontalSpeed() final { return horizontal_velocity; }

    double getVerticalSpeed() final { return vertical_velocity; }

    bool isRightBlocked() final { return rightBlocked; }

    bool isLeftBlocked() final { return leftBlocked; }

    void setRightBlocked(bool newStatus) final { rightBlocked = newStatus; }

    void setLeftBlocked(bool newStatus) final { leftBlocked = newStatus; }

    bool isFloorBlocked() final { return floorBlocked; }

    void setFloorBlocked(bool newStatus) final { floorBlocked = newStatus; }
    
    ~Player() final = default;
};

} // namespace LSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_PLAYER_H
