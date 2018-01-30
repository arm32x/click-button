/// @file MainButton.hpp

#pragma once

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "Options.hpp"

class MainButton : public Button {

public:
    MainButton(Vector2f position);

    void update();

    static double getScore();
    static void setScore(double value);
    static double getCps();
    static void setCps(double value);
    static long getPower();
    static void setPower(long value);

    FloatRect getGlobalBounds();

protected:
    virtual void draw(RenderTarget& window, RenderStates states) const;

    RectangleShape stand;
    RectangleShape standShadow;

private:
    using Button::Button;

    static Font labelFont;
    static Font initLabelFont();

    using Button::onPress;
    using Button::onRelease;

    static double score;
    static double cps;
    static long power;

    void updateScoreText();

};
