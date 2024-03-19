//
// Created by oterk on 16/11/2022.
//

#include "WallView.h"
#include "TextureManager.h"

namespace GSTD {

void WallView::handle() {

    if(!isInit()){
        setBlock(sf::Sprite(TextureManager::wallTexture , sf::IntRect(480 , 60 , 60 , 60)));
        setInit(true);
    }
    // Draw wall
    // Get coordinates
    auto s = getBlock();
    s.setPosition(getPositionX() , getPositionY());
    s.setScale(getWidth() / getBlock().getLocalBounds().width , getHeight() / getBlock().getLocalBounds().height);
    setBlock(s);
    // Scale the sprite

    GameWindow::getInstance().getGWindow()->draw(getBlock());
    }

} // namespace GSTD