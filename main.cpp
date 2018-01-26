#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "Collision.hpp"
#include "MainButton.hpp"
#include "Options.hpp"
#include "Random.hpp"
#include "ShopItem.hpp"

int main() {

    Random::getIntFromRange(0, 1); // Advance the random number generator to avoid repeated splash texts.
    int splashTextIndex = Random::getIntFromRange(0, Options::SplashTexts.size());
    RenderWindow window(VideoMode(854, 480), "Click button. " + Options::SplashTexts[splashTextIndex], Style::Titlebar | Style::Close);
    window.setFramerateLimit(60); // Make sure that CPS (Clicks Per Second) is ACTUALLY PER SECOND!!! (see `MainButton::update()`)


    MainButton mainButton(Vector2f(100.0f, 150.0f));


    Font logoFont;
    if (!logoFont.loadFromFile("res/Oswald-Bold.ttf")) {
        exit(1);
    }

    Text logo;
    logo.setFont(logoFont);
    logo.setFillColor(Color(0xFF, 0xFF, 0xFF));
    logo.setCharacterSize(24);
    logo.setPosition(20.0f, 10.0f);
    logo.setString("Click button.");


    Font splashTextFont;
    if (!splashTextFont.loadFromFile("res/Oswald-Regular.ttf")) {
        exit(1);
    }

    Text splashTextLabel;
    splashTextLabel.setFont(splashTextFont);
    splashTextLabel.setFillColor(Color(0xFF, 0xFF, 0xFF));
    splashTextLabel.setCharacterSize(12);
    splashTextLabel.setPosition(20.0f, 40.0f);
    splashTextLabel.setString(Options::SplashTexts[splashTextIndex]);


    RectangleShape shopDivider;
    shopDivider.setFillColor(Options::DividerColor);
    shopDivider.setSize(Vector2f(1.0f, 480.0f));
    shopDivider.setPosition(Vector2f(475.0f, 0.0f));


    Text shopHeader;
    shopHeader.setFont(logoFont);
    shopHeader.setFillColor(Color(0xFF, 0xFF, 0xFF));
    shopHeader.setCharacterSize(24);
    shopHeader.setPosition(496.0f, 10.0f);
    shopHeader.setString("Buy things.");

    Text shopSlogan;
    shopSlogan.setFont(splashTextFont);
    shopSlogan.setFillColor(Color(0xFF, 0xFF, 0xFF));
    shopSlogan.setCharacterSize(12);
    shopSlogan.setPosition(496.0f, 40.0f);
    shopSlogan.setString("Increase your clicking power.");


    ShopItem testItem(0, "Finger Puppet", "Give me money. Please?", 100, 1, 1);


    bool autoclicking = false;
    bool autoclicking1 = false;
    bool autoclicking2 = false;

    while (window.isOpen()) {
        {// Event handling
            Event e;
            while (window.pollEvent(e)) {
                mainButton.handleEvent(e, window);
                testItem.handleEvent(e, window);
                switch (e.type) {
                    case Event::Closed:
                        window.close();
                        break;
                    default:
                        break;
                }
            }
        }

        autoclicking = Keyboard::isKeyPressed(Keyboard::Num5) && Keyboard::isKeyPressed(Keyboard::Dash);

        autoclicking1 = false;
        if (autoclicking) {
            autoclicking1 = true;
            autoclicking2 = true;
            if (mainButton.isPressed()) {
                if (Keyboard::isKeyPressed(Keyboard::Tab)) {
                    for (int index = 0; index < 10; index++) {
                        mainButton.release();
                        mainButton.press();
                    }
                }
                mainButton.release();
            } else {
                mainButton.press();
            }
        }
        if (!autoclicking1 && autoclicking2 && mainButton.isPressed()) {
            mainButton.release();
        }
        if (!autoclicking) {
            autoclicking2 = false;
        }

        mainButton.update();
        testItem.update();

        window.clear(Options::BackgroundColor);
        window.draw(shopDivider);
        window.draw(shopHeader);
        window.draw(shopSlogan);
        window.draw(testItem);
        window.draw(logo);
        window.draw(splashTextLabel);
        window.draw(mainButton);
        window.display();
    }

    return 0;

}
