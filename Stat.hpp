/// @file Stat.hpp

#pragma once

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "MainButton.hpp"
#include "Options.hpp"

////////////////////////////////////////////////////////////////////////////////
/// A class to represent a statistic on the right of the screen.
///
/// Metrics:
///   - Each item has 51px of height and 5px of bottom padding.
///   - To fit the stats area, each item is exactly 338px wide.
///   - The buy button is 150px wide.
////////////////////////////////////////////////////////////////////////////////
class Stat : public Drawable {

public:
    Stat(const int index, const std::string name, const std::string description);

    void update(std::string newValue);

protected:
    Text title;
    Text descriptionLabel;
    Text valueLabel;

    std::string value;

    virtual void draw(RenderTarget& window, RenderStates states) const;

    void rewrapText(); ///< Make sure all of the text is aligned properly.

    static Vector2f getCoordsWithIndex(const int index, const Vector2f position);

    static Font titleFont;
    static Font initTitleFont();

    static Font descriptionFont;
    static Font initDescriptionFont();

    static Font valueFont;
    static Font initValueFont();

};
