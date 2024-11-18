#pragma once

#include <cmath>
#include <random>
#include <iostream>
#include <limits>
#include <memory>

//c++ std usings
using std::make_shared;
using std::shared_ptr;

//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265358979832385;

//utility functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.1);
    static std::mt19937 generator;
    return distribution(generator);
}

//common headers
#include "color.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"