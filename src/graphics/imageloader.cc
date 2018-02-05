//
// Created by Timothy Herchen on 2/3/18.
//

#include "imageloader.h"

namespace Sine::Graphics {

    template<typename P>
    P ImageLoader<P>::load(const std::string &filename) {
        int x, y, n;

        unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 0); /// Interface to stbi_load
        if (data == nullptr) { // If data is invalid, throw an error
            throw std::runtime_error("Image does not exist or is inaccessible.");
        }

        P p(x, y);

        if (p.ColorSize == n) {
            p.setPixelPointer(static_cast<void *>(data)); // Set pointer of Pixmap to correct location
            return p;
        } else {
            throw std::runtime_error("Invalid data type length for image.");
        }
    }

    template<>
    Bitmap ImageLoader<Bitmap>::loadAny(const std::string &filename) {
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
    Graymap ImageLoader<Graymap>::loadAny(const std::string &filename) {
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
    RGBMap ImageLoader<RGBMap>::loadAny(const std::string &filename) {
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
    RGBAMap ImageLoader<RGBAMap>::loadAny(const std::string &filename) {
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

    // Explicit instantiation to make linker happy
    template
    struct ImageLoader<Bitmap>;
    template
    struct ImageLoader<Graymap>;
    template
    struct ImageLoader<RGBMap>;
    template
    struct ImageLoader<RGBAMap>;
}