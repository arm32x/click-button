/// @file EnemyExplosion.cpp

#include "EnemyExplosion.hpp"

std::function<void(EnemyExplosion* explosion)> EnemyExplosion::destroy;

std::vector<std::pair<float, float>> EnemyExplosion::frames = {
    std::pair<float, float>(16.0f,  -1.0f),
    std::pair<float, float>(16.0f,  -3.0f),
    std::pair<float, float>(16.0f,  -5.0f),
    std::pair<float, float>(16.0f,  -7.0f),
    std::pair<float, float>(16.0f,  -9.0f),
    std::pair<float, float>(16.0f, -11.0f),
    std::pair<float, float>(16.0f, -13.0f),
    std::pair<float, float>(16.0f, -15.0f),
    std::pair<float, float>(15.0f, -15.0f),
    std::pair<float, float>(13.0f, -13.0f),
    std::pair<float, float>(11.0f, -11.0f),
    std::pair<float, float>( 9.0f,  -9.0f),
    std::pair<float, float>( 7.0f,  -7.0f),
    std::pair<float, float>( 5.0f,  -5.0f),
    std::pair<float, float>( 3.0f,  -3.0f),
    std::pair<float, float>( 1.0f,  -1.0f)
};

EnemyExplosion::EnemyExplosion(Vector2f position)
    : IconButton(position, true, "") {

}


void EnemyExplosion::update() {
    if (currentFrame >= frames.size()) {// Finished the animation.
        destroy(this);
        return;
    }

    background.setRadius(frames[currentFrame].first);
    background.setOrigin(Vector2f(background.getRadius(), background.getRadius()));
    background.setOutlineThickness(frames[currentFrame].second);
    currentFrame++;
}
