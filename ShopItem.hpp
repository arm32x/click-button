/// @file ShopItem.hpp

#pragma once

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "MainButton.hpp"
#include "Options.hpp"

////////////////////////////////////////////////////////////////////////////////
/// A class to represent an item in the shop on the right of the screen.
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

    int getQuantityOwned();

    void hideQuantity();

protected:
    Text title;
    Text descriptionLabel;
    Button buyButton;
    Text priceLabel;
    Text quantityLabel;

    long price;
    bool insufficientFunds; ///< Whether or not you have enough points to buy this item.
    int quantity = 0;
    bool showQuantity = true;

    virtual void draw(RenderTarget& window, RenderStates states) const;

    void rewrapText(); ///< Make sure all of the text is aligned properly.

    static Vector2f getCoordsWithIndex(const int index, const Vector2f position);

    static Font titleFont;
    static Font initTitleFont();

    static Font descriptionFont;
    static Font initDescriptionFont();

    static Font priceFont;
    static Font initPriceFont();

};
