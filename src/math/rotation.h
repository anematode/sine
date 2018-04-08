//
// Created by Timothy Herchen on 3/9/18.
//

#ifndef VISUALIZATION_ROTATION_H
#define VISUALIZATION_ROTATION_H

#include "geometryutils.h"
#include "transformation.h"

namespace Sine {
    namespace Math {
        class Rotation : public Transformation {
            double x;
            double y;
            double angle;
        public:
            template<typename T>
            inline auto transform(T a) -> decltype(T::rotate) {
                return T::rotate(angle, x, y);
            }
        };

        template<>
        inline Vec2d Rotation::transform(Vec2d a) {
            return GeometryUtils::rotate(a, angle, x, y);
        }
    }
}


#endif //VISUALIZATION_ROTATION_H
