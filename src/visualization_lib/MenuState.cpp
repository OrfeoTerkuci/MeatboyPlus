#include "MenuState.h"
#include "TextureManager.h"
#include "StateManager.h"
#include "GameWindow.h"
#include "../logic_lib/World.h"
#include "../logic_lib/Camera.h"
#include "../logic_lib/Stopwatch.h"

namespace GSTD {

sf::Text MenuState::playButton = sf::Text();
sf::Text MenuState::levelsButton = sf::Text();


void MenuState::draw() {
    // Draw menu background
    GameWindow::getInstance().getGWindow()->draw( TextureManager::menuBackgroundImage );
    // Draw buttons

    // select the font
    playButton.setFont(TextureManager::buttonFont);

    // set the string to display
    playButton.setString("Play");

    // set the character size
    playButton.setCharacterSize(120); // in pixels, not points!

    // set the color
    playButton.setFillColor(sf::Color::Red);

    if(playButton.getPosition().x == 0 && playButton.getPosition().y == 0){
        playButton.setPosition(Vector2f(360 ,
                                        270)
                               );
    }

    // select the font
    levelsButton.setFont(TextureManager::buttonFont);

    // set the string to display
    levelsButton.setString("Levels");

    // set the character size
    levelsButton.setCharacterSize(120); // in pixels, not points!

    // set the color
    levelsButton.setFillColor(sf::Color::Red);

    if(levelsButton.getPosition().x == 0 && levelsButton.getPosition().y == 0){
        levelsButton.setPosition(Vector2f(560 ,
                                          270)
                                 );
    }

    GameWindow::getInstance().getGWindow()->draw(playButton);
    GameWindow::getInstance().getGWindow()->draw(levelsButton);

}

void MenuState::keyHandle(const Keyboard::Key& key) {
    auto keyHighlight = getKeyHighlight();
    switch (key) {
        case sf::Keyboard::W:
            if (keyHighlight == 1) {
                levelsButton.setStyle(sf::Text::Regular);
                playButton.setStyle(sf::Text::Bold | sf::Text::Italic);
                playButton.setFillColor(sf::Color::Magenta);
                setKeyHighlight(0);
            } else {
                playButton.setStyle(sf::Text::Regular);
                levelsButton.setStyle(sf::Text::Bold | sf::Text::Italic);
                levelsButton.setFillColor(sf::Color::Magenta);
                setKeyHighlight(1);
            }
            break;
        case sf::Keyboard::S :
            if (keyHighlight == 1) {
                levelsButton.setStyle(sf::Text::Regular);
                playButton.setStyle(sf::Text::Bold | sf::Text::Italic);
                playButton.setFillColor(sf::Color::Magenta);
                setKeyHighlight(0);
            } else {
                playButton.setStyle(sf::Text::Regular);
                levelsButton.setStyle(sf::Text::Bold | sf::Text::Italic);
                levelsButton.setFillColor(sf::Color::Magenta);
                setKeyHighlight(1);
            }
            break;
        case sf::Keyboard::Enter :
            // Button selected is "Play"
            if(keyHighlight == 0){
                // Preload level 0
                load();
                // Change state to level for visualization
                StateManager::getInstance().setStateType(1);
                StateManager::getInstance().changeState();
            }
            // Button selected is "Levels"
            else if(keyHighlight == 1){
                StateManager::getInstance().setStateType(3);
                StateManager::getInstance().changeState();
            }
            break;
    }
}

void MenuState::mouseMoveHandle() {
    auto mouseCoordinates = getMouseCoordinates();
    if(playButton.getGlobalBounds().contains(Vector2f(mouseCoordinates.x , mouseCoordinates.y))){
            levelsButton.setStyle(sf::Text::Regular);
            playButton.setStyle(sf::Text::Bold | sf::Text::Italic);
            playButton.setFillColor(sf::Color::Green);
            setKeyHighlight(1);
    }
    else if(levelsButton.getGlobalBounds().contains(Vector2f(mouseCoordinates.x , mouseCoordinates.y))){
            playButton.setStyle(sf::Text::Regular);
            levelsButton.setStyle(sf::Text::Bold | sf::Text::Italic);
            levelsButton.setFillColor(sf::Color::Magenta);
            setKeyHighlight(0);
    }
    else{
        playButton.setStyle(sf::Text::Regular);
        levelsButton.setStyle(sf::Text::Regular);
        setKeyHighlight(3);
    }
}

void MenuState::load() {
    // Load level
    LSTD::World::getInstance().reset();
    LSTD::World::getInstance().parse("../levels/level0.json");
    LSTD::Camera::getInstance().reset();
    // Start stopwatch
    LSTD::Stopwatch::getInstance().reset();
    // Change window name to level name
    GameWindow::getInstance().getGWindow()->setTitle(LSTD::World::getInstance().getName());
}

void MenuState::mouseClickHandle(const Mouse::Button& mouseButton) {
    auto mouseCoordinates = getMouseCoordinates();
    if(mouseButton == sf::Mouse::Button::Left){
        if(playButton.getGlobalBounds().contains(mouseCoordinates.x , mouseCoordinates.y)){
            setKeyHighlight(0);
        }
        else if(levelsButton.getGlobalBounds().contains(mouseCoordinates.x , mouseCoordinates.y)){
            setKeyHighlight(1);
        }
        keyHandle(sf::Keyboard::Enter);
    }
}

} // namespace GSTD
