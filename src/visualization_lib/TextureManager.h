#ifndef INC_2022_PROJECT_ORFEOTERKUCI_TEXTUREMANAGER_H
#define INC_2022_PROJECT_ORFEOTERKUCI_TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>

namespace GSTD {

class LoadFail : public std::exception {
private:
    std::string error {};
public:
    /**
     * Constructor for LoadFail exception
     * @param error The error message
     */
    explicit LoadFail(std::string  error) : error(std::move(error)) {}

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return error.c_str();
    }

    ~LoadFail() override = default;
};

class TextureManager {
public:
    // Textures //
    static sf::Texture menuBackground;
    static sf::Texture levelBackground;
    static sf::Sprite menuBackgroundImage;
    static sf::Sprite levelBackgroundImage;
    static sf::Texture wallTexture;
    static sf::Texture playerTexture;
    static sf::Texture goalTexture;
    static sf::Texture levelArrow;
    // Fonts //
    static sf::Font buttonFont;

    //== Constructor ==//
    /**
     * Default constructor for TextureManager
     */
    TextureManager() = default;

    /**
     * Load all the required textures
     */
    static void loadTextures();

    virtual ~TextureManager() = default;
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_TEXTUREMANAGER_H
