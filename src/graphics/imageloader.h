#include "imageutils.h"
#include "color.h"
#include "pixmap.h"

#include "stb_image.h"
#include "imageconverter.h"

#ifndef IMAGE_LOADER_DEFINED_
#define IMAGE_LOADER_DEFINED_

namespace Sine::Graphics {
    /**
     * Loads a P, given a file.
     * @tparam P Pixmap type.
     */
    template<class P>
    struct ImageLoader {
    public:
        /**
         * Load a file, assuming the types match up.
         * @param filename File location.
         * @return A Pixmap.
         */
        static P load(const std::string &filename);

        /**
         * Load a file of any type, converting if necessary.
         * @param filename File location.
         * @return A Pixmap.
         */
        static P loadAny(const std::string &filename);
    };
}

#endif
