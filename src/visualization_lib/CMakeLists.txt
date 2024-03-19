add_library(visualization_lib
        ConcreteFactory.cpp
        EntityView.cpp
        Game.cpp
        GameWindow.cpp
        GoalView.cpp
        LevelState.cpp
        MenuState.cpp
        PlayerView.cpp
        SelectionState.cpp
        State.cpp
        StateManager.cpp
        TextureManager.cpp
        WallView.cpp
        )

set_target_properties(visualization_lib PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(visualization_lib PROPERTIES SOVERSION 1)

include(GNUInstallDirs)

install(TARGETS visualization_lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})