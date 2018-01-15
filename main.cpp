#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "Collision.hpp"
#include "MainButton.hpp"
#include "Options.hpp"
#include "Random.hpp"

int main() {

    int splashTextIndex = Random::getIntFromRange(0, Options::SplashTexts.size());
    RenderWindow window(Options::ScreenSize, "Click button. " + Options::SplashTexts[splashTextIndex], Style::Titlebar | Style::Close);


    MainButton mainButton(Vector2f(50.0f, 150.0f));


    Font logoFont;
    if (!logoFont.loadFromFile("res/Oswald-Bold.ttf")) {
        exit(1);
    }

    Text logo;
    logo.setFont(logoFont);
    logo.setFillColor(Color(0xFF, 0xFF, 0xFF));
    logo.setCharacterSize(24);
    logo.setPosition(10.0f, 10.0f);
    logo.setString("Click button.");


    Font splashTextFont;
    if (!splashTextFont.loadFromFile("res/Oswald-Regular.ttf")) {
        exit(1);
    }

    Text splashTextLabel;
    splashTextLabel.setFont(splashTextFont);
    splashTextLabel.setFillColor(Color(0xFF, 0xFF, 0xFF));
    splashTextLabel.setCharacterSize(12);
    splashTextLabel.setPosition(10.0f, 40.0f);
    splashTextLabel.setString(Options::SplashTexts[splashTextIndex]);

    while (window.isOpen()) {
        {// Event handling
            Event e;
            while (window.pollEvent(e)) {
                switch (e.type) {
                    case Event::Closed:
                        window.close();
                        break;
                    case Event::MouseButtonPressed:
                        if (e.mouseButton.button == Mouse::Left && Collision::pointToRect(window.mapPixelToCoords(Mouse::getPosition(window)), mainButton.getGlobalBounds())) {
                            mainButton.press();
                        }
                        break;
                    case Event::MouseButtonReleased:
                        mainButton.release();
                        break;
                    default:
                        break;
                }
            }
        }

        window.clear(Options::BackgroundColor);
        window.draw(logo);
        window.draw(splashTextLabel);
        window.draw(mainButton);
        window.display();
    }

    return 0;

}
