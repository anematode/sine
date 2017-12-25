#ifndef GRAYMAP_DEFINED_
#define GRAYMAP_DEFINED_

#include "pixmap.h"
#include "imageutils.h"
#include <fstream>
#include <exception>
#include <iostream>

namespace Vis {

class Graymap : public Pixmap<unsigned char> {
public:
  Graymap(int width, int height) : Pixmap<unsigned char>(width, height) {

  }

  void exportToBMP(std::string path) {
    
  }

  void exportToJPEG(std::string file) {

  }

  void exportToGIF(std::string file) {

  }

  void exportToPNG(std::string file) {

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

        if (getPixel(j, i, false) < 128) {
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

  void exportToPGM(std::string file) {

  }

  void exportToPPM(std::string file) {

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
};

}

#endif
