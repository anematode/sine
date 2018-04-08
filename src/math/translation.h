//
// Created by Timothy Herchen on 3/10/18.
//

#ifndef VISUALIZATION_TRANSLATION_H
#define VISUALIZATION_TRANSLATION_H

#include "transformation.h"
#include "vec2.h"

namespace Sine {
    namespace Math {
        class Translation : public Transformation {
            double x;
            double y;
        public:
            Translation(int _x, int _y);

            template<typename T>
            inline auto transform(T a) -> decltype(T::translate) {
                return a.translate(x, y);
            }
        };
    }
}

#endif //VISUALIZATION_TRANSLATION_H
