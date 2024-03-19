#include "EntityView.h"

namespace GSTD {

void EntityView::update(double posX, double posY, double newWidth, double newHeight) {
    // Update position
    setPositionX ( (posX + 1) / 2 * (GameWindow::getInstance().getGWindow()->getSize().x - 1) );
    setPositionY( (GameWindow::getInstance().getGWindow()->getSize().y) * (1 - ((posY + 1) / 10) ) );
    setWidth((newWidth / 2) * (GameWindow::getInstance().getGWindow()->getSize().x - 1));
    setHeight((newHeight / 10) * (GameWindow::getInstance().getGWindow()->getSize().y));
}

} // namespace GSTD