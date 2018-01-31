/// @file MainButton.cpp

#include "MainButton.hpp"

double MainButton::score = 0;
double MainButton::cps = 0;
long MainButton::power = 1;
double MainButton::peakScore = 0;

MainButton::MainButton(Vector2f position)
    : Button(Vector2f(position + Vector2f(10.0f, 10.0f)), Vector2f(Options::MainButtonSize + Vector2f(-20.0f, -25.0f)), Options::MainButtonColor, Options::MainButtonShadowColor, Options::MainButtonTextColor, "0") {

    stand.setPosition(position);
    stand.setSize(Options::MainButtonSize + Vector2f(0.0f, -5.0f));
    stand.setFillColor(Options::StandardButtonColor);

    standShadow.setPosition(position + Vector2f(0.0f, 5.0f));
    standShadow.setSize(Options::MainButtonSize + Vector2f(0.0f, -5.0f));
    standShadow.setFillColor(Options::StandardButtonShadowColor);

    label.setFont(labelFont);
    label.setCharacterSize(Options::MainButtonTextSize);
    rewrapLabelText();

    onRelease = [this] () -> void {
        setScore(getScore() + getPower());
        updateScoreText();
    };
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

void MainButton::update() {
    score += cps / 60;
    updateScoreText();
}

double MainButton::getScore() { return score; }
void MainButton::setScore(double value) { score = value; }
double MainButton::getCps() { return cps; }
void MainButton::setCps(double value) { cps = value; }
long MainButton::getPower() { return power; }
void MainButton::setPower(long value) { power = value; }
double MainButton::getPeakScore() { return peakScore; }

/// Returns a rectangle representing the global bounds of this button. Global
/// bounds is a term used by SFML to represent a rectangle containing the X
/// and Y positions of a shape, along with its width and height.
///
/// @return The global bounds of this button.
FloatRect MainButton::getGlobalBounds() {
    return FloatRect(stand.getPosition().x, stand.getPosition().y, stand.getSize().x, stand.getSize().y + 5.0f);
}

Font MainButton::labelFont = MainButton::initLabelFont();
Font MainButton::initLabelFont() {
    Font labelFont;
    if (!labelFont.loadFromFile("res/Oswald-Regular.ttf")) {
        exit(1);
    }
    return labelFont;
}


void MainButton::updateScoreText() {
    label.setString(std::to_string((int)std::floor(getScore())));
    if (std::floor(getScore()) < 0) {
        label.setFillColor(Color(Options::MainButtonTextColor.r,
                                 Options::MainButtonTextColor.g,
                                 Options::MainButtonTextColor.b,
                                 0.35 * 0xFF));
    } else {
        label.setFillColor(Options::MainButtonTextColor);
    }
    if (getScore() > getPeakScore()) {
        peakScore = getScore();
    }
    rewrapLabelText();
}
