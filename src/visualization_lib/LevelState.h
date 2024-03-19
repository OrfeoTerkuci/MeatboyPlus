#ifndef INC_2022_PROJECT_ORFEOTERKUCI_LEVELSTATE_H
#define INC_2022_PROJECT_ORFEOTERKUCI_LEVELSTATE_H
#include "State.h"
namespace GSTD {

class LevelState : public State {
public:
    /**
     * Default constructor for object of LevelState type
     */
    LevelState() = default;

    void draw() override;
    void mouseMoveHandle() override {} // No mouse usage in level
    void keyHandle(const sf::Keyboard::Key& key) override;
    void mouseClickHandle(const sf::Mouse::Button& mouseButton) override {}
    void lost() override;
    void won() override;
    void load() override;

    ~LevelState() override = default;
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_LEVELSTATE_H
