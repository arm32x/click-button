/// @file IconButton.hpp

#pragma once

#include <functional>
#include <string>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Collision.hpp"
#include "Icons.hpp"
#include "Options.hpp"

////////////////////////////////////////////////////////////////////////////////
/// A circular transparent button with an icon on it. This class has no relation
/// to the `Button` class.
///
/// @see Button
////////////////////////////////////////////////////////////////////////////////
class IconButton : public Drawable {

public:
    IconButton(const Vector2f position, const bool mini, const std::string iconName);
    IconButton(const Vector2f position, const std::string iconName);

    /// @{
    /// Accessors for the pressed state of this button. @see IconButton::pressed
    bool isPressed() const;
    void setPressed(bool value);
    void press();
    void release();
    void toggle();
    /// @}

    Vector2f getPosition() const;
    void setPosition(const Vector2f value);
    void move(const Vector2f by);
    float getRadius() const;
    void setIcon(const std::string name);

    std::function<void()> onPress;
    std::function<void()> onRelease;

    void handleEvent(Event& e, Window& window);

protected:
    virtual void draw(RenderTarget& window, RenderStates states) const;

    CircleShape background;
    Sprite icon;

    bool pressed;

};

////////////////////////////////////////////////////////////////////////////////
/// @page miniIconButtons Mini icon buttons
/// Icon buttons can be mini-sized. Mini buttons have a smaller radius and thus
/// are smaller. The specific radii are defined in 'Options.hpp'.
///
/// @see IconButton
/// @see Options::IconButtonRadius
/// @see Options::MiniIconButtonRadius
////////////////////////////////////////////////////////////////////////////////
