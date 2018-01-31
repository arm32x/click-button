/// @file MainButton.hpp

#pragma once

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "Options.hpp"

////////////////////////////////////////////////////////////////////////////////
/// This class is the main button. The one that you click on to get points?
////////////////////////////////////////////////////////////////////////////////
class MainButton : public Button {

public:
    MainButton(Vector2f position);

    void update(); ///< Update the main button so we can apply CPS.

    // Various score 'n' stuff getters and setters
    static double getScore();
    static void setScore(double value);
    static double getCps();
    static void setCps(double value);
    static long getPower();
    static void setPower(long value);
    static int getShieldFrames();
    static void setShieldFrames(int value);
    static double getPeakScore();

    FloatRect getGlobalBounds();
    FloatRect getShieldBounds();

protected:
    virtual void draw(RenderTarget& window, RenderStates states) const;

    RectangleShape stand;
    RectangleShape standShadow;
    RectangleShape shield;

private:
    using Button::Button;

    static Font labelFont;
    static Font initLabelFont();

    using Button::onPress;
    using Button::onRelease;

    static double score;      ///< The score, displayed on the button.
    static double cps;        ///< The number of points to add per second.
    static long power;        ///< How many points clicking the button gives you.
    static double peakScore;  ///< The total number of points that have been accumulated.
    static int shieldFrames;  ///< The number of frames that the shield will remain up.

    void updateScoreText(); ///< Make sure the score text is properly centered.

};
