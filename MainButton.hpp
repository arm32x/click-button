#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "Options.hpp"

class MainButton : public Button {

public:
    MainButton(Vector2f position);

protected:
    virtual void draw(RenderTarget& window, RenderStates states) const;

    RectangleShape stand;
    RectangleShape standShadow;

private:
    using Button::Button;

    static Font labelFont;
    static Font initLabelFont();

};
