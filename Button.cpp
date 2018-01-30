/// @file Button.cpp

#include "Button.hpp"

/// @param position    The top-left corner of the button.
/// @param size        The size of the button.
/// @param color       The main color of the button. @see Button::shape
/// @param shadowColor The shadow color of the button. @see Button::shadowShape
/// @param textColor   The color of the label. @see Button::label
/// @param labelText   The text to show on the button. @see Button::label
Button::Button(const Vector2f position, const Vector2f size, const Color color, const Color shadowColor, const Color textColor, const std::string labelText) {
    shape.setPosition(position);
    // We want the main shape to be shorter to make room for the shadow.
    shape.setSize(size + Vector2f(0.0f, -5.0f));
    shape.setFillColor(color);

    // Move the shadow down a bit to make it visible under the main shape.
    shadowShape.setPosition(position + Vector2f(0.0f, 5.0f));
    // Decrease its height so it doesn't show when the button is pressed.
    shadowShape.setSize(size + Vector2f(0.0f, -5.0f));
    shadowShape.setFillColor(shadowColor);

    label.setFont(labelFont);
    label.setCharacterSize(Options::StandardButtonTextSize);
    label.setFillColor(textColor);
    label.setString(labelText);
    rewrapLabelText(); // Make sure that the label is centered.
}


/// @param position    The top-left corner of the button.
/// @param size        The size of the button.
/// @param color       The main color of the button. @see Button::shape
/// @param shadowColor The shadow color of the button. @see Button::shadowShape
Button::Button(const Vector2f position, const Vector2f size, const Color color, const Color shadowColor)
    : Button(position, size, color, shadowColor, Options::StandardButtonTextColor, "") { }
/// @param position    The top-left corner of the button.
/// @param size        The size of the button.
/// @param labelText   The text to show on the button. @see Button::label
Button::Button(const Vector2f position, const Vector2f size, const std::string labelText)
    : Button(position, size, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, labelText) { }
/// @param position    The top-left corner of the button.
/// @param size        The size of the button.
Button::Button(const Vector2f position, const Vector2f size)
    : Button(position, size, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, "") { }
/// @param position    The top-left corner of the button.
/// @param color       The main color of the button. @see Button::shape
/// @param shadowColor The shadow color of the button. @see Button::shadowShape
/// @param textColor   The color of the label. @see Button::label
/// @param labelText   The text to show on the button. @see Button::label
Button::Button(const Vector2f position, const Color color, const Color shadowColor, const Color textColor, const std::string labelText)
    : Button(position, Options::StandardButtonSize, color, shadowColor, textColor, labelText) { }
/// @param position    The top-left corner of the button.
/// @param color       The main color of the button. @see Button::shape
/// @param shadowColor The shadow color of the button. @see Button::shadowShape
Button::Button(const Vector2f position, const Color color, const Color shadowColor)
    : Button(position, Options::StandardButtonSize, color, shadowColor, Options::StandardButtonTextColor, "") { }
/// @param position    The top-left corner of the button.
/// @param labelText   The text to show on the button. @see Button::label
Button::Button(const Vector2f position, const std::string labelText)
    : Button(position, Options::StandardButtonSize, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, labelText) { }
/// @param position    The top-left corner of the button.
Button::Button(const Vector2f position)
    : Button(position, Options::StandardButtonSize, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, "") { }


bool Button::isPressed() const { return pressed; }
void Button::setPressed(bool value) { pressed = value; }
void Button::press() { if (onPress != nullptr) onPress(); setPressed(true); }
void Button::release() { if (isPressed() && onRelease != nullptr) onRelease(); setPressed(false); }
void Button::toggle() { setPressed(!isPressed()); }


Color Button::getFillColor() const { return shape.getFillColor(); }
void Button::setFillColor(Color color) { shape.setFillColor(color); }
Color Button::getShadowColor() const { return shadowShape.getFillColor(); }
void Button::setShadowColor(Color color) { shadowShape.setFillColor(color); }


/// Returns a rectangle representing the global bounds of this button. Global
/// bounds is a term used by SFML to represent a rectangle containing the X
/// and Y positions of a shape, along with its width and height.
///
/// @return The global bounds of this button.
FloatRect Button::getGlobalBounds() {
    return FloatRect(shape.getPosition().x, shape.getPosition().y, shape.getSize().x, shape.getSize().y + 5.0f);
}


void Button::draw(RenderTarget& window, RenderStates states) const {
    if (isPressed()) {
        // The shadow shape stays stationary. We want it to look as if the
        // button is pressed into the background.
        window.draw(shadowShape);

        // Move the main shape down a bit because the button is pressed.
        RectangleShape pressedShape(shape);
        pressedShape.move(Vector2f(0.0f, 3.0f));
        window.draw(pressedShape);

        // Do the same to the label.
        Text pressedLabel(label);
        pressedLabel.move(Vector2f(0.0f, 3.0f));
        window.draw(pressedLabel);
    } else {
        // Draw the button normally.
        window.draw(shadowShape);
        window.draw(shape);
        window.draw(label);
    }
}

void Button::handleEvent(Event& e, const Window& window) {
    switch (e.type) {
        case Event::MouseButtonPressed:
            // Check to make sure we actually clicked the button.
            if (e.mouseButton.button == Mouse::Left && Collision::pointToRect((Vector2f)Mouse::getPosition(window), Button::getGlobalBounds())) {
                // Set the button to display as pressed and trigger the
                // `onPress` event handler.
                press();
            }
            break;
        case Event::MouseButtonReleased:
            // Stop the button from displaying as pressed. This only triggers
            // the `onRelease` event handler if the button was actually pressed
            // before this was called.
            release();
            break;
        default:
            break;
    }
}


void Button::rewrapLabelText() {
    // Get the local bounds of the text. Local bounds is a term used by SFML to
    // represent a rectangle that contains all of the text and nothing more.
    // The X and Y positions of this rectangle are relative to the text's
    // current position.
    FloatRect labelBounds = label.getLocalBounds();
    // Set the origin of the text to the center, and round it to make sure the
    // text isn't blurry.
    label.setOrigin(std::round(labelBounds.left + labelBounds.width  / 2.0f),
                    std::round(labelBounds.top  + labelBounds.height / 2.0f));
    // Center the text within the button.
    label.setPosition(Vector2f(std::round(shape.getPosition().x + shape.getSize().x / 2.0f),
                               std::round(shape.getPosition().y + shape.getSize().y / 2.0f)));
}


Font Button::labelFont = Button::initLabelFont();
Font Button::initLabelFont() {
    Font labelFont;
    if (!labelFont.loadFromFile("res/Oswald-Regular.ttf")) {
        exit(1);
    }
    return labelFont;
}
