/// @file Collision.cpp

#include "Collision.hpp"

bool Collision::pointToRect(Vector2f point, FloatRect rect) {
    if (point.x < rect.left)              return false;
    if (point.x > rect.left + rect.width) return false;

    if (point.y < rect.top)               return false;
    if (point.y > rect.top + rect.height) return false;

    return true;
}
