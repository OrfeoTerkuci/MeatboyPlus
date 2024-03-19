#ifndef INC_2022_PROJECT_ORFEOTERKUCI_STATE_H
#define INC_2022_PROJECT_ORFEOTERKUCI_STATE_H
#include <SFML/Graphics.hpp>

namespace GSTD {

class State {
private:
    int keyHighlight = 0;
    sf::Vector2u mouseCoordinates = sf::Vector2u();
public:
    /**
     * Default constructor for State type object
     */
    State() = default;

    /**
     * Getter for the selected level / key
     * @return The selected (highlighted) level / key
     */
    int getKeyHighlight() const { return keyHighlight; }

    /**
     * Setter for the key highlight
     * @param newHighlight The newly selected key/level
     */
    void setKeyHighlight(int newHighlight) { State::keyHighlight = newHighlight; }

    /**
     * Getter for the mouse coordinates on screen
     * @return The mouse coordinates
     */
    const sf::Vector2u& getMouseCoordinates() const { return mouseCoordinates; }

    /**
     * Setter for the mouse coordinates on the screen
     * @param newCoordinates The new position of the mouse to be saved
     */
    void setMouseCoordinates(const sf::Vector2u& newCoordinates) { mouseCoordinates = newCoordinates; }

    /**
     * Draw the current screen
     */
    virtual void draw() = 0;

    /**
     * Handle function for key press event
     * @param key The pressed key
     */
    virtual void keyHandle(const sf::Keyboard::Key& key) = 0;

    /**
     * Handle function for mouse move event
     */
    virtual void mouseMoveHandle() = 0;

    /**
     * Handle function for mouse click event
     * @param mouseButton The clicked mouse button
     */
    virtual void mouseClickHandle(const sf::Mouse::Button& mouseButton) = 0;

    /**
     * Player lost
     */
    virtual void lost() = 0;

    /**
     * Player won
     */
    virtual void won() = 0;

    /**
     * Load level
     */
    virtual void load() = 0;

    virtual ~State() = default;
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_STATE_H
