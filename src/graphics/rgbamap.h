#ifndef RGBAMap_DEFINED_
#define RGBAMap_DEFINED_

#include "imageutils.h"
#include "pixmap.h"
#include <exception>
#include <fstream>
#include <iostream>

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../include/stb_image_write.h"
#endif

#include "color.h"
#include "pixmap.h"

namespace Vis {

class RGBAMap : public Pixmap<RGBA> {
public:
  RGBAMap(int width, int height) : Pixmap<RGBA>(width, height) {}

  void exportToBMP(std::string path) {
    throw std::logic_error("BMP output is not implemented for RGBAMaps.");
  }

  void exportToJPEG(std::string path, int quality = 90) {
    stbi_write_jpg(path.c_str(), getWidth(), getHeight(), 4,
                   static_cast<void *>(getPixels()), quality);
  }

  void exportToGIF(std::string file) {
    throw std::logic_error("GIF output is not implemented for RGBAMaps.");
  }

  void exportToPNG(std::string file) {
    stbi_write_png(file.c_str(), getWidth(), getHeight(), 4,
                   static_cast<void *>(getPixels()), getWidth());
  }

  void exportToPBM(std::string path) {
    throw std::logic_error("PBM output is not implemented for RGBAMaps.");
  }

  void exportToPGM(std::string path) {
    throw std::logic_error("PGM output is not implemented for RGBAMaps.");
  }

  void exportToPPM(std::string path) {
    throw std::logic_error("PPM output is not implemented for RGBAMaps.");
  }

  bool exportToFile(std::string file, ImageType type = ImageType::UNKNOWN) {
  guessType:

    switch (type) {
    case ImageType::UNKNOWN:
      type = extractImageType(file);

      if (type == ImageType::UNKNOWN) {
        return false;
      }

      goto guessType;

    case ImageType::BMP:
      exportToBMP(file);
      break;

    case ImageType::JPEG:
      exportToJPEG(file);
      break;

    case ImageType::GIF:
      exportToGIF(file);
      break;

    case ImageType::PNG:
      exportToPNG(file);
      break;

    case ImageType::PBM:
      exportToPBM(file);
      break;

    case ImageType::PGM:
      exportToPGM(file);
      break;

    case ImageType::PPM:
      exportToPPM(file);
      break;

    default:
      return false;
    }

    return true;
  }

  void fill(RGBA rgba) {
    for (size_t i = 0; i < getArea(); i++) {
      setPixel(i, rgba, false);
    }
  }

  void clear() {
    RGBA copyF;
    copyF.r = copyF.g = copyF.b = 255;
    copyF.a = 0;
    fill(copyF);
  }
};

} // namespace Vis

#endif
