#ifndef PIXMAP_DEFINED_
#define PIXMAP_DEFINED_

#include <string>

#include <algorithm>
#include <exception>
#include <iostream>

#include "../math/vec2.h"
#include "imageutils.h"
#include "color.h"
#include <fstream>

#include "stb_image_write.h"

#include <cmath>

namespace Sine {

    /**
  Pixmap is the base class for Graymap, Bitmap, RGBMap and RGBMap
  Basically it just abstracts a 2D array of pixels, given a template argument for the pixel itself
    **/



    template<typename PixelColor>
    class Pixmap {
    protected:
        PixelColor *pixels;
        int width;
        int height;
        long area;

    public:
        using PixelType = PixelColor;
        const static int ColorSize = sizeof(PixelColor);

        Pixmap(int width, int height);

        Pixmap(const Pixmap<PixelColor> &p);

        Pixmap(Pixmap<PixelColor> &&p) noexcept;

        Pixmap<PixelColor> &operator=(Pixmap<PixelColor> &&p) noexcept;

        void copyFrom(const Pixmap &p);

        PixelColor *begin();

        PixelColor *end();

        ~Pixmap();

        void checkIndex(int index) const;

        void checkPair(int x, int y) const;

        int getWidth() const;

        int getHeight() const;

        PixelColor *getPixels() const;

        long getArea() const;

        void setPixelPointer(void *p);

        bool indexContained(int index) const;

        bool pairContained(int x, int y) const;

        int pairToIndex(int x, int y) const;

        PixelColor &operator()(int row, int col);

        PixelColor operator()(int row, int col) const;

        PixelColor &operator()(int index);

        PixelColor operator()(int index) const;

        PixelColor getPixel(int index) const;

        PixelColor getPixel(int x, int y) const;

        //PixelColor getPixelAny(int x, int y) const;

        PixelColor &getPixelRef(int index);

        PixelColor &getPixelRef(int x, int y);

        void setPixel(int index, PixelColor c);

        void setPixel(int x, int y, PixelColor c);

        bool exportToFile(std::string file,
                          ImageType type = ImageType::UNKNOWN);

        Pixmap sample(double x) const;

        void exportToBMP(std::string file);

        void exportToJPEG(std::string file, int quality = 90);

        void exportToGIF(std::string file);

        void exportToPNG(std::string file);

        void exportToPBM(std::string file);

        void exportToPPM(std::string file);

        void exportToPGM(std::string file);
    };

    typedef Pixmap<bool> Bitmap;
    typedef Pixmap<RGB> RGBMap;
    typedef Pixmap<uint8_t> Graymap;
    typedef Pixmap<RGBA> RGBAMap;

} // namespace Sine


#endif
