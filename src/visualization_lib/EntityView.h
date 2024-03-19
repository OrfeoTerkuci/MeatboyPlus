#ifndef INC_2022_PROJECT_ORFEOTERKUCI_ENTITYVIEW_H
#define INC_2022_PROJECT_ORFEOTERKUCI_ENTITYVIEW_H

#include "../logic_lib/Observer.h"
#include "../logic_lib/EntityModel.h"
#include "GameWindow.h"
#include <SFML/Graphics.hpp>

namespace GSTD {

class EntityView : public LSTD::Observer{
private:
    sf::Sprite block;
    bool init {false};
    double positionX {0};
    double positionY {0};
    double width {0};
    double height {0};
public:

    /**
     * Default constructor for EntityView type object
     */
    EntityView() = default;

    //== Getters ==//

    /**
     * Getter for the sprite representing the entity
     * @return The sprite
     */
    const sf::Sprite& getBlock() const { return block; }

    /**
     * Whether the entityView has been given textures and initialized
     * @return
     */
    bool isInit() const { return init; }

    /**
     * Getter for the x-coordinate of the entity in the game window
     * @return The x-coordinate
     */
    double getPositionX() const { return positionX; }

    /**
     * Getter for the y-coordinate of the entity in the game window
     * @return The y-coordinate
     */
    double getPositionY() const { return positionY; }

    /**
     * Getter for the width of the entity in the game window
     * @return The width
     */
    double getWidth() const { return width; }

    /**
     * Getter for the height of the entity in the game window
     * @return The height
     */
    double getHeight() const { return height; }

    //== Setters ==//

    /**
     * Setter for the sprite
     * @param newBlock The new sprite
     */
    void setBlock(const sf::Sprite& newBlock) { block = newBlock; }

    /**
     * Setter for the initialized status
     * @param newInit The new status
     */
    void setInit(bool newInit) { init = newInit; }

    /**
     * Setter for the x-coordinate
     * @param newPosX The new x-coordinate
     */
    void setPositionX(double newPosX) { positionX = newPosX; }

    /**
     * Setter for the y-coordinate
     * @param newPosY The new y-coordinate
     */
    void setPositionY(double newPosY) { positionY = newPosY; }

    /**
     * Setter for the width
     * @param newWidth The new width
     */
    void setWidth(double newWidth) { width = newWidth; }

    /**
     * Setter for the height
     * @param newHeight The new height
     */
    void setHeight(double newHeight) { height = newHeight; }

    /**
     * Calculates new window position from the new parameters
     * @param posX The in-world x-coordinate
     * @param posY The in-world y-coordinate
     * @param newWidth The in-world width
     * @param newHeight the in-world height
     */
    void update(double posX, double posY, double newWidth, double newHeight) override;

    ~EntityView() override = default;
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_ENTITYVIEW_H
