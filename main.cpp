#include <SFML/Graphics.hpp>
using namespace sf;

#include "Options.hpp"
#include "Random.hpp"

int main() {

    int splashTextIndex = Random::getIntFromRange(0, Options::SplashTexts.size());
    RenderWindow window(Options::ScreenSize, "Click button. " + Options::SplashTexts[splashTextIndex], Style::Titlebar | Style::Close);

    while (window.isOpen()) {
        {// Event handling
            Event e;
            while (window.pollEvent(e)) {
                switch (e.type) {
                    case Event::Closed:
                        window.close();
                        break;
                    default:
                        break;
                }
            }
        }

        window.clear(Options::BackgroundColor);
        window.display();
    }

    return 0;

}
