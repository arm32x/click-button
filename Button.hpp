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
    Button(const Vector2f position, const Vector2f size, const Color color, const Color shadowColor, const Color textColor, const std::string labelText);
    Button(const Vector2f position, const Vector2f size, const Color color, const Color shadowColor);
    Button(const Vector2f position, const Vector2f size, const std::string labelText);
    Button(const Vector2f position, const Vector2f size);
    Button(const Vector2f position, const Color color, const Color shadowColor, const Color textColor, const std::string labelText);
    Button(const Vector2f position, const Color color, const Color shadowColor);
    Button(const Vector2f position, const std::string labelText);
    Button(const Vector2f position);

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
