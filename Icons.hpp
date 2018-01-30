/// @file Icons.hpp

#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

namespace Icons {

    extern std::map<const std::string, Texture> textures;

    Texture& getTexture(const std::string iconName);

    Sprite getSprite(const std::string iconName);
    Sprite getSpriteAt(Vector2f position, const std::string iconName);

};
