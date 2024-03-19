cmake_minimum_required(VERSION 3.16)

project(MeatboyPlus VERSION 1.0 DESCRIPTION "Meatboy")

set(CMAKE_CXX_FLAGS_INIT "-Werror -Wall -Wextra -Wpedantic")

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_subdirectory(src/logic_lib)
add_subdirectory(src/visualization_lib)

# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

set(subject_libs
        src/logic_lib/Subject.cpp src/logic_lib/Subject.h
        src/logic_lib/EntityModel.cpp src/logic_lib/EntityModel.h
        src/logic_lib/Player.cpp src/logic_lib/Player.h
        src/logic_lib/Wall.cpp src/logic_lib/Wall.h
        src/logic_lib/Goal.cpp src/logic_lib/Goal.h
        )

set(logic_src
#        src/logic_lib/Camera.cpp src/logic_lib/Camera.h
#        src/logic_lib/Observer.cpp src/logic_lib/Observer.h
#        src/logic_lib/Score.cpp src/logic_lib/Score.h
#        src/logic_lib/World.cpp src/logic_lib/World.h
#        src/logic_lib/Stopwatch.cpp src/logic_lib/Stopwatch.h
#        ${subject_libs}
#        src/logic_lib/Camera.cpp src/logic_lib/Camera.h
#        src/logic_lib/AbstractFactory.cpp src/logic_lib/AbstractFactory.h
#        src/logic_lib/StandardValues.h
        )

set(entity_libs
        src/visualization_lib/EntityView.cpp src/visualization_lib/EntityView.h
        src/visualization_lib/PlayerView.cpp src/visualization_lib/PlayerView.h
        src/visualization_lib/WallView.cpp src/visualization_lib/WallView.h
        src/visualization_lib/GoalView.cpp src/visualization_lib/GoalView.h
        )

set(state_libs
        src/visualization_lib/State.cpp src/visualization_lib/State.h
        src/visualization_lib/MenuState.cpp src/visualization_lib/MenuState.h
        src/visualization_lib/LevelState.cpp src/visualization_lib/LevelState.h
        src/visualization_lib/SelectionState.cpp src/visualization_lib/SelectionState.h)

set(Concrete_factories
        src/visualization_lib/ConcreteFactory.cpp src/visualization_lib/ConcreteFactory.h
        )

set(Managers
        src/visualization_lib/StateManager.cpp src/visualization_lib/StateManager.h
        src/visualization_lib/TextureManager.cpp src/visualization_lib/TextureManager.h
        )

set(Game_libs
        src/visualization_lib/Game.cpp src/visualization_lib/Game.h
        src/visualization_lib/GameWindow.cpp src/visualization_lib/GameWindow.h
        )

set(visual_src
        ${Game_libs}
        ${Concrete_factories}
        ${state_libs}
        ${entity_libs}
        ${Managers}
        )

add_executable(debug_main
        ${logic_src}
        ${visual_src}
        main.cpp
        )

add_executable(release_main
        ${logic_src}
        ${visual_src}
        main.cpp
        )

# Link target to SFML libs
TARGET_LINK_LIBRARIES(debug_main sfml-system sfml-graphics sfml-window)
TARGET_LINK_LIBRARIES(debug_main logic_lib)
TARGET_LINK_LIBRARIES(debug_main visualization_lib)
TARGET_LINK_LIBRARIES(release_main sfml-system sfml-graphics sfml-window)
TARGET_LINK_LIBRARIES(release_main logic_lib)
TARGET_LINK_LIBRARIES(release_main visualization_lib)

# Install our executable to the CMAKE_INSTALL_PREFIX/bin
INSTALL(TARGETS debug_main DESTINATION bin)
INSTALL(TARGETS release_main DESTINATION bin)

IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF()

