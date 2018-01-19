#pragma once

#include <string>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "Options.hpp"

class MainButton : public Button {

public:
    MainButton(Vector2f position);

    void update();

    static long getScore();
    static void increaseCps(long by);
    static void increasePower(long by);

protected:
    virtual void draw(RenderTarget& window, RenderStates states) const;

    RectangleShape stand;
    RectangleShape standShadow;

    void onRelease();

private:
    using Button::Button;

    static Font labelFont;
    static Font initLabelFont();

    static long score;
    static long cps;
    static long power;

};
