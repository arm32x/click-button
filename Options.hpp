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

};
