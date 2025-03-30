
#ifndef CS221UTIL_RGBAPIXEL_H
#define CS221UTIL_RGBAPIXEL_H




using namespace std;

namespace cs221util {
    class RGBAPixel {
    public:
        unsigned char r;  // Red channel
        unsigned char g;  // Green channel
        unsigned char b;  // Blue channel
        double a;         // Alpha (transparency)

        // Default constructor (white pixel with alpha 1.0)
        RGBAPixel();

        // 3-argument constructor (full opacity)
        RGBAPixel(unsigned char r, unsigned char g, unsigned char b);

        // 4-argument constructor
        RGBAPixel(unsigned char r, unsigned char g, unsigned char b, double a);
    };

}

#endif // CS221UTIL_RGBAPIXEL_H
