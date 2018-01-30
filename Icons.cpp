/// @file Icons.cpp

#include "Icons.hpp"

std::map<const std::string, Texture> Icons::textures;

Texture& Icons::getTexture(const std::string iconName) {
    if (textures.count(iconName) < 1) {
        textures[iconName] = Texture();
        if (!textures[iconName].loadFromFile("res/icons/" + iconName + ".png")) {
            exit(1);
        }
    }
    return textures[iconName];
}

Sprite Icons::getSprite(const std::string iconName) {
    return Sprite(getTexture(iconName));
}
Sprite Icons::getSpriteAt(Vector2f position, const std::string iconName) {
    Sprite iconSprite = getSprite(iconName);
    iconSprite.setPosition(position);
    return iconSprite;
}
