add_library(logic_lib
        AbstractFactory.cpp
        Camera.cpp
        EntityModel.cpp
        Goal.cpp
        Player.cpp
        Wall.cpp
        json.hpp
        Observer.cpp
        Stopwatch.cpp
        Subject.cpp
        World.cpp
        StandardValues.h)

set_target_properties(logic_lib PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(logic_lib PROPERTIES SOVERSION 1)

include(GNUInstallDirs)

install(TARGETS logic_lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})