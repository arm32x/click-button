/// @file Random.hpp

#pragma once

#include <ctime>
#include <random>

////////////////////////////////////////////////////////////////////////////////
/// \brief A namespace to contain some random number generation logic.
////////////////////////////////////////////////////////////////////////////////
namespace Random {

    extern std::mt19937 generator;  ///< The random number generator.

    int getIntFromRange(int minimum, int maximum);
    float getFloatFromRange(float minimum, float maximum);

};
