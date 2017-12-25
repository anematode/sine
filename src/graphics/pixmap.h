#ifndef PIXMAP_DEFINED_
#define PIXMAP_DEFINED_

#include <string>

#include <algorithm>
#include <exception>
#include <iostream>

#include "imageutils.h"
#include "../math/vec2.h"

namespace Vis {

template <typename PixelColor> class Pixmap {
private:
  PixelColor *pixels;
  int width;
  int height;
  size_t area;

public:
  Pixmap(int width, int height);
  Pixmap(const Pixmap& p);
  Pixmap(Pixmap&& p);

  ~Pixmap();

  inline void checkIndex(int index) const;
  inline void checkPair(int x, int y) const;

  int getWidth() const;
  int getHeight() const;
  PixelColor *getPixels() const;
  size_t getArea() const;

  inline bool indexContained(int index) const;
  inline bool pairContained(int x, int y) const;
  inline int pairToIndex(int x, int y) const;

  PixelColor getPixel(int index, bool safe = true) const;
  PixelColor getPixel(int x, int y, bool safe = true) const;

  void setPixel(int index, PixelColor c, bool safe = true);
  void setPixel(int x, int y, PixelColor c, bool safe = true);
  virtual void clear();
  void fill(PixelColor color);

  virtual bool exportToFile(std::string file, ImageType type = ImageType::UNKNOWN);
};

template <typename PixelColor>
Pixmap<PixelColor>::Pixmap(int width, int height) {
  pixels = new PixelColor[width * height];
  this->width = width;
  this->height = height;
  area = width * height;

  clear();
}

template <typename PixelColor>
Pixmap<PixelColor>::Pixmap(const Pixmap& p) {
  pixels = new PixelColor[p.width * p.height];
  std::copy(p.pixels, pixels);

  this->width = p.width;
  this->height = p.height;
  area = width * height;

  clear();
}

template <typename PixelColor>
Pixmap<PixelColor>::Pixmap(Pixmap&& p) {
  pixels = p.pixels;
  p.pixels = nullptr;
}

template <typename PixelColor> Pixmap<PixelColor>::~Pixmap() {
  delete[] pixels;
}

template <typename PixelColor> int Pixmap<PixelColor>::getWidth() const {
  return width;
}

template <typename PixelColor> int Pixmap<PixelColor>::getHeight() const {
  return height;
}

template <typename PixelColor> size_t Pixmap<PixelColor>::getArea() const {
  return area;
}

template <typename PixelColor> PixelColor* Pixmap<PixelColor>::getPixels() const {
  return pixels;
}

template <typename PixelColor>
inline bool Pixmap<PixelColor>::indexContained(int index) const {
  return (0 <= index && index < static_cast<int>(area));
}

template <typename PixelColor>
inline bool Pixmap<PixelColor>::pairContained(int x, int y) const {
  return (0 <= x && x < width && 0 <= y && y < width);
}

template <typename PixelColor>
inline void Pixmap<PixelColor>::checkIndex(int index) const {
  if (!indexContained(index)) {
    throw std::out_of_range(
        "Tried to access pixel at index = " + std::to_string(index) +
        ", max index is " + std::to_string(area) + ".");
  }
}

template <typename PixelColor>
inline void Pixmap<PixelColor>::checkPair(int x, int y) const {
  if (!pairContained(x, y)) {
    throw std::out_of_range(
        "Tried to access pixel at x,y = " + Vec2f(x, y).toString() +
        ", max dimensions are " + Vec2f(width, height).toString() + ".");
  }
}

template <typename PixelColor>
inline int Pixmap<PixelColor>::pairToIndex(int x, int y) const {
  return y * width + x;
}

template <typename PixelColor>
PixelColor Pixmap<PixelColor>::getPixel(int index, bool safe) const {
  if (safe)
    checkIndex(index);

  return pixels[index];
}

template <typename PixelColor>
PixelColor Pixmap<PixelColor>::getPixel(int x, int y, bool safe) const {
  if (safe)
    checkPair(x, y);

  return pixels[pairToIndex(x, y)];
}

template <typename PixelColor>
void Pixmap<PixelColor>::setPixel(int index, PixelColor c, bool safe) {
  if (safe && !indexContained(index))
    return;

  pixels[index] = c;
}

template <typename PixelColor>
void Pixmap<PixelColor>::setPixel(int x, int y, PixelColor c, bool safe) {
  if (safe && !pairContained(x, y))
    return;

  pixels[pairToIndex(x, y)] = c;
}

template <typename PixelColor> void Pixmap<PixelColor>::clear() {
  fill(255);
}

template <typename PixelColor> void Pixmap<PixelColor>::fill(PixelColor c) {
  std::fill_n(pixels, area, c);
}

template <typename PixelColor>
bool Pixmap<PixelColor>::exportToFile(std::string file, ImageType type) {
  throw std::logic_error("This function is not implemented generically.");
}

} // namespace Vis

#endif