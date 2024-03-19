#ifndef INC_2022_PROJECT_ORFEOTERKUCI_WALL_H
#define INC_2022_PROJECT_ORFEOTERKUCI_WALL_H

#include "EntityModel.h"

namespace LSTD {

class Wall : public EntityModel {
public:
    Wall() = default;

    void accelerate(double acceleration) override {}
    void move_left() override {}
    void move_right() override {}
    void jump() override {}
    void fall() override {}
    void drag() override {}
    void resetHorizontalSpeed() override {}
    void resetVerticalSpeed() override {}
    void resetJumping() override {}
    double getHorizontalSpeed() override { return 0; }
    double getVerticalSpeed() override { return 0; }
    bool isRightBlocked() override { return false; }
    bool isLeftBlocked() override { return false; }
    void setRightBlocked(bool newStatus) override {}
    void setLeftBlocked(bool newStatus) override {}
    bool isFloorBlocked() override { return false; }
    void setFloorBlocked(bool newStatus) override {}

    ~Wall() override = default;
};

} // namespace LSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_WALL_H
