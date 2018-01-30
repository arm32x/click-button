/// @file Random.cpp

#include "Random.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief The random number generator.
////////////////////////////////////////////////////////////////////////////////
std::mt19937 Random::generator(time(nullptr));

////////////////////////////////////////////////////////////////////////////////
/// Gets a random integer from the range specified.
///
/// @param minimum The minimum number that can generate, inclusive.
/// @param maximum The maximum number that can generate, exclusive.
/// @return A random integer in the given range.
////////////////////////////////////////////////////////////////////////////////
int Random::getIntFromRange(int minimum, int maximum) {
    std::uniform_int_distribution<int> dist(minimum, maximum - 1);
    return dist(generator);
}

////////////////////////////////////////////////////////////////////////////////
/// Gets a random float from the range specified.
///
/// @param minimum The minimum number that can generate, inclusive.
/// @param maximum The maximum number that can generate, exclusive.
/// @return A random float in the given range.
////////////////////////////////////////////////////////////////////////////////
float Random::getFloatFromRange(float minimum, float maximum) {
    std::uniform_real_distribution<float> dist(minimum, maximum - 1.0f);
    return dist(generator);
}
