#include "SelectionState.h"
#include "GameWindow.h"
#include "TextureManager.h"
#include "StateManager.h"
#include "../logic_lib/World.h"
#include "../logic_lib/Camera.h"
#include "../logic_lib/Stopwatch.h"


namespace GSTD {


std::vector<std::string> SelectionState::levelButtons = {};
sf::Text SelectionState::button = sf::Text("" , TextureManager::buttonFont , 100);
sf::Sprite SelectionState::leftArrow = sf::Sprite(TextureManager::levelArrow ,
                                                  sf::IntRect(192 , 486 , 67 , 89));
sf::Sprite SelectionState::rightArrow = sf::Sprite(TextureManager::levelArrow ,
                                                   sf::IntRect(192 , 486 , 67 , 89));
bool SelectionState::loaded = false;

void SelectionState::draw() {
    loadLevels();
    // Draw menu background
    GameWindow::getInstance().getGWindow()->draw( TextureManager::menuBackgroundImage );
    // Check which key is highlighted
    button.setString(levelButtons[getKeyHighlight()]);
    button.setFillColor(sf::Color::Red);
    if(button.getPosition().x == 0 && button.getPosition().y == 0){
        double posX = (GameWindow::getInstance().getWidth() / 2) - (button.getGlobalBounds().width / 2);
        button.setPosition(Vector2f(posX ,
                                    270)
        );
    }
    // Arrows on each side
    if(rightArrow.getPosition().x == 0 && rightArrow.getPosition().y == 0){
        // Right side
        double posX = button.getPosition().x + button.getGlobalBounds().width + 100;
        if(posX < GameWindow::getInstance().getWidth() * 0.70){
            posX = GameWindow::getInstance().getWidth() * 0.70;
        }
        rightArrow.setPosition(posX ,
                               button.getPosition().y - button.getGlobalBounds().height + rightArrow.getGlobalBounds().height);

    }
    if(leftArrow.getPosition().x == 0 && leftArrow.getPosition().y == 0){
        double posX = button.getPosition().x - 100;
        // Mirror to left side
        if(posX > GameWindow::getInstance().getWidth() * 0.30){
            posX = GameWindow::getInstance().getWidth() * 0.30;
        }
        leftArrow.setScale(-1 , 1);
        leftArrow.setPosition(posX,
                              button.getPosition().y - button.getGlobalBounds().height + leftArrow.getGlobalBounds().height);
    }
    GameWindow::getInstance().getGWindow()->draw(rightArrow);
    GameWindow::getInstance().getGWindow()->draw(leftArrow);
    GameWindow::getInstance().getGWindow()->draw(button);
}

void SelectionState::keyHandle(const sf::Keyboard::Key& key) {
    auto keyHighlight = getKeyHighlight();
    switch (key) {
    case sf::Keyboard::W:
        if(keyHighlight == 0){
            setKeyHighlight(levelButtons.size() - 1);
        }
        else{
            setKeyHighlight(keyHighlight - 1);
        }
        break;

    case sf::Keyboard::S :
        if(keyHighlight == levelButtons.size() - 1){
            setKeyHighlight(0);
        }
        else{
            setKeyHighlight(keyHighlight + 1);
        }
        break;

    case sf::Keyboard::Enter :
            // Preload level
            load();
            // Switch to level state for visualization
            StateManager::getInstance().setStateType(1);
            StateManager::getInstance().changeState();
        break;

    case sf::Keyboard::Escape :
        // Go back to menu screen
        StateManager::getInstance().setStateType(0);
        StateManager::getInstance().changeState();
        break;

    case sf::Keyboard::Backspace:
        // Go back to menu screen
        StateManager::getInstance().setStateType(0);
        StateManager::getInstance().changeState();
        break;
    }
}

void SelectionState::mouseMoveHandle() {} // No hover functionality

void SelectionState::mouseClickHandle(const Mouse::Button& mouseButton) {
    auto mouseCoords = getMouseCoordinates();
    if(leftArrow.getGlobalBounds().contains(mouseCoords.x , mouseCoords.y)){
        keyHandle(sf::Keyboard::W);
    }
    else if(rightArrow.getGlobalBounds().contains(mouseCoords.x , mouseCoords.y)){
        keyHandle(sf::Keyboard::S);
    }
    else if(button.getGlobalBounds().contains(mouseCoords.x , mouseCoords.y)){
        keyHandle(sf::Keyboard::Enter);
    }
}

void SelectionState::load() {
    if(!loaded){
        loadLevels();
    }
    // Load level
    std::string name = "../levels/" + levelButtons[getKeyHighlight()] + ".json";
    LSTD::World::getInstance().reset();
    LSTD::World::getInstance().parse(name);
    LSTD::Camera::getInstance().reset();
    // Start stopwatch
    LSTD::Stopwatch::getInstance().reset();
    // Change window name to level name
    GameWindow::getInstance().getGWindow()->setTitle(LSTD::World::getInstance().getName());
}

void SelectionState::won() {
    if(getKeyHighlight() == levelButtons.size() - 1){
        load();
    }
    else{
        setKeyHighlight(getKeyHighlight() + 1);
        load();
    }
}

void SelectionState::loadLevels() {
    // Read all available levels
    if(!loaded){
        try {
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir ("../levels")) != nullptr) {
                /* print all the files and directories within directory */
                while ((ent = readdir (dir)) != nullptr) {
                    std::string name = ent->d_name;
                    if(name.length() >= 5 && name.substr(name.length() - 4 , 4) == "json"){
                        // Create new text button for the level
                        name = name.substr(0 , name.length() - 5);
                        levelButtons.push_back(name);
                    }
                }
                closedir (dir);
                SelectionState::loaded = true;
                if(!levelButtons.empty()){
                    std::sort(levelButtons.begin() , levelButtons.end() ,
                              [](const auto t1 , const auto t2) -> bool {
                                  return t1 < t2;
                              });
                }

            } else {
                /* could not open directory */
                throw ExitFailure("Could not open directory");
            }
        } catch (ExitFailure& e) {
            std::cout << e.what();
        }
    }
}

} // namespace GSTD