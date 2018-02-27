//
// Created by Timothy Herchen on 2/24/18.
//

#ifndef VISUALIZATION_GEOMETRY_H
#define VISUALIZATION_GEOMETRY_H

#include "boundingbox.h"

namespace Sine {
    namespace Math {
        class Geometry {
            virtual BoundingBox boundingBox() = 0;
        };
    }
}


#endif //VISUALIZATION_GEOMETRY_H
