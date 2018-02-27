//
// Created by Timothy Herchen on 2/24/18.
//

#ifndef VISUALIZATION_THICKENER_H
#define VISUALIZATION_THICKENER_H

#include "circle.h"

namespace Sine {
    namespace Graphics {
        namespace Algorithms {
            template<typename Func>
            inline auto constexpr thickenForwardAliasedDraw(Func f, int r = 2) {
                return ([=](int x, int y) {
                    drawFilledCircle(x, y, r, f);
                });
            };
        }
    }
}


#endif //VISUALIZATION_THICKENER_H
