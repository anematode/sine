#ifndef BITMAP_DEFINED_
#define BITMAP_DEFINED_

#include "pixmap.h"
#include "imageutils.h"
#include <fstream>
#include <exception>
#include <iostream>
#include "graymap.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#ifndef INCLUDE_STB_IMAGE_WRITE_H
#include "../include/stb_image_write.h"
#endif

namespace Vis {

class Bitmap : public Pixmap<bool> {
public:
  Bitmap(int width, int height) : Pixmap<bool>(width, height) {

  }

  void exportToBMP(std::string path) {
    Graymap temp = Graymap(getWidth(), getHeight());

    for (int index = 0; index < getArea(); index++) {
      temp.setPixel(index, (getPixel(index, false) ? 255 : 0));
    }

    temp.exportToBMP(path);
  }

  void exportToJPEG(std::string path, int quality = 90) {
    Graymap temp = Graymap(getWidth(), getHeight());

    for (int index = 0; index < getArea(); index++) {
      temp.setPixel(index, (getPixel(index, false) ? 255 : 0));
    }

    temp.exportToJPEG(path, quality);
  }

  void exportToGIF(std::string path) {
    throw std::logic_error("GIF output is not implemented for Bitmaps.");
  }

  void exportToPNG(std::string path) {
    Graymap temp = Graymap(getWidth(), getHeight());

    for (int index = 0; index < getArea(); index++) {
      temp.setPixel(index, (getPixel(index, false) ? 255 : 0));
    }

    temp.exportToPNG(path);
  }

  void exportToPBM(std::string path) {
    std::ofstream file;
    file.open(path, std::ios_base::out | std::ios_base::binary);

    file << "P4\n";
    file << std::to_string(getWidth()) << ' ' << std::to_string(getHeight()) << '\n';

    uint8_t byteOut;
    int bitCount;

    int width = getWidth();

    for (int i = 0; i < getHeight(); i++) {
      bitCount = 0;
      byteOut = 0;

      for (int j = 0; j < width; j++) {
        if (bitCount > 7) {
          file << byteOut;

          bitCount = 0;
          byteOut = 0;
        }

        if (!getPixel(j, i, false)) {
          byteOut |= 1U << (7 - bitCount);
        }

        bitCount++;
      }

      if (bitCount != 0) {
        file << byteOut;
      }
    }

    file.close();
  }

  void exportToPGM(std::string path) {
    std::ofstream file;
    file.open(path, std::ios_base::out | std::ios_base::binary);

    file << "P5\n";
    file << std::to_string(getWidth()) << ' ' << std::to_string(getHeight()) << '\n';
    file << "255";
    file << '\n';

    for (size_t index = 0; index < getArea(); index++) {
      file << static_cast<uint8_t>(getPixel(index, false) ? 255 : 0);
    }

    file.close();
  }

  void exportToPPM(std::string path) {
    std::ofstream file;
    file.open(path, std::ios_base::out | std::ios_base::binary);

    file << "P6\n";
    file << std::to_string(getWidth()) << ' ' << std::to_string(getHeight()) << '\n';
    file << "255";
    file << '\n';

    uint8_t c_out;

    for (size_t index = 0; index < getArea(); index++) {
      c_out = static_cast<uint8_t>(getPixel(index, false) ? 255 : 0);
      file << c_out << c_out << c_out;
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

  void clear() {
    fill(true);
  }

  void fill(unsigned char value) {
    std::fill_n(getPixels(), getArea(), value);
  }
};

}

#endif
