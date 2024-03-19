#ifndef INC_2022_PROJECT_ORFEOTERKUCI_GAME_H
#define INC_2022_PROJECT_ORFEOTERKUCI_GAME_H

#include <memory>
#include "../logic_lib/World.h"
#include "../logic_lib/Camera.h"
#include "../logic_lib/Stopwatch.h"
#include "ConcreteFactory.h"

namespace GSTD {

class StateManager;

class Game {
private:

    static void setupWindow();
    static void setupLogic();

public:

    /**
     * Default constructor for object of Game class
     */
    Game() = default;

    /**
     * Launch the game
     */
    static void launch();

    virtual ~Game() = default;
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_GAME_H
