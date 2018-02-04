#ifndef IMAGE_UTILS_DEFINED_
#define IMAGE_UTILS_DEFINED_

#include <string>
#include <fstream>

namespace Sine {

    enum class ImageType {
        UNKNOWN,
        JPEG,
        JPG = static_cast<int>(JPEG),
        GIF,
        BMP,
        PNG,
        PBM,
        PGM,
        PPM
    };

    ImageType extractImageType(std::string filename) noexcept;

    bool fileExists(const char *fileName);

} // namespace Sine

#endif
