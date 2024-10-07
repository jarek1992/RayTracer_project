#pragma once

#include "vec3.hpp"
#include <iostream>

using color = vec3;

//save pixel_color to the stream
void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //translate the [0,1] component values to the byte range [0,255]
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    //write out the pixel color components
    out << rbyte << " " << gbyte << " " << bbyte << '\n';

}