/// @file Options.hpp

#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

////////////////////////////////////////////////////////////////////////////////
/// A namespace to keep track of various configuration options for the game.
////////////////////////////////////////////////////////////////////////////////
namespace Options {

    /// A list of splash texts that will be randomly shown in the game.
    const std::vector<std::string> SplashTexts = {
        "Get points.",
        "Click button more. Click button even more.",
        "Lose time.",
        "Admire animations.",
        "Realize this is a Cookie Clicker clone.",
        "Get bored.",
        "Batteries not included.",
        "Get wither.",
        "Waste time."
    };

    const Color BackgroundColor = Color(0x21, 0x21, 0x2B); ///< The background color of the main window.

    const        Color StandardButtonColor       = Color(0xCC, 0xCC, 0xCC); ///< The color of a standard button.
    const        Color StandardButtonShadowColor = Color(0xAA, 0xAA, 0xAA); ///< The shadow color of a standard button.
    const        Color StandardButtonTextColor   = Color(0x21, 0x21, 0x21); ///< The text color of a standard button.
    const unsigned int StandardButtonTextSize    = 15;                      ///< The text size of a standard button.
    const     Vector2f StandardButtonSize        = Vector2f(180.0f, 41.0f); ///< The size of a standard button.

    const        Color DisabledButtonColor       = Color(0x88, 0x88, 0x88); ///< The color of a disabled standard button.
    const        Color DisabledButtonShadowColor = Color(0x66, 0x66, 0x66); ///< The shadow color of a disabled standard button.

    const        Color MainButtonColor       = Color(0xF0, 0x3A, 0x3A);  ///< The color of the main button.
    const        Color MainButtonShadowColor = Color(0xC2, 0x2F, 0x2F);  ///< The shadow color of the main button.
    const        Color MainButtonTextColor   = Color(0xFA, 0xFA, 0xFA);  ///< The text color of the main button.
    const unsigned int MainButtonTextSize    = 45;                       ///< The text size of the main button.
    const     Vector2f MainButtonSize        = Vector2f(275.0f, 150.0f); ///< The size of the main button.

    const Color DividerColor = Color(0xFF, 0xFF, 0xFF, 0.10 * 0xFF); ///< The color of dividers.
    const float ShadeOpacity = 0.65 * 0xFF;                          ///< How opaque should shades (semi-transparent covers) be?

    const float IconButtonRadius      = 20.0f;                                ///< The radius of a normal icon button.
    const float MiniIconButtonRadius  = 16.0f;                                ///< The radius of a mini icon button.
    const Color IconButtonColor       = Color(0xFF, 0xFF, 0xFF, 0.00 * 0xFF); ///< The background color of an icon button.
    const Color ActiveIconButtonColor = Color(0xFF, 0xFF, 0xFF, 0.05 * 0xFF); ///< The background color of a pressed icon button.
    const float IconButtonBorderWidth = 1.0f;                                 ///< The border width of an icon button.
    const Color IconButtonBorderColor = Options::DividerColor;                ///< The border color of an icon button.

    const float EnemySpawnMargin         = -20.0f; ///< How close to the edge an enemy will spawn. Negative numbers are offscreen. @see Enemy::getSpawnPosition()
    const float EnemyAttackLabelTextSize = 11.0f;  ///< The font size for the small label on an enemy.
    const float EnemySpeed               = 1.0f;   ///< The speed of the enemy, in pixels per frame.

    const float ShopPriceHikeRate = 1.35f; ///< How much to increase the price of a shop item by after it is bought. @see ShopItem

    const  long ScoreGoal         = 10000; ///< When enemy spawn rates will stop increasing.
    const float MinEnemySpawnRate = 0.2f;  ///< The slowest enemies can spawn, in enemies per second.
    const float MaxEnemySpawnRate = 10.0f; ///< The fastest enemies can spawn, in enemies per second.

};
