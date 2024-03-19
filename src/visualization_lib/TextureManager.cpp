#include "TextureManager.h"
#include "GameWindow.h"
#include <iostream>

namespace GSTD {

sf::Texture TextureManager::menuBackground = sf::Texture();
sf::Texture TextureManager::levelBackground = sf::Texture();
sf::Texture TextureManager::levelArrow = sf::Texture();
sf::Sprite TextureManager::menuBackgroundImage = sf::Sprite();
sf::Sprite TextureManager::levelBackgroundImage = sf::Sprite();
    sf::Font TextureManager::buttonFont = sf::Font();
sf::Texture TextureManager::wallTexture = sf::Texture();
sf::Texture TextureManager::playerTexture = sf::Texture();
sf::Texture TextureManager::goalTexture = sf::Texture();

void TextureManager::loadTextures() {
    try {
        // Load all the textures
        if (!GSTD::TextureManager::menuBackground.loadFromFile("../resources/pc/LevelPalettes/retro3intro.png"))
        {
            // error...
            throw LoadFail("Failed to load menuBackground texture image");
        }
        if (!GSTD::TextureManager::levelBackground.loadFromFile("../resources/pc/LevelPalettes/hospitalbg.png"))
        {
            // error...
            throw LoadFail("Failed to load levelBackground texture image");
        }
        if (!buttonFont.loadFromFile("../resources/Fonts/Pixellettersfull-BnJ5.ttf"))
        {
            throw LoadFail("Failed to load font");
        }
        if (!wallTexture.loadFromFile("../resources/pc/LevelPalettes/hospitaltiles01.png"))
        {
            throw LoadFail("Failed to load font");
        }
        if (!playerTexture.loadFromFile("../resources/pc/Animations/ogmo.png"))
        {
            throw LoadFail("Failed to load font");
        }
        if (!goalTexture.loadFromFile("../resources/pc/LevelPalettes/hospitaltiles01.png"))
        {
            throw LoadFail("Failed to load font");
        }
        if (!levelArrow.loadFromFile("../resources/pc/HUD/meathuds.png"))
        {
            // error...
            throw LoadFail("Failed to load levelArrow texture image");
        }

    } catch (LoadFail& i) {
        std::cout << i.what() << std::endl;
    }

    // Texture properties
    GSTD::TextureManager::menuBackground.setSmooth(true);
    GSTD::TextureManager::levelBackground.setSmooth(true);
    GSTD::TextureManager::levelArrow.setSmooth(true);
    // Rescale textures
    double scaleX = (double) GameWindow::getInstance().getWidth() / (menuBackground.getSize().x - 33);
    double scaleY = (double) GameWindow::getInstance().getHeight() / (menuBackground.getSize().y - 33);
    // Upscale sprites
    menuBackgroundImage.setScale(scaleX , scaleY);
    scaleX = (double) GameWindow::getInstance().getWidth() / (levelBackground.getSize().x);
    scaleY = (double) GameWindow::getInstance().getHeight() / (levelBackground.getSize().y);
    levelBackgroundImage.setScale(scaleX , scaleY);

    // Load textures to sprites
    GSTD::TextureManager::menuBackgroundImage.setTexture(GSTD::TextureManager::menuBackground);
    GSTD::TextureManager::levelBackgroundImage.setTexture(GSTD::TextureManager::levelBackground);

}

} // namespace GSTD