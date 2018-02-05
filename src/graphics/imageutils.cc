//
// Created by Timothy Herchen on 2/3/18.
//

#include "imageutils.h"

namespace Sine::Graphics {
    ImageType extractImageType(std::string filename) noexcept {
        std::string extension;

        for (size_t index = filename.length() - 1; index > 0; index--) {
            if (filename[index] == '.') {
                break;
            }
            extension += static_cast<char>(tolower(filename[index]));
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

    bool fileExists(const char *filename) {
        std::ifstream infile(filename);
        return infile.good();
    }

}