#ifndef RGBMAP_DEFINED_
#define RGBMAP_DEFINED_

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

class RGBMap : public Pixmap<RGB> {
public:
  RGBMap(int width, int height) : Pixmap<RGB>(width, height) {}

  void exportToBMP(std::string path) {
    stbi_write_bmp(path.c_str(), getWidth(), getHeight(), 3,
                   static_cast<void *>(getPixels()));
  }

  void exportToJPEG(std::string path, int quality = 90) {
    stbi_write_jpg(path.c_str(), getWidth(), getHeight(), 3,
                   static_cast<void *>(getPixels()), quality);
  }

  void exportToGIF(std::string file) {
    throw std::logic_error("GIF output is not implemented for RGBMaps.");
  }

  void exportToPNG(std::string file) {
    stbi_write_png(file.c_str(), getWidth(), getHeight(), 3,
                   static_cast<void *>(getPixels()), 3 * getWidth());
  }

  void exportToPBM(std::string path) {
    throw std::logic_error("PBM output is not implemented for RGBMaps.");
  }

  void exportToPGM(std::string path) {
    throw std::logic_error("PGM output is not implemented for RGBMaps.");
  }

  void exportToPPM(std::string path) {
    std::ofstream file;
    file.open(path, std::ios_base::out | std::ios_base::binary);

    file << "P6\n";
    file << std::to_string(getWidth()) << ' ' << std::to_string(getHeight())
         << '\n';
    file << "255";
    file << '\n';

    RGB c_out = RGB(0, 0, 0);

    for (size_t index = 0; index < getArea(); index++) {
      c_out = getPixel(index, false);
      file << c_out.r << c_out.g << c_out.b;
    }

    file.close();
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

  void fill(RGB rgb) {
    for (size_t i = 0; i < getArea(); i++) {
      setPixel(i, rgb, false);
    }
  }

  void clear() {
    RGB copyF;
    copyF.r = copyF.g = copyF.b = 255;
    fill(copyF);
  }
};

} // namespace Vis

#endif
