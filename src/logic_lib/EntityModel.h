#ifndef INC_2022_PROJECT_ORFEOTERKUCI_ENTITYMODEL_H
#define INC_2022_PROJECT_ORFEOTERKUCI_ENTITYMODEL_H

#include "Subject.h"

namespace LSTD {

class EntityModel : public Subject {

private:

    double position_x {0};
    double position_y {0};
    double width {0};
    double height {0};
    double old_xCoord {0};
    double old_yCoord {0};

public:

    /**
     * Constructor for EntityModel class object
     * @param positionX The x-coordinate ( between -1 and 1 )
     * @param positionY The y-coordinate ( greater or equal to -1 )
     */
    explicit EntityModel(double positionX = 0 , double positionY = 0);

    //== Getters==//
    /**
     * Getter for x-coordinate
     * @return The x-coordinate
     */
    double getPositionX() const { return position_x; }

    /**
     * Getter for y-coordinate
     * @return The y-coordinate
     */
    double getPositionY() const { return position_y; }

    /**
     * Getter for the entity width
     * @return The width
     */
    double getWidth() const { return width; }

    /**
     * Getter for the entity height
     * @return The height
     */
    double getHeight() const { return height; }

    /**
     * Getter for the old x-coordinate
     * @return The old x-coordinate
     */
    double getOldXCoord() const { return old_xCoord; }

    /**
     * Getter for the old y-coordinate
     * @return The old y-coordinate
     */
    double getOldYCoord() const { return old_yCoord; }

    //== Setters ==//

    /**
     * Setter for the x-coordinate
     * @param positionX The x-coordinate
     */
    void setPositionX(double positionX);

    /**
     * Setter for the y-coordinate
     * @param positionY The new y-coordinate
     */
    void setPositionY(double positionY);

    /**
     * Setter for the width
     * @param newWidth The new width
     */
    void setWidth(double newWidth) { EntityModel::width = newWidth; }

    /**
     * Setter for the height
     * @param newHeight The new height
     */
    void setHeight(double newHeight) { EntityModel::height = newHeight; }

    /**
     * Setter for the old x-coordinate
     * @param oldXCoord The old x-coordinate
     */
    void setOldXCoord(double oldXCoord) { old_xCoord = oldXCoord; }

    /**
     * Setter for the old y-coordinate
     * @param oldYCoord The old y-coordinate
     */
    void setOldYCoord(double oldYCoord) { old_yCoord = oldYCoord; }

    //== Virtual functions for movement ==//

    /**
     * Accelerates the entity with the given acceleration
     * @param acceleration The acceleration
     */
    virtual void accelerate(double acceleration) = 0;

    /**
     * Movement to the left
     */
    virtual void move_left() = 0;

    /**
     * Movement to the right
     */
    virtual void move_right() = 0;

    /**
     * Jumping movement
     */
    virtual void jump() = 0;

    /**
     * Falling calculation. The new y-coordinate is also calculated here
     */
    virtual void fall() = 0;

    /**
     * Drag calculation (slowing down). The new x-coordinate is also calculated here
     */
    virtual void drag() = 0;

    /**
     * Resets the horizontal speed of the entity
     */
    virtual void resetHorizontalSpeed() = 0;

    /**
     * Resets the vertical speed of the entity
     */
    virtual void resetVerticalSpeed() = 0;

    /**
     * Resets the jumping status of the entity
     */
    virtual void resetJumping() = 0;

    /**
     * Getter for the horizontal speed
     * @return The horizontal speed of the entity
     */
    virtual double getHorizontalSpeed() = 0;

    /**
     * Getter for the vertical speed
     * @return The vertical speed of the entity
     */
    virtual double getVerticalSpeed() = 0;

    /**
     * Check if the entity is blocked to the right (entity against another entity to the right)
     * @return True if it is blocked to the right
     */
    virtual bool isRightBlocked() = 0;

    /**
     * Check if the entity is blocked to the left (entity against another entity to the left)
     * @return True if it is blocked to the left
     */
    virtual bool isLeftBlocked() = 0;

    /**
     * Checi if entity is floor blocked (entity against another entity below)
     * @return True if it is floor blocked
     */
    virtual bool isFloorBlocked() = 0;

    /**
     * Setter for rightBlocked
     * @param newStatus The new status
     */
    virtual void setRightBlocked(bool newStatus) = 0;

    /**
     * Setter for leftBlocked
     * @param newStatus The new status
     */
    virtual void setLeftBlocked(bool newStatus) = 0;

    /**
     * Setter for floorBlocked
     * @param newStatus The new status
     */
    virtual void setFloorBlocked(bool newStatus) = 0;

    ~EntityModel() override = default;
};

} // namespace LSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_ENTITYMODEL_H
