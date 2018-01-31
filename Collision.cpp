/// @file Collision.cpp

#include "Collision.hpp"

bool Collision::pointToRect(Vector2f point, FloatRect rect) {
    // If the point is outside the rectangle, then it's not colliding.
    if (point.x < rect.left)              return false;
    if (point.x > rect.left + rect.width) return false;

    if (point.y < rect.top)               return false;
    if (point.y > rect.top + rect.height) return false;

    return true;
}

bool Collision::pointToCircle(Vector2f point, Vector2f circleCenter, float circleRadius) {
    // If the distance from the point to the circle's center is more than the
    // circle's radius, it's not colliding.
    float xDistance = point.x - circleCenter.x;
    float yDistance = point.y - circleCenter.y;

    float distanceSquared = xDistance * xDistance + yDistance * yDistance;

    return distanceSquared <= circleRadius * circleRadius;
}


bool Collision::circleToRect(Vector2f circleCenter, float circleRadius, FloatRect rect) {
    // Find closest point on the rectangle to the circle's center.
    Vector2f closestPoint = circleCenter;

    if (circleCenter.x < rect.left)               closestPoint.x = rect.left;
    if (circleCenter.x > rect.left + rect.width)  closestPoint.x = rect.left + rect.width;

    if (circleCenter.y < rect.top)                closestPoint.y = rect.top;
    if (circleCenter.y > rect.top  + rect.height) closestPoint.y = rect.top  + rect.height;

    // Do a point-to-circle collision check with our new point.
    return pointToCircle(closestPoint, circleCenter, circleRadius);
}
