/// @file Enemy.cpp

#include "Enemy.hpp"

std::function<void(Enemy* enemy)> Enemy::destroy;

/// @param position The position to spawn the center of the enemy at.
/// @param attack   @see Enemy::attack
Enemy::Enemy(const Vector2f position, long attack)
    : IconButton(position, true, ""), attack(attack) {

    attackLabel.setFont(attackFont);
    attackLabel.setCharacterSize(Options::EnemyAttackLabelTextSize);
    attackLabel.setString("-" + std::to_string(attack));
    rewrapLabelText();
}

/// @param attack @see Enemy::attack
Enemy::Enemy(long attack)
    : Enemy(getSpawnPosition(), attack) { }


Vector2f Enemy::getSpawnPosition() {
    unsigned short edge = Random::getIntFromRange(0, 4);
    switch (edge) {
        case 0: // The top edge
            return Vector2f(Random::getIntFromRange(Options::EnemySpawnMargin,
                                                    475.0f - Options::EnemySpawnMargin),
                            Options::EnemySpawnMargin);
        case 1: // The right edge
            return Vector2f(475.0f - Options::EnemySpawnMargin,
                            Random::getIntFromRange(Options::EnemySpawnMargin,
                                                    480.0f - Options::EnemySpawnMargin));
        case 2: // The bottom edge
            return Vector2f(Random::getIntFromRange(Options::EnemySpawnMargin,
                                                    475.0f - Options::EnemySpawnMargin),
                            480.0f - Options::EnemySpawnMargin);
        case 3: // The left edge
            return Vector2f(Options::EnemySpawnMargin,
                            Random::getIntFromRange(Options::EnemySpawnMargin,
                                                    480.0f - Options::EnemySpawnMargin));
        default: // In case something goes wrong:
            return Vector2f(Options::EnemySpawnMargin, // Spawn in the top-left corner.
                            Options::EnemySpawnMargin);
    }
}


void Enemy::draw(RenderTarget& window, RenderStates states) const {
    IconButton::draw(window, states); // Draw the background as an icon button.
    window.draw(attackLabel); // Draw the label.
}

/// @param mainButton This is required because I never bothered to make
///                   `MainButton` a singleton.
void Enemy::update(MainButton& mainButton) {
    // Is the enemy touching the main button?
    if (Collision::circleToRect(getPosition(), getRadius(), mainButton.getGlobalBounds())) {
        // If so, we want to deduct the score and destroy this enemy.

        // Deducting the score involves some basic subtraction:
        MainButton::setScore(MainButton::getScore() - attack);

        destroy(this); // And then we need to destroy the enemy.
    } else if (pressed) {
        destroy(this);
    }


    // We want to move towards the center of the main button. so first we have
    // to find the center of the main button.
    FloatRect mainButtonBounds = mainButton.getGlobalBounds();
    Vector2f destination(mainButtonBounds.left + mainButtonBounds.width  / 2,
                         mainButtonBounds.top  + mainButtonBounds.height / 2);

    // We can then calculate the distance in the X and Y directions we have to
    // move to get to our destination.
    Vector2f distance = destination - background.getPosition();

    // We need the direct distance (named length here) for our next step, so we
    // calculate it using the Pythagorean Theorem.
    float length = std::sqrt(distance.x * distance.x + distance.y * distance.y);

    // Normalize our distance vector, or bring it's length down to one, and then
    // multiply it by speed. This will give us the exact values we need to move
    // on the X and Y axes.
    distance /= length;

    // Move the enemy by the amounts calculated above.
    move(distance);
    rewrapLabelText(); // Move the text as well.
}


Font Enemy::attackFont = Enemy::initAttackFont();
Font Enemy::initAttackFont() {
    Font attackFont;
    if (!attackFont.loadFromFile("res/Oswald-Bold.ttf")) {
        exit(1);
    }
    return attackFont;
}


void Enemy::rewrapLabelText() {
    // Get the local bounds of the text. Local bounds is a term used by SFML to
    // represent a rectangle that contains all of the text and nothing more.
    // The X and Y positions of this rectangle are relative to the text's
    // current position.
    FloatRect labelBounds = attackLabel.getLocalBounds();
    // Set the origin of the text to the center, and round it to make sure the
    // text isn't blurry.
    attackLabel.setOrigin(std::round(labelBounds.left + labelBounds.width  / 2.0f),
                    std::round(labelBounds.top  + labelBounds.height / 2.0f));
    // Center the text within the enemy.
    attackLabel.setPosition(background.getPosition());
}
