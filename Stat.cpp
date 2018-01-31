/// @file Stat.cpp

#include "Stat.hpp"

Stat::Stat(const int index, const std::string name, const std::string description) {
    title.setPosition(getCoordsWithIndex(index, Vector2f(0.0f, 5.0f)));
    title.setFont(titleFont);
    title.setCharacterSize(18);
    title.setString(name);

    descriptionLabel.setPosition(getCoordsWithIndex(index, Vector2f(0.0f, 28.0f)));
    descriptionLabel.setFont(descriptionFont);
    descriptionLabel.setCharacterSize(14);
    descriptionLabel.setString(description);

    valueLabel.setPosition(getCoordsWithIndex(index, Vector2f(338.0f, 5.0f)));
    valueLabel.setFont(valueFont);
    valueLabel.setCharacterSize(18);
    valueLabel.setString("");

    rewrapText();
}


/// Takes in an index and a position, and outputs another position.
///
/// @param index    The index of this shop item. 0 is the first, 1 is the
///                 second, and so on.
/// @param position A position relative to the top-left corner of the shop item.
/// @return An absolute position representing where the item should be in the
///         game.
Vector2f Stat::getCoordsWithIndex(const int index, const Vector2f position) {
    return Vector2f(position.x + 496.0f, position.y + 56.0f * index + 80.0f);
}


void Stat::draw(RenderTarget& window, RenderStates states) const {
    window.draw(descriptionLabel);
    window.draw(title);
    window.draw(valueLabel);
}

void Stat::update(std::string newValue) {
    value = newValue;
    valueLabel.setString(newValue);
    rewrapText();
}


void Stat::rewrapText() {
    FloatRect valueLabelBounds = valueLabel.getLocalBounds();
    valueLabel.setOrigin(Vector2f(std::round(valueLabelBounds.left + valueLabelBounds.width), 0.0f));
}


Font Stat::titleFont = Stat::initTitleFont();
Font Stat::initTitleFont() {
    Font titleFont;
    if (!titleFont.loadFromFile("res/Oswald-Medium.ttf")) {
        exit(1);
    }
    return titleFont;
}

Font Stat::descriptionFont = Stat::initDescriptionFont();
Font Stat::initDescriptionFont() {
    Font descriptionFont;
    if (!descriptionFont.loadFromFile("res/Oswald-Light.ttf")) {
        exit(1);
    }
    return descriptionFont;
}

Font Stat::valueFont = Stat::initValueFont();
Font Stat::initValueFont() {
    Font valueFont;
    if (!valueFont.loadFromFile("res/Oswald-Bold.ttf")) {
        exit(1);
    }
    return valueFont;
}
