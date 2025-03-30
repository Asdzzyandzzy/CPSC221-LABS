#include "RGBAPixel.h"

namespace cs221util {

// Default constructor (white pixel with alpha 1.0)
RGBAPixel::RGBAPixel() : r(255), g(255), b(255), a(1.0) {}

// 3-argument constructor (full opacity)
RGBAPixel::RGBAPixel(unsigned char r, unsigned char g, unsigned char b)
    : r(r), g(g), b(b), a(1.0) {}

// 4-argument constructor
RGBAPixel::RGBAPixel(unsigned char r, unsigned char g, unsigned char b, double a)
    : r(r), g(g), b(b), a(a) {}

} // namespace cs221util
