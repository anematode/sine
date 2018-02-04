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
        static P load(const std::string &filename);

        static P loadAny(const std::string &filename);
    };
}

#endif
