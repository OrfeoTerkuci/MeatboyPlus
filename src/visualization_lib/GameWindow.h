//
// Created by oterk on 05/12/2022.
//

#ifndef INC_2022_PROJECT_ORFEOTERKUCI_GAMEWINDOW_H
#define INC_2022_PROJECT_ORFEOTERKUCI_GAMEWINDOW_H
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;

namespace GSTD {

class GameWindow {
private:
    std::unique_ptr<sf::RenderWindow> gWindow;
    GameWindow();

    GameWindow(GameWindow const& ref); // Not implemented
    GameWindow& operator=(GameWindow const& ref); // Not implemented

public:

    /**
     * Getter function for the GameWindow instance
     * @return The static GameWindow class type object. If it doesn't exist, it is created
     */
    static GameWindow& getInstance() {
        // https://stackoverflow.com/a/271104/6453334
        // The only instance
        // Guaranteed to be lazy initialized
        // Guaranteed that it will be destroyed correctly
        static GameWindow instance;
        return instance;
    }

    /**
     * Getter for the smfl RenderWindow object
     * @return The game window
     */
    const std::unique_ptr<sf::RenderWindow>& getGWindow() const { return gWindow; }

    /**
     * Getter for the window width
     * @return The window width
     */
    unsigned int getWidth() const { return getGWindow()->getSize().x; }

    /**
     * Getter for the window height
     * @return The window height
     */
    unsigned int getHeight() const { return getGWindow()->getSize().y; }

    ~GameWindow() = default;
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_GAMEWINDOW_H
