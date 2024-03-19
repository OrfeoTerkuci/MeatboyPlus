//
// Created by oterk on 16/11/2022.
//

#include "Game.h"

#include <memory>
#include "GameWindow.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "State.h"

namespace GSTD {

void Game::launch() {
    // Load textures
    TextureManager::loadTextures();
    // Initialize state manager
    StateManager::getInstance();
    // Set up game logic
    setupLogic();
    // Initialize game window
    setupWindow();
}

void Game::setupWindow() {
    auto& g_win = GSTD::GameWindow::getInstance();

    auto& window = g_win.getGWindow();

    auto& cam = LSTD::Camera::getInstance();

    auto& world = LSTD::World::getInstance();

    window->setFramerateLimit(FRAMERATE);

    while (window->isOpen())
    {
        sf::Event event{};
        while (window->pollEvent(event))
        {
            switch (event.type) {
            case Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                StateManager::getInstance().getCurrentState()->keyHandle(event.key.code);
                break;
            case sf::Event::KeyReleased:
                break;
            case Event::MouseMoved:
                StateManager::getInstance().getCurrentState()->setMouseCoordinates(Vector2u (event.mouseMove.x , event.mouseMove.y));
                StateManager::getInstance().getCurrentState()->mouseMoveHandle();
                break;
            case Event::MouseButtonPressed:
                StateManager::getInstance().getCurrentState()->setMouseCoordinates(Vector2u(event.mouseButton.x , event.mouseButton.y));
                StateManager::getInstance().getCurrentState()->mouseClickHandle(event.mouseButton.button);
                break;
            }
        }
        if(StateManager::getInstance().getStateType() == 1){
            // Check if player lost
            StateManager::getInstance().lost();
            // Check if player won
            StateManager::getInstance().won();
            // Scroll up if world is on autoscroll
            if(world.isScroll()){
                cam.scroll();
            }
            // Visible blocks calculation
            cam.playerCheck(world.getCurrentPlayer(), world.getMaxHeight());
            // Calculate visible entities
            cam.calculateVisible(world.getWalls());
            if(cam.isVisible(world.getCurrentPlayer())){
                cam.update(world.getCurrentPlayer());
            }
            if(cam.isVisible(world.getCurrentGoal())){
                cam.update(world.getCurrentGoal());
            }
            // Update stopwatch
            LSTD::Stopwatch::getInstance().update();
            // Physics calculations
            world.fall();
            world.drag();
            world.calculateCollision();

        }
        // Show everything
        window->clear();
        StateManager::getInstance().draw();
        window->display();
    }
}

void Game::setupLogic() {
    // Create the world
    auto& world = LSTD::World::getInstance();
    // Set up concrete factory
    world.loadFactory(std::make_unique<ConcreteFactory>());
    // Set up the camera
    LSTD::Camera::getInstance();
}

} // namespace GSTD