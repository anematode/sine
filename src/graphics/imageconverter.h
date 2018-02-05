#ifndef IMAGE_CONVERTER_DEFINED_
#define IMAGE_CONVERTER_DEFINED_

#include <memory>
#include "pixmap.h"

namespace Sine::Graphics {
    /**
     * Defines whether to convert to grayscale based on an average, or based on luminosity
     * The latter is closer to how our eyes see it
     */
    enum class ImageConversionParam {
        AVERAGE, ///< Average color channels to get grayscale
        AVG = static_cast<int>(AVERAGE),
        LUMINOSITY, ///< Weigh color channels to get grayscale
        LUM = static_cast<int>(LUMINOSITY)
    };

    /**
     *
     * @tparam TypeA Type to convert pixmaps into
     * @tparam opt Image conversion parameter, used iff TypeA == Graymap
     */
    template<typename TypeA, ImageConversionParam opt = ImageConversionParam::LUM>
    struct ImageConverter {
        static TypeA convert(const RGBMap &a);

        static TypeA convert(const RGBAMap &a);

        static TypeA convert(const Bitmap &a);

        static TypeA convert(const Graymap &a);
    };
}

#endif
