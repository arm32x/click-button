#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

namespace Options {

    const VideoMode ScreenSize = VideoMode(854, 480);

    const std::vector<std::string> SplashTexts = {
        "Get credits.",
        "Click button more. Click button even more.",
        "Lose time."
    };

    const Color BackgroundColor = Color(0x21, 0x21, 0x2B);

    const        Color StandardButtonColor       = Color(0xCC, 0xCC, 0xCC);
    const        Color StandardButtonShadowColor = Color(0xAA, 0xAA, 0xAA);
    const        Color StandardButtonTextColor   = Color(0x21, 0x21, 0x21);
    const unsigned int StandardButtonTextSize    = 16;
    const     Vector2f StandardButtonSize        = Vector2f(180.0f, 41.0f);

};