#ifndef CANVAS_DEFINED_
#define CANVAS_DEFINED_

#include "pixmap.h"

namespace Vis {
  template <typename T = RGBA>
  class Canvas : public Pixmap<T> {
  public:
    Canvas(int width, int height);
    Canvas(Pixmap<T>& p);
    ~Canvas();
  };

  template <typename T>
  Canvas<T>::Canvas(int w, int h) : Pixmap<T>{w, h} {

  }

  template <typename T>
  Canvas<T>::Canvas(Pixmap<T>& p) : Pixmap<T>{p} {

  }

  template <typename T>
  Canvas<T>::~Canvas() {

  }
}

#endif
