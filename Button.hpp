#pragma once

#include <cmath>
#include <functional>
#include <string>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Collision.hpp"
#include "Options.hpp"

////////////////////////////////////////////////////////////////////////////////
/// Represents an in-game button and can be drawn like any
/// other SFML shape. It can show a label in addition to just being a button.
///
/// @see IconButton
/// @see MainButton
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

    bool isPressed() const;      ///< Check whether or not this button is pressed. @see Button::pressed
    void setPressed(bool value); ///< Set the pressed state of this button. @see Button::pressed
    void press();                ///< Press this button, triggering the corresponding event handler. @see Button::onPress
    void release();              ///< Release this button, triggering the corresponding event handler. @see Button::onRelease
    void toggle();               ///< Toggle whether or not this button is pressed. @see Button::pressed

    Color getFillColor() const;       ///< Get the main fill color of this button. @see Button::shape
    void setFillColor(Color color);   ///< Set the main fill color of this button. @see Button::shape
    Color getShadowColor() const;     ///< Get the shadow color of this button. @see Button::shadowShape
    void setShadowColor(Color color); ///< Set the shadow color of this button. @see Button::shadowShape

    FloatRect getGlobalBounds();

    std::function<void()> onPress;   ///< An event handler. Triggers when this button is pressed.
    std::function<void()> onRelease; ///< An event handler. Triggers when this button is released.

    void handleEvent(Event& e, const Window& window); ///< Handle an event, or do nothing if not applicable.

protected:
    virtual void draw(RenderTarget& window, RenderStates states) const; ///< Draw this button to the screen.

    RectangleShape shape;       ///< The main body of the button.
    RectangleShape shadowShape; ///< The shadow of the button. Shown below the main body.
    Text label;                 ///< Represents the label on the button.

    void rewrapLabelText(); ///< Make sure that the label is centered properly.

private:
    bool pressed = false; ///< Whether or not this button is pressed.

    static Font labelFont;       ///< The font used for the label on the button.
    static Font initLabelFont(); ///< @see Button::labelFont

};
