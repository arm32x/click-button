/// @file Random.hpp

#pragma once

#include <ctime>
#include <random>

////////////////////////////////////////////////////////////////////////////////
/// \brief A namespace to contain some random number generation logic.
////////////////////////////////////////////////////////////////////////////////
namespace Random {

    extern std::mt19937 generator;  ///< The random number generator.

    int getIntFromRange(int minimum, int maximum); ///< Gets a random integer from the range specified.
    float getFloatFromRange(float minimum, float maximum); ///< Gets a random float from the range specified.

};
