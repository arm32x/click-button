/// @file ShopItem.cpp

#include "ShopItem.hpp"

ShopItem::ShopItem(const int index, const std::string name, const std::string description, long price, std::function<void()> buyAction)
    : buyButton(getCoordsWithIndex(index, Vector2f(213.0f, 5.0f)), Vector2f(120.0f, 41.0f), "Buy"), price(price) {

    title.setPosition(getCoordsWithIndex(index, Vector2f(0.0f, 5.0f)));
    title.setFont(titleFont);
    title.setCharacterSize(18);
    title.setString(name);

    descriptionLabel.setPosition(getCoordsWithIndex(index, Vector2f(0.0f, 28.0f)));
    descriptionLabel.setFont(descriptionFont);
    descriptionLabel.setCharacterSize(14);
    descriptionLabel.setString(description);

    priceLabel.setPosition(getCoordsWithIndex(index, Vector2f(198.0f, 5.0f)));
    priceLabel.setFont(priceFont);
    priceLabel.setCharacterSize(18);
    priceLabel.setString(std::to_string(price));

    quantityLabel.setPosition(getCoordsWithIndex(index, Vector2f(198.0f, 28.0f)));
    quantityLabel.setFont(descriptionFont);
    quantityLabel.setCharacterSize(14);
    quantityLabel.setString("×" + std::to_string(quantity));

    rewrapText();

    buyButton.onRelease = std::bind([this, &price = this->price] (std::function<void()> buyAction) -> void {
        buyAction();
        MainButton::setScore(MainButton::getScore() - price);

        price = std::round(price * Options::ShopPriceHikeRate);
        priceLabel.setString(std::to_string(price));
        quantity++;
        quantityLabel.setString("×" + std::to_string(quantity));
        rewrapText();
    }, buyAction);
}

ShopItem::ShopItem(const int index, const std::string name, const std::string description, long price, long powerIncrease, long cpsIncrease)
    : ShopItem(index, name, description, price, [powerIncrease, cpsIncrease] () -> void {

    MainButton::setPower(MainButton::getPower() + powerIncrease);
    MainButton::setCps(MainButton::getCps() + cpsIncrease);
}) { };


Vector2f ShopItem::getCoordsWithIndex(const int index, const Vector2f position) {
    return Vector2f(position.x + 496.0f, position.y + 56.0f * index + 80.0f);
}


void ShopItem::draw(RenderTarget& window, RenderStates states) const {
    window.draw(descriptionLabel);
    window.draw(title);
    window.draw(buyButton);
    window.draw(quantityLabel);
    window.draw(priceLabel);
}

void ShopItem::update() {
    if (MainButton::getScore() < price) {
        insufficientFunds = true;
        buyButton.setFillColor(Options::DisabledButtonColor);
        buyButton.setShadowColor(Options::DisabledButtonShadowColor);
    } else {
        insufficientFunds = false;
        buyButton.setFillColor(Options::StandardButtonColor);
        buyButton.setShadowColor(Options::StandardButtonShadowColor);
    }
}

void ShopItem::handleEvent(Event& e, Window& window) {
    switch (e.type) {
        case Event::MouseButtonPressed:
            if (!insufficientFunds && e.mouseButton.button == Mouse::Left && Collision::pointToRect((Vector2f)Mouse::getPosition(window), buyButton.getGlobalBounds())) {
                buyButton.press();
            }
            break;
        case Event::MouseButtonReleased:
            buyButton.release();
            break;
        default:
            break;
    }
}


int ShopItem::getQuantityOwned() {
    return quantity;
}


void ShopItem::rewrapText() {
    FloatRect priceLabelBounds = priceLabel.getLocalBounds();
    priceLabel.setOrigin(Vector2f(std::round(priceLabelBounds.left + priceLabelBounds.width), 0.0f));

    FloatRect quantityLabelBounds = quantityLabel.getLocalBounds();
    quantityLabel.setOrigin(Vector2f(std::round(quantityLabelBounds.left + quantityLabelBounds.width), 0.0f));
}


Font ShopItem::titleFont = ShopItem::initTitleFont();
Font ShopItem::initTitleFont() {
    Font titleFont;
    if (!titleFont.loadFromFile("res/Oswald-Medium.ttf")) {
        exit(1);
    }
    return titleFont;
}

Font ShopItem::descriptionFont = ShopItem::initDescriptionFont();
Font ShopItem::initDescriptionFont() {
    Font descriptionFont;
    if (!descriptionFont.loadFromFile("res/Oswald-Light.ttf")) {
        exit(1);
    }
    return descriptionFont;
}

Font ShopItem::priceFont = ShopItem::initPriceFont();
Font ShopItem::initPriceFont() {
    Font priceFont;
    if (!priceFont.loadFromFile("res/Oswald-Bold.ttf")) {
        exit(1);
    }
    return priceFont;
}
