#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

namespace Options {

    const std::vector<std::string> SplashTexts = {
        "Get points.",
        "Click button more. Click button even more.",
        "Lose time.",
        "Admire animations.",
        "Realize this is a Cookie Clicker clone.",
        "Get bored.",
        "Batteries not included.",
        "Buy stuff with points.",
        "Get wither."
    };

    const Color BackgroundColor = Color(0x21, 0x21, 0x2B);

    const        Color StandardButtonColor       = Color(0xCC, 0xCC, 0xCC);
    const        Color StandardButtonShadowColor = Color(0xAA, 0xAA, 0xAA);
    const        Color StandardButtonTextColor   = Color(0x21, 0x21, 0x21);
    const unsigned int StandardButtonTextSize    = 15;
    const     Vector2f StandardButtonSize        = Vector2f(180.0f, 41.0f);

    const        Color MainButtonColor       = Color(0xF0, 0x3A, 0x3A);
    const        Color MainButtonShadowColor = Color(0xC2, 0x2F, 0x2F);
    const        Color MainButtonTextColor   = Color(0xFA, 0xFA, 0xFA);
    const unsigned int MainButtonTextSize    = 45;
    const     Vector2f MainButtonSize        = Vector2f(275.0f, 150.0f);

    const Color DividerColor = Color(0xFF, 0xFF, 0xFF, 0.10 * 0xFF);

};
