#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "Collision.hpp"
#include "Options.hpp"
#include "Random.hpp"

int main() {

    int splashTextIndex = Random::getIntFromRange(0, Options::SplashTexts.size());
    RenderWindow window(Options::ScreenSize, "Click button. " + Options::SplashTexts[splashTextIndex], Style::Titlebar | Style::Close);

    Button testButton(Vector2f(5.0f, 5.0f), "This is a test.");

    while (window.isOpen()) {
        {// Event handling
            Event e;
            while (window.pollEvent(e)) {
                switch (e.type) {
                    case Event::Closed:
                        window.close();
                        break;
                    case Event::MouseButtonPressed:
                        if (e.mouseButton.button == Mouse::Left && Collision::pointToRect(window.mapPixelToCoords(Mouse::getPosition(window)), testButton.getGlobalBounds())) {
                            testButton.press();
                        }
                        break;
                    case Event::MouseButtonReleased:
                        testButton.release();
                        break;
                    default:
                        break;
                }
            }
        }

        window.clear(Options::BackgroundColor);
        window.draw(testButton);
        window.display();
    }

    return 0;

}
