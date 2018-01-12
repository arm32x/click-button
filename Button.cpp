#include "Button.hpp"

Button::Button(Vector2f position, Vector2f size, Color color, Color shadowColor, Color textColor, std::string labelText) {

    shape.setPosition(position);
    shape.setSize(size + Vector2f(0.0f, -5.0f));
    shape.setFillColor(color);

    shadowShape.setPosition(position + Vector2f(0.0f, 5.0f));
    shadowShape.setSize(size + Vector2f(0.0f, -5.0f));
    shadowShape.setFillColor(shadowColor);

    label.setFont(labelFont);
    label.setCharacterSize(Options::StandardButtonTextSize);
    label.setFillColor(textColor);
    label.setString(labelText);
    FloatRect labelBounds = label.getLocalBounds();
    label.setOrigin(labelBounds.left + labelBounds.width  / 2.0f,
                    labelBounds.top  + labelBounds.height / 2.0f);
    label.setPosition(shape.getPosition() + shape.getSize() / 2.0f);
}

Button::Button(Vector2f position, Vector2f size, Color color, Color shadowColor)
    : Button(position, size, color, shadowColor, Options::StandardButtonTextColor, "") { }
Button::Button(Vector2f position, Vector2f size, std::string labelText)
    : Button(position, size, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, labelText) { }
Button::Button(Vector2f position, Vector2f size)
    : Button(position, size, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, "") { }
Button::Button(Vector2f position, Color color, Color shadowColor, Color textColor, std::string labelText)
    : Button(position, Options::StandardButtonSize, color, shadowColor, textColor, labelText) { }
Button::Button(Vector2f position, Color color, Color shadowColor)
    : Button(position, Options::StandardButtonSize, color, shadowColor, Options::StandardButtonTextColor, "") { }
Button::Button(Vector2f position, std::string labelText)
    : Button(position, Options::StandardButtonSize, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, labelText) { }
Button::Button(Vector2f position)
    : Button(position, Options::StandardButtonSize, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, "") { }


bool Button::isPressed() const { return pressed; }
void Button::setPressed(bool value) { pressed = value; }
void Button::press() { setPressed(true); }
void Button::release() { setPressed(false); }
void Button::toggle() { setPressed(!isPressed()); }


FloatRect Button::getGlobalBounds() {
    return FloatRect(shape.getPosition().x, shape.getPosition().y, shape.getSize().x, shape.getSize().y + 5.0f);
}


void Button::draw(RenderTarget& window, RenderStates states) const {
    if (isPressed()) {
        window.draw(shadowShape);

        RectangleShape pressedShape(shape);
        pressedShape.move(Vector2f(0.0f, 3.0f));
        window.draw(pressedShape);

        Text pressedLabel(label);
        pressedLabel.move(Vector2f(0.0f, 3.0f));
        window.draw(pressedLabel);
    } else {
        window.draw(shadowShape);
        window.draw(shape);
        window.draw(label);
    }
}


Font Button::labelFont = Button::initLabelFont();
Font Button::initLabelFont() {
    Font labelFont;
    if (!labelFont.loadFromFile("res/RobotoCondensed-Regular.ttf")) {
        exit(1);
    }
    return labelFont;
}
