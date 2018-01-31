/// @file EnemyExplosion.hpp

#pragma once

#include <functional>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "IconButton.hpp"

////////////////////////////////////////////////////////////////////////////////
/// A visual effect that is created when an enemy is destroyed.
////////////////////////////////////////////////////////////////////////////////
class EnemyExplosion : public IconButton {

public:
    EnemyExplosion(Vector2f position);

    static std::function<void(EnemyExplosion* explosion)> destroy;

    /// A list of animation frames to display.
    static std::vector<std::pair<float, float>> frames;
    short currentFrame = 0;

    void update();

private:
    using IconButton::onPress;
    using IconButton::onRelease;

    using IconButton::handleEvent;

};
