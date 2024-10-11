#pragma once

#include <cmath>
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

//common headers
#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"