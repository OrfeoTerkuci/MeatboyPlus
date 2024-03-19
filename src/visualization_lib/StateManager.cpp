#include "StateManager.h"
#include <memory>
#include "State.h"
#include "MenuState.h"
#include "LevelState.h"
#include "SelectionState.h"

namespace GSTD {

StateManager::StateManager() {
    // Initialize state as menu state
    currentState = std::unique_ptr<State>(new MenuState());
}

void StateManager::changeState() {
    auto highlight = currentState->getKeyHighlight();
    // Check state needed
    if(stateType == 0){
        currentState = std::make_unique<MenuState>();
        currentState->setKeyHighlight(highlight);
    }
    else if(stateType == 1){
        currentState = std::make_unique<LevelState>();
        currentState->setKeyHighlight(highlight);
    }
    else if(stateType == 3){
        currentState = std::make_unique<SelectionState>();
        currentState->setKeyHighlight(highlight);
    }
    // False state was given. Reset to 0
    else{
        setStateType(0);
    }
}

void StateManager::draw() {
    currentState->draw();
}

void StateManager::lost() {
    currentState->lost();
}

void StateManager::load() {
    currentState->load();
}

void StateManager::won() {
    currentState->won();
}

void StateManager::changeLevel() {
    // Temp to selection screen
    setStateType(3);
    // Load next level
    changeState();
    won();
    // Change back to level state
    setStateType(1);
    changeState();
    load();
}

void StateManager::reloadLevel() {
    // Temp to selection screen
    setStateType(3);
    changeState();
    load();
    // Change back to level state
    setStateType(1);
    changeState();
    load();
}

StateManager::~StateManager() {
    currentState.reset();
};

} // namespace GSTD