/// @file IconButton.cpp

#include "IconButton.hpp"

/// @param position The center of the icon button.
/// @param mini     @see Options::MiniIconButtonRadius
/// @param iconName What icon to put on the button. @see Icons
IconButton::IconButton(const Vector2f position, const bool mini, const std::string iconName)
    : background(0.0f, 80) {
    // Set the proper radius on our icon button.
    if (!mini) {
        background.setRadius(Options::IconButtonRadius);
        background.setOrigin(Vector2f(Options::IconButtonRadius, Options::IconButtonRadius));
    } else {
        background.setRadius(Options::MiniIconButtonRadius);
        background.setOrigin(Vector2f(Options::MiniIconButtonRadius, Options::MiniIconButtonRadius));
    }
    background.setFillColor(Options::IconButtonColor);
    background.setOutlineThickness(Options::IconButtonBorderWidth);
    background.setOutlineColor(Options::IconButtonBorderColor);
    background.setPosition(position);

    if (iconName != "") {
        icon.setTexture(Icons::getTexture(iconName));
    } else {
        icon.setColor(Color(0xFF, 0xFF, 0xFF, 0.00 * 0xFF));
    }
    icon.setOrigin(Vector2f(12.0f, 12.0f));
    icon.setPosition(position);
}

/// @see IconButton::IconButton(const Vector2f, const bool, const std::string)
IconButton::IconButton(const Vector2f position, const std::string iconName)
    : IconButton(position, false, iconName) { }

bool IconButton::isPressed() const { return pressed; }
void IconButton::setPressed(bool value) { pressed = value; }
void IconButton::press() { if (onPress != nullptr) onPress(); setPressed(true); }
void IconButton::release() { if (isPressed() && onRelease != nullptr) onRelease(); setPressed(false); }
void IconButton::toggle() { setPressed(!isPressed()); }

Vector2f IconButton::getPosition() const { return background.getPosition(); }
void IconButton::setPosition(const Vector2f value) { background.setPosition(value); icon.setPosition(value); }
void IconButton::move(const Vector2f by) { setPosition(getPosition() + by); }
float IconButton::getRadius() const { return background.getRadius(); }
void IconButton::setIcon(const std::string name) { icon.setTexture(Icons::getTexture(name)); }


void IconButton::draw(RenderTarget& window, RenderStates states) const {
    window.draw(background);
    window.draw(icon);
}

void IconButton::handleEvent(Event& e, Window& window) {
    switch (e.type) {
        case Event::MouseButtonPressed:
            if (Collision::pointToCircle((Vector2f)Mouse::getPosition(window), getPosition(), getRadius())) {
                background.setFillColor(Options::ActiveIconButtonColor);
                press();
            }
            break;
        case Event::MouseButtonReleased:
            background.setFillColor(Options::IconButtonColor);
            release();
            break;
        default:
            break;
    }
}

