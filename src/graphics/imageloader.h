#include "imageutils.h"
#include "color.h"
#include "pixmap.h"

#include "stb_image.h"
#include "imageconverter.h"

#ifndef IMAGE_LOADER_DEFINED_
#define IMAGE_LOADER_DEFINED_

namespace Sine {
    template<class P>
    class ImageLoader {
    private:

    public:
        static P load(std::string filename) {
            int x, y, n;

            unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 0);
            if (data == nullptr) {
                throw std::runtime_error("Image does not exist or is inaccessible.");
            }

            P p(x, y);

            if (p.ColorSize == n) {
                p.setPixelPointer(static_cast<void *>(data));
                return p;
            } else {
                throw std::runtime_error("Invalid data type length for image.");
            }
        }

        static P loadAny(std::string filename);
    };

    template<>
    inline Bitmap ImageLoader<Bitmap>::loadAny(std::string filename) {
        typedef Bitmap P;
        int x, y, n;

        unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 0);
        if (data == nullptr) {
            throw std::runtime_error("Image does not exist or is inaccessible.");
        }

        if (Bitmap::ColorSize == n) {
            Bitmap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));

            return temp;
        } else if (Graymap::ColorSize == n) {
            Graymap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else if (RGBMap::ColorSize == n) {
            RGBMap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else if (RGBAMap::ColorSize == n) {
            RGBAMap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else {
            throw std::runtime_error("Invalid data type length for image.");
        }
    }

    template<>
    inline Graymap ImageLoader<Graymap>::loadAny(std::string filename) {
        typedef Graymap P;
        int x, y, n;

        unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 0);
        if (data == nullptr) {
            throw std::runtime_error("Image does not exist or is inaccessible.");
        }

        if (Bitmap::ColorSize == n) {
            Bitmap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else if (Graymap::ColorSize == n) {
            Graymap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));

            return temp;
        } else if (RGBMap::ColorSize == n) {
            RGBMap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else if (RGBAMap::ColorSize == n) {
            RGBAMap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else {
            throw std::runtime_error("Invalid data type length for image.");
        }
    }

    template<>
    inline RGBMap ImageLoader<RGBMap>::loadAny(std::string filename) {
        typedef RGBMap P;
        int x, y, n;

        unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 0);
        if (data == nullptr) {
            throw std::runtime_error("Image does not exist or is inaccessible.");
        }

        if (Bitmap::ColorSize == n) {
            Bitmap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else if (Graymap::ColorSize == n) {
            Graymap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else if (RGBMap::ColorSize == n) {
            RGBMap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));

            return temp;
        } else if (RGBAMap::ColorSize == n) {
            RGBAMap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else {
            throw std::runtime_error("Invalid data type length for image.");
        }
    }

    template<>
    inline RGBAMap ImageLoader<RGBAMap>::loadAny(std::string filename) {
        typedef RGBAMap P;
        int x, y, n;

        unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 0);
        if (data == nullptr) {
            throw std::runtime_error("Image does not exist or is inaccessible.");
        }

        if (Bitmap::ColorSize == n) {
            Bitmap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else if (Graymap::ColorSize == n) {
            Graymap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else if (RGBMap::ColorSize == n) {
            RGBMap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));
            ImageConverter<P> conv;

            return conv.convert(temp);
        } else if (RGBAMap::ColorSize == n) {
            RGBAMap temp(x, y);

            temp.setPixelPointer(static_cast<void *>(data));

            return temp;
        } else {
            throw std::runtime_error("Invalid data type length for image.");
        }
    }
}

#endif
