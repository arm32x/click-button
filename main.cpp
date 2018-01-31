/// @file main.cpp

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Button.hpp"
#include "Collision.hpp"
#include "Enemy.hpp"
#include "IconButton.hpp"
#include "Icons.hpp"
#include "MainButton.hpp"
#include "Options.hpp"
#include "Random.hpp"
#include "ShopItem.hpp"

/// Stands for "linear interpolation". Returns the value that is a percentage
/// (represented by `t`) in between two values.
///
/// @param begin The start value.
/// @param end   The end value.
/// @param t     A percentage (from 0.0f to 1.0f).
/// @return The value that is a percentage in between two values.
float lerp(float begin, float end, float t) {
    float difference = end - begin;
    return begin + difference * t;
}

////////////////////////////////////////////////////////////////////////////////
/// @page fontinit Font initialization
///
/// Fonts are initialized by first declaring a font variable, and then assigning
/// the return value of an initialization function to it.
///
/// Each font object will only be used at one size throughout the program, but
/// multiple font objects can reference the same font file.
////////////////////////////////////////////////////////////////////////////////

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

    RectangleShape shopBackground;
    shopBackground.setSize(Vector2f(379.0f, 480.0f));
    shopBackground.setPosition(Vector2f(475.0f, 0.0f));
    shopBackground.setFillColor(Options::BackgroundColor);


    ShopItem shopItemCursor(0, "Cursor", "Increases CPS by 1", 100, 0, 1);
    ShopItem shopItemGloves(1, "Gloves", "Increases power by 1", 125, 1, 0);
    ShopItem shopItemCustomCursor(2, "Custom Cursor", "Increases CPS by 10", 900, 0, 10);
    ShopItem shopItemCustomGloves(3, "Custom Gloves", "Increases power by 10", 1150, 10, 0);


    IconButton pauseButton(Vector2f(28.0f, 452.0f), false, "pause");
    bool gamePaused = false;
    pauseButton.onRelease = [&pauseButton, &gamePaused] () -> void {
        gamePaused = !gamePaused;
        if (gamePaused) {
            pauseButton.setIcon("play");
        } else {
            pauseButton.setIcon("pause");
        }
    };

    RectangleShape pauseShade;
    pauseShade.setSize(Vector2f(854.0f, 480.0f)); // Cover the entire screen
    pauseShade.setPosition(Vector2f(0.0f, 0.0f));
    pauseShade.setFillColor(Color(Options::BackgroundColor.r,
                                  Options::BackgroundColor.g,
                                  Options::BackgroundColor.b,
                                  Options::ShadeOpacity));


    Text statsHeader;
    statsHeader.setFont(logoFont);
    statsHeader.setFillColor(Color(0xFF, 0xFF, 0xFF));
    statsHeader.setCharacterSize(24);
    statsHeader.setPosition(496.0f, 10.0f);
    statsHeader.setString("View stats.");

    Text statsSlogan;
    statsSlogan.setFont(splashTextFont);
    statsSlogan.setFillColor(Color(0xFF, 0xFF, 0xFF));
    statsSlogan.setCharacterSize(12);
    statsSlogan.setPosition(496.0f, 40.0f);
    statsSlogan.setString("See how much time you've lost.");


    std::vector<Enemy> enemies; ///< A list of all enemies in-game.
    Enemy::destroy = [&enemies] (Enemy* enemy) -> void {
        for (unsigned int index = 0; index < enemies.size(); index++) {
            if (&enemies[index] == enemy) {
                enemies.erase(enemies.begin() + index);
            }
        }
    };
    bool firstEnemySpawned = false;
    float enemySpawnTimer = 0.0f;


    bool autoclicking = false;
    bool autoclicking1 = false;
    bool autoclicking2 = false;

    while (window.isOpen()) {
        {// Event handling
            Event e;
            while (window.pollEvent(e)) {
                if (!gamePaused) {
                    mainButton.handleEvent(e, window);
                    shopItemCursor.handleEvent(e, window);
                    shopItemGloves.handleEvent(e, window);
                    shopItemCustomCursor.handleEvent(e, window);
                    shopItemCustomGloves.handleEvent(e, window);
                    for (unsigned int index = 0; index < enemies.size(); index++) {
                        enemies[index].handleEvent(e, window);
                    }
                }
                pauseButton.handleEvent(e, window);
                switch (e.type) {
                    case Event::Closed:
                        window.close();
                        break;
                    default:
                        break;
                }
            }
        }

        if (!gamePaused) {
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
            shopItemCursor.update();
            shopItemGloves.update();
            shopItemCustomCursor.update();
            shopItemCustomGloves.update();
            for (unsigned int index = 0; index < enemies.size(); index++) {
                enemies[index].update(mainButton);
            }

            if (MainButton::getTotalScore() >= 50 && !firstEnemySpawned) {
                enemies.push_back(Enemy(10));
                firstEnemySpawned = true;
            } else if (MainButton::getTotalScore() >= 100) {
                enemySpawnTimer += MainButton::getTotalScore() >= Options::ScoreGoal ? Options::MaxEnemySpawnRate
                                   : lerp(Options::MinEnemySpawnRate, Options::MaxEnemySpawnRate,
                                          (MainButton::getTotalScore() - 100) / (Options::ScoreGoal - 100));
                while (enemySpawnTimer >= 60.0f) {
                    enemies.push_back(Enemy(50));
                    enemySpawnTimer -= 60.0f;
                }
            }
        }

        window.clear(Options::BackgroundColor);
        for (unsigned int index = 0; index < enemies.size(); index++) {
            window.draw(enemies[index]);
        }
        // Don't draw the shop if the game is paused because the stats page
        // covers it up.
        if (!gamePaused) {
            window.draw(shopBackground);
            window.draw(shopDivider);
            window.draw(shopHeader);
            window.draw(shopSlogan);
            window.draw(shopItemCursor);
            window.draw(shopItemGloves);
            window.draw(shopItemCustomCursor);
            window.draw(shopItemCustomGloves);
        }
        window.draw(mainButton);
        if (gamePaused) window.draw(pauseShade);
        window.draw(pauseButton);
        window.draw(logo);
        window.draw(splashTextLabel);
        if (gamePaused) {
            // Just reusing some variables, don't mind me. ;)
            window.draw(shopBackground);
            window.draw(shopDivider);

            window.draw(statsHeader);
            window.draw(statsSlogan);
        }
        window.display();
    }

    return 0;

}
