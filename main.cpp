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
        window.draw(mainButton);
        window.display();
    }

    return 0;

}
