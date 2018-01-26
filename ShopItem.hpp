#pragma once

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "MainButton.hpp"
#include "Options.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief A class to represent an item in the shop on the right of the screen.
///
/// Metrics:
///   - Each item has 51px of height and 5px of bottom padding.
///   - To fit the shop area, each item is exactly 338px wide.
///   - The buy button is 150px wide.
////////////////////////////////////////////////////////////////////////////////
class ShopItem : public Drawable {

public:
    ShopItem(const int index, const std::string name, const std::string description, long price, std::function<void()> buyAction);
    ShopItem(const int index, const std::string name, const std::string description, long price, long powerIncrease, long cpsIncrease);

    void update();
    void handleEvent(Event& e, Window& window);

protected:
    Text title;
    Text descriptionLabel;
    Button buyButton;
    Text priceLabel;

    long price;
    bool insufficientFunds;

    virtual void draw(RenderTarget& window, RenderStates states) const;

    void rewrapPriceText();

    static Vector2f getCoordsWithIndex(const int index, const Vector2f position);

    /// \page fonts Font initialization
    ///
    /// Fonts are initialized by calling the initialization method and assigning
    /// the result to the actual font.

    static Font titleFont;
    static Font initTitleFont();

    static Font descriptionFont;
    static Font initDescriptionFont();

    static Font priceFont;
    static Font initPriceFont();

};
