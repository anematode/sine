//
// Created by Timothy Herchen on 2/24/18.
//

#ifndef VISUALIZATION_CYCLE_H
#define VISUALIZATION_CYCLE_H


#include "path.h"

namespace Sine {
    namespace Math {
        class Cycle : public Path {
            virtual void fillDraw(Graphics::Canvas &c, Graphics::Pen &p) = 0;
        };
    }
}


#endif //VISUALIZATION_CYCLE_H
