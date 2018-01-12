#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Options.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief A class to represent a button in the game.
///
/// The Button class represents an in-game button and can be drawn like any
/// other SFML shape. It can show a label in addition to just being a button.
///
/// Mouse clicks are not handled by this class, it is purely for display. The
/// 'pressed' state can be set through various functions.
////////////////////////////////////////////////////////////////////////////////
class Button : public Drawable {

public:
    Button(Vector2f position, Vector2f size, Color color, Color shadowColor, Color textColor, std::string labelText);
    Button(Vector2f position, Vector2f size, Color color, Color shadowColor);
    Button(Vector2f position, Vector2f size, std::string labelText);
    Button(Vector2f position, Vector2f size);
    Button(Vector2f position, Color color, Color shadowColor, Color textColor, std::string labelText);
    Button(Vector2f position, Color color, Color shadowColor);
    Button(Vector2f position, std::string labelText);
    Button(Vector2f position);

    bool isPressed() const;
    void setPressed(bool value);
    void press();
    void release();
    void toggle();

    FloatRect getGlobalBounds();

protected:
    virtual void draw(RenderTarget& window, RenderStates states) const;

    RectangleShape shape;
    RectangleShape shadowShape;
    Text label;

    static Font labelFont;
    static Font initLabelFont();

private:
    bool pressed = false;

};
