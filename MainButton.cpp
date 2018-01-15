#include "MainButton.hpp"

MainButton::MainButton(Vector2f position)
    : Button(Vector2f(position + Vector2f(10.0f, 10.0f)), Vector2f(Options::MainButtonSize + Vector2f(-20.0f, -25.0f)), Options::MainButtonColor, Options::MainButtonShadowColor, Options::MainButtonTextColor, "0") {

    stand.setPosition(position);
    stand.setSize(Options::MainButtonSize + Vector2f(0.0f, -5.0f));
    stand.setFillColor(Options::StandardButtonColor);

    standShadow.setPosition(position + Vector2f(0.0f, 5.0f));
    standShadow.setSize(Options::MainButtonSize + Vector2f(0.0f, -5.0f));
    standShadow.setFillColor(Options::StandardButtonShadowColor);

    label.setCharacterSize(Options::MainButtonTextSize);
    FloatRect labelBounds = label.getLocalBounds();
    label.setOrigin(labelBounds.left + labelBounds.width  / 2.0f,
                    labelBounds.top  + labelBounds.height / 2.0f);
    label.setPosition(shape.getPosition() + shape.getSize() / 2.0f);
}


void MainButton::draw(RenderTarget& window, RenderStates states) const {
    if (isPressed()) {
        window.draw(standShadow);
        window.draw(stand);
        window.draw(shadowShape);

        RectangleShape pressedShape(shape);
        pressedShape.move(Vector2f(0.0f, 3.0f));
        window.draw(pressedShape);

        Text pressedLabel(label);
        pressedLabel.move(Vector2f(0.0f, 3.0f));
        window.draw(pressedLabel);
    } else {
        window.draw(standShadow);
        window.draw(stand);
        window.draw(shadowShape);
        window.draw(shape);
        window.draw(label);
    }
}
