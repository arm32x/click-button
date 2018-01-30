/// @file Collision.cpp

#include "Collision.hpp"

bool Collision::pointToRect(Vector2f point, FloatRect rect) {
    if (point.x < rect.left)              return false;
    if (point.x > rect.left + rect.width) return false;

    if (point.y < rect.top)               return false;
    if (point.y > rect.top + rect.height) return false;

    return true;
}

bool Collision::pointToCircle(Vector2f point, Vector2f circleCenter, float circleRadius) {
    float xDistance = point.x - circleCenter.x;
    float yDistance = point.y - circleCenter.y;

    float distanceSquared = xDistance * xDistance + yDistance * yDistance;

    return distanceSquared <= circleRadius * circleRadius;
}
