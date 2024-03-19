#ifndef INC_2022_PROJECT_ORFEOTERKUCI_CAMERA_H
#define INC_2022_PROJECT_ORFEOTERKUCI_CAMERA_H

#include "EntityModel.h"

namespace LSTD {

class Camera {

private:

    //== Camera properties ==//
    double currentHeight { -1.0 };
    bool maxed {false};
    //== Private constructors ==//
    Camera() = default;
    Camera(Camera const& ref); // Not implemented
    Camera& operator=(Camera const& ref); // Not implemented

public:

    /**
     * Getter function for the camera instance
     * @return The static Camera class type object. If it doesn't exist, it is created
     */
    static Camera& getInstance() {
        static Camera instance;
        return instance;
    }

    /**
     * Calculates the coordinates of all entities
     * @param models The entity models
     */
    void calculateVisible(const std::vector<std::shared_ptr<EntityModel>>& models) const;

    /**
     * Calculates if a single entity is visible
     * @param entity The entity
     * @return True if the entity is visible
     */
    bool isVisible(const std::shared_ptr<EntityModel>& entity) const;

    /**
     * Calculates the new coordinate of the entity
     * @param entity The entity
     */
    void update(const std::shared_ptr<EntityModel>& entity) const;

    /**
     * Getter for current height of the camera
     * @return The current height
     */
    double getCurrentHeight() const { return currentHeight; }

    /**
     * Setter for the current height of the camera
     * @param newHeight The new height you want to set
     */
    void setCurrentHeight(double newHeight) { Camera::currentHeight = newHeight; }

    /**
     * Checks whether player has died (fallen out of bounds).
     * Also fixes camera height if player is above 80% of the current height.
     * @param player The player
     * @param maxHeight The maximal height of the world
     * @return True if player is within visible range , false otherwise
     */
    bool playerCheck(const std::shared_ptr<EntityModel>& player, int maxHeight);

    /**
     * If the height is not already maxed out, moves the camera upwards automatically with a speed of 1/5 tick speed.
     * Caution : The check for whether the world has automatic scrolling should be done separately.
     */
    void scroll();

    /**
     * Reset the camera parameters to default
     */
    void reset();

    virtual ~Camera() = default;
};

} // namespace LSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_CAMERA_H
