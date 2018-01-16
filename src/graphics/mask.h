#ifndef MASK_DEFINED_
#define MASK_DEFINED_

#error "This doesn't work yet!"

#include "pixmap.h"
#include "color.h"

namespace Vis {
  template <typename PixelColor>
  class Mask {
  public:
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual int getArea() const = 0;

    virtual bool pixelAllowed(int i) const = 0;
    virtual bool pixelAllowed(int x, int y) const = 0;

    virtual PixelColor getPixel(int i, bool safe = true) = 0;
    virtual PixelColor getPixel(int x, int y, bool safe = true) = 0;

    virtual void setPixel(int x, int y, PixelColor k, bool safe = true) = 0;
    virtual void setPixel(int i, PixelColor k, bool safe = true) = 0;
  };

  typedef Mask<bool> Bitmask;
  typedef Mask<unsigned char> Graymask;
  typedef Mask<RGB> RGBMask;
  typedef Mask<RGBA> RGBAMask;

  template <typename PixelColor>
  class SimpleMask : public Mask<PixelColor> {
  private:
    Pixmap<PixelColor>* map;
    bool* maskPointer;

    int width, height, area;
  public:
    SimpleMask(Pixmap<PixelColor>* p);
    ~SimpleMask();

    int pairToIndex(int x, int y) const;

    bool pixelAllowed(int i) const;
    bool pixelAllowed(int x, int y) const;

    int getWidth() const;
    int getHeight() const;
    int getArea() const;

    void allowPixel(int i);
    void allowPixel(int x, int y);

    void disallowPixel(int i);
    void disallowPixel(int x, int y);

    PixelColor getPixel(int x, int y, bool safe = true);
    PixelColor getPixel(int i, bool safe = true);

    void setPixel(int x, int y, PixelColor k, bool safe = true);
    void setPixel(int i, PixelColor k, bool safe = true);
  };

  template <typename PixelColor>
  SimpleMask<PixelColor>::SimpleMask(Pixmap<PixelColor>* p) {
    map = p;

    width = p->getWidth();
    height = p->getHeight();
    area = p->getArea();

    maskPointer = new bool[width * height]();
  }

  template <typename PixelColor>
  SimpleMask<PixelColor>::~SimpleMask() {
    delete[] maskPointer;
  }

  template <typename PixelColor>
  int SimpleMask<PixelColor>::pairToIndex(int x, int y) const {
    return x * width + y;
  }

  template <typename PixelColor>
  bool SimpleMask<PixelColor>::pixelAllowed(int i) const {
    return (i >= 0 && i < area && maskPointer[i]);
  }

  template <typename PixelColor>
  bool SimpleMask<PixelColor>::pixelAllowed(int x, int y) const {
    return (x >= 0 && x < width && y >= 0 && y < height && maskPointer[pairToIndex(x, y)]);
  }

  template <typename PixelColor>
  void SimpleMask<PixelColor>::allowPixel(int i) {
    maskPointer[i] = true;
  }

  template <typename PixelColor>
  void SimpleMask<PixelColor>::allowPixel(int x, int y) {
    maskPointer[pairToIndex(x, y)] = true;
  }

  template <typename PixelColor>
  void SimpleMask<PixelColor>::disallowPixel(int i) {
    maskPointer[i] = false;
  }

  template <typename PixelColor>
  void SimpleMask<PixelColor>::disallowPixel(int x, int y) {
    maskPointer[pairToIndex(x, y)] = false;
  }

  template <typename PixelColor>
  int SimpleMask<PixelColor>::getWidth() const {
    return width;
  }

  template <typename PixelColor>
  int SimpleMask<PixelColor>::getHeight() const {
    return height;
  }

  template <typename PixelColor>
  int SimpleMask<PixelColor>::getArea() const {
    return height;
  }


  template <typename PixelColor>
  void SimpleMask<PixelColor>::setPixel(int x, int y, PixelColor k, bool safe) {
    if (!safe || (safe && pixelAllowed(x, y))) {
      map->setPixel(x, y, k);
    }
  }

  template <typename PixelColor>
  void SimpleMask<PixelColor>::setPixel(int i, PixelColor k, bool safe) {
    if (!safe || (safe && pixelAllowed(i))) {
      map->setPixel(i, k);
    }
  }

  template <typename PixelColor>
  PixelColor SimpleMask<PixelColor>::getPixel(int x, int y, bool safe) {
    return map->getPixel(x, y, safe);
  }

  template <typename PixelColor>
  PixelColor SimpleMask<PixelColor>::getPixel(int i, bool safe) {
    return map->getPixel(i, safe);
  }
}

#endif
