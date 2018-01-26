#include "Button.hpp"

Button::Button(const Vector2f position, const Vector2f size, const Color color, const Color shadowColor, const Color textColor, const std::string labelText) {
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
    rewrapLabelText();
}

Button::Button(const Vector2f position, const Vector2f size, const Color color, const Color shadowColor)
    : Button(position, size, color, shadowColor, Options::StandardButtonTextColor, "") { }
Button::Button(const Vector2f position, const Vector2f size, const std::string labelText)
    : Button(position, size, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, labelText) { }
Button::Button(const Vector2f position, const Vector2f size)
    : Button(position, size, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, "") { }
Button::Button(const Vector2f position, const Color color, const Color shadowColor, const Color textColor, const std::string labelText)
    : Button(position, Options::StandardButtonSize, color, shadowColor, textColor, labelText) { }
Button::Button(const Vector2f position, const Color color, const Color shadowColor)
    : Button(position, Options::StandardButtonSize, color, shadowColor, Options::StandardButtonTextColor, "") { }
Button::Button(const Vector2f position, const std::string labelText)
    : Button(position, Options::StandardButtonSize, Options::StandardButtonColor, Options::StandardButtonShadowColor, Options::StandardButtonTextColor, labelText) { }
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


FloatRect Button::getGlobalBounds() {
    return FloatRect(shape.getPosition().x, shape.getPosition().y, shape.getSize().x, shape.getSize().y + 5.0f);
}


void Button::handleEvent(Event& e, const Window& window) {
    switch (e.type) {
        case Event::MouseButtonPressed:
            if (e.mouseButton.button == Mouse::Left && Collision::pointToRect((Vector2f)Mouse::getPosition(window), getGlobalBounds())) {
                press();
            }
            break;
        case Event::MouseButtonReleased:
            release();
            break;
        default:
            break;
    }
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


void Button::rewrapLabelText() {
    FloatRect labelBounds = label.getLocalBounds();
    label.setOrigin(std::round(labelBounds.left + labelBounds.width  / 2.0f),
                    std::round(labelBounds.top  + labelBounds.height / 2.0f));
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
