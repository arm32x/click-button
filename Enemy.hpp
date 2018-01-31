/// @file Enemy.hpp

#pragma once

#include <cmath>
#include <functional>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "Collision.hpp"
#include "IconButton.hpp"
#include "MainButton.hpp"
#include "Random.hpp"

////////////////////////////////////////////////////////////////////////////////
/// Enemies are... well... enemies.
///
/// Enemies will come at you from all sides, and attack the main button. If they
/// touch the button, you will lose points. They will get progressively more
/// frequent and will deduct more points as you accumulate more total points.
///
/// To create an enemy, call the constructor like a function. This will create
/// an enemy in the enemies `std::vector`.
////////////////////////////////////////////////////////////////////////////////
class Enemy : public IconButton {

public:
    Enemy(const Vector2f position, long attack);
    Enemy(long attack);

    static std::function<void(Enemy* enemy)> destroy;

    Vector2f getSpawnPosition();

    void update(MainButton& mainButton);
    using IconButton::handleEvent;

protected:
    virtual void draw(RenderTarget& window, RenderStates states) const;

    Text attackLabel;

    long attack; ///< How much damage this enemy will do when it hits the main button.

    static Font attackFont;
    static Font initAttackFont();

    void rewrapLabelText();

private:
    using IconButton::icon; // This is to prevent an icon from being added to an enemy.

    using IconButton::onPress;
    using IconButton::onRelease;

};
