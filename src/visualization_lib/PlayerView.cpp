#include "PlayerView.h"
#include "TextureManager.h"

namespace GSTD {

void PlayerView::handle() {
    //     300 x 311 , 90 x 86 texture coordinates
    // Draw player
    if(!isInit()){
        setBlock(sf::Sprite(TextureManager::playerTexture , sf::IntRect(300 , 311 , 90 , 76)));
        setInit(true);
    }
    // Draw wall
    // Get coordinates
    auto s = getBlock();
    s.setPosition(getPositionX() , getPositionY());
    s.setScale(getWidth() / getBlock().getLocalBounds().width , getHeight() / getBlock().getLocalBounds().height);
    setBlock(s);
    GameWindow::getInstance().getGWindow()->draw(getBlock());
}

} // namespace GSTD