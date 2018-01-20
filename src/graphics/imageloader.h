#include "imageutils.h"
#include "color.h"
#include "pixmap.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#endif

#ifndef IMAGE_LOADER_DEFINED_
#define IMAGE_LOADER_DEFINED_

namespace Vis {
    template<class P>
    class ImageLoader {
    private:

    public:
        P load(std::string filename) {
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
    };
}

#endif
