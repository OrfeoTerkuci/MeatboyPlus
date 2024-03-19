#include "GoalView.h"
#include "TextureManager.h"

namespace GSTD {

void GoalView::handle() {
    // Draw goal
    if(!isInit()){
        setBlock(sf::Sprite(TextureManager::goalTexture , sf::IntRect(480 , 540 , 60 , 60)));
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