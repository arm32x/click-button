/// @file Collision.hpp

#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

////////////////////////////////////////////////////////////////////////////////
/// A namespace to contain collision-related methods.
////////////////////////////////////////////////////////////////////////////////
namespace Collision {

    bool pointToRect(Vector2f point, FloatRect rect);
    bool pointToCircle(Vector2f point, Vector2f circleCenter, float circleRadius);

    bool circleToRect(Vector2f circleCenter, float circleRadius, FloatRect rect);

};
