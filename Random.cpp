/// @file Random.cpp

#include "Random.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief The random number generator.
////////////////////////////////////////////////////////////////////////////////
std::mt19937 Random::generator(time(nullptr));

////////////////////////////////////////////////////////////////////////////////
/// \brief Gets a random integer from the range specified.
///
/// \param minimum The minimum number that can generate.
/// \param maximum The maximum number that can generate.
/// \return A random integer.
////////////////////////////////////////////////////////////////////////////////
int Random::getIntFromRange(int minimum, int maximum) {
    std::uniform_int_distribution<int> dist(minimum, maximum - 1);
    return dist(generator);
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Gets a random float from the range specified.
///
/// \param minimum The minimum number that can generate.
/// \param maximum The maximum number that can generate.
/// \return A random float.
////////////////////////////////////////////////////////////////////////////////
float Random::getFloatFromRange(float minimum, float maximum) {
    std::uniform_real_distribution<float> dist(minimum, maximum - 1.0f);
    return dist(generator);
}
