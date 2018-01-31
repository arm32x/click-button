/// @file Icons.hpp

#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

////////////////////////////////////////////////////////////////////////////////
/// Allows for loading of icon images (stored in 'res/icons/') as Textures, and
/// optionally applying them to a sprite.
////////////////////////////////////////////////////////////////////////////////
namespace Icons {

    /// Stores all loaded textures, even ones that aren't currently being used.
    extern std::map<const std::string, Texture> textures;

    /// Get a texture, and load it if necessary.
    Texture& getTexture(const std::string iconName);

    Sprite getSprite(const std::string iconName);                      ///< Return a sprite with the given icon's Texture on it.
    Sprite getSpriteAt(Vector2f position, const std::string iconName); ///< Does the same as Icons::getSprite(), except at a position. @see Icons::getSprite()

};
