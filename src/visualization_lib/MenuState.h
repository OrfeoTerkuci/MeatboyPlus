#ifndef INC_2022_PROJECT_ORFEOTERKUCI_MENUSTATE_H
#define INC_2022_PROJECT_ORFEOTERKUCI_MENUSTATE_H
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace GSTD {

class MenuState : public State {

public:
    // Public Static window items
    static sf::Text playButton;
    static sf::Text levelsButton;

    MenuState() = default;
    void draw() override;
    void keyHandle(const sf::Keyboard::Key& key) override;
    void mouseMoveHandle() override;
    void mouseClickHandle(const sf::Mouse::Button& mouseButton) override;
    void lost() override {}
    void load() override;
    void won() override {}

    ~MenuState() override = default;
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_MENUSTATE_H
