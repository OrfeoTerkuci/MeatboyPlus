//
// Created by oterk on 29/12/2022.
//

#ifndef INC_2022_PROJECT_ORFEOTERKUCI_SELECTIONSTATE_H
#define INC_2022_PROJECT_ORFEOTERKUCI_SELECTIONSTATE_H
#include "State.h"
#include <string>
#include <iostream>
#include <dirent.h>

namespace GSTD {
class ExitFailure : public std::exception {
private:
    std::string error {};
public:
    explicit ExitFailure(std::string  error) : error(std::move(error)) {}
    ExitFailure(const ExitFailure& ref) noexcept : error(ref.error) {}
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return error.c_str();
    }
    ~ExitFailure() override = default;
};

class SelectionState : public State {
private:
    static bool loaded;
    static void loadLevels();
public:
    // Sprites and text elements
    static std::vector<std::string> levelButtons;
    static sf::Text button;
    static sf::Sprite leftArrow;
    static sf::Sprite rightArrow;

    //== Constructor ==//

    /**
     * Default constructor for object of type SelectionState
     */
    SelectionState() = default;

    void draw() override;
    void keyHandle(const sf::Keyboard::Key& key) override;
    void mouseMoveHandle() override;
    void mouseClickHandle(const sf::Mouse::Button& mouseButton) override;
    void lost() override {}; // Selection screen has no lost function
    void load() override;
    void won() override;

    ~SelectionState() override = default;
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_SELECTIONSTATE_H
