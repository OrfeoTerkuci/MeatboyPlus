#include "GameWindow.h"
#include "TextureManager.h"

#include <memory>

namespace GSTD {

GameWindow::GameWindow() {
    gWindow = std::make_unique<RenderWindow>(sf::VideoMode(1080 , 720),
                                             "Game Window" ,
                                             sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close);

    gWindow->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - gWindow->getSize().x/2,
                                            sf::VideoMode::getDesktopMode().height - gWindow->getSize().y * 1.25));

    gWindow->getSize();

    }

}


 // namespace GSTD