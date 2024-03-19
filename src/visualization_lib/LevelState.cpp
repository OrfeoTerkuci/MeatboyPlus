//
// Created by oterk on 16/11/2022.
//

#include "LevelState.h"
#include "../logic_lib/Camera.h"
#include "../logic_lib/World.h"
#include "../logic_lib/Stopwatch.h"
#include "TextureManager.h"
#include "GameWindow.h"
#include "StateManager.h"

namespace GSTD {

void LevelState::draw() {
    // Draw background
    GameWindow::getInstance().getGWindow()->draw(TextureManager::levelBackgroundImage);
    // Draw all visible entities
    for(auto& e : LSTD::World::getInstance().getWalls()){
        if(LSTD::Camera::getInstance().isVisible(e)){
            for(const auto& o : e->getObservers()){
                o->handle();
            }
        }
    }
    auto& player = LSTD::World::getInstance().getCurrentPlayer();
    if(LSTD::Camera::getInstance().isVisible(player)){
        for(const auto& o : player->getObservers()){
            o->handle();
        }
    }

    auto& goal = LSTD::World::getInstance().getCurrentGoal();
    if(LSTD::Camera::getInstance().isVisible(goal)){
        for(const auto& o : goal->getObservers()){
            o->handle();
        }
    }
}

void LevelState::keyHandle(const Keyboard::Key& key) {
    switch (key) {
    case sf::Keyboard::A :
        // Left and jump
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            LSTD::World::getInstance().jump();
        }
        // If already moving right (D)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            break;
        }
        LSTD::World::getInstance().move_left();
        break;

    case sf::Keyboard::D :
        // Right and jump
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            LSTD::World::getInstance().jump();
        }
        // If already moving left (D)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            break;
        }
        LSTD::World::getInstance().move_right();
        break;

    case sf::Keyboard::Space :
        // Left and jump
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            keyHandle(sf::Keyboard::A);
        }
        // Left and jump
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            keyHandle(sf::Keyboard::D);
        }
        LSTD::World::getInstance().jump();
        break;

    case sf::Keyboard::Escape :

    case sf::Keyboard::Backspace:
        // Erase current level
        LSTD::World::getInstance().reset();
        LSTD::Camera::getInstance().reset();
        LSTD::Stopwatch::getInstance().reset();
        setKeyHighlight(0);
        // Go back to menu screen
        StateManager::getInstance().setStateType(0);
        StateManager::getInstance().changeState();
        break;

    }
}

void LevelState::load() {

}

void LevelState::lost() {
    if(!LSTD::Camera::getInstance().playerCheck(LSTD::World::getInstance().getCurrentPlayer(),
                                                                         LSTD::World::getInstance().getMaxHeight())){
        StateManager::getInstance().reloadLevel();
    }
}

void LevelState::won() {
    if(LSTD::World::getInstance().playerWon()){
        StateManager::getInstance().changeLevel();
    }
}

} // namespace GSTD