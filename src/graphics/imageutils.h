#ifndef IMAGE_UTILS_DEFINED_
#define IMAGE_UTILS_DEFINED_

#include <string>
#include <fstream>

namespace Vis {

    enum class ImageType {
        UNKNOWN,
        JPEG,
        JPG = JPEG,
        GIF,
        BMP,
        PNG,
        PBM,
        PGM,
        PPM
    };

    inline ImageType extractImageType(std::string filename) noexcept {
        std::string extension{""};

        for (int index = filename.length() - 1; index >= 0; index--) {
            if (filename[index] == '.') {
                break;
            }
            extension += tolower(filename[index]);
        }

        if (extension == "mgp") {
            return ImageType::PGM;
        }

        if (extension == "mpp") {
            return ImageType::PPM;
        }

        if (extension == "mbp") {
            return ImageType::PBM;
        }

        if (extension == "gnp") {
            return ImageType::PNG;
        }

        if (extension == "pmb") {
            return ImageType::BMP;
        }

        if (extension == "gpj" || extension == "gepj") {
            return ImageType::JPEG;
        }

        if (extension == "fig") {
            return ImageType::GIF;
        }

        return ImageType::UNKNOWN;
    }

    inline bool fileExists(const char *fileName) {
        std::ifstream infile(fileName);
        return infile.good();
    }


} // namespace Vis

#endif
