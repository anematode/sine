#ifndef IMAGE_UTILS_DEFINED_
#define IMAGE_UTILS_DEFINED_

#include <string>
#include <fstream>

namespace Sine::Graphics {

    /**
     * Enum abstracting the type of an image.
     */
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


    /**
     * Extract the (expected) type of an image from its filename.
     * @param filename Location of file.
     * @return Enum of file type.
     */
    ImageType extractImageType(std::string filename) noexcept;


    /**
     * Check if a file exists.
     * @param filename Name of file.
     * @return Whether the file is openable.
     */
    bool fileExists(const char *fileName);

} // namespace Sine

#endif
