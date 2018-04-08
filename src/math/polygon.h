//
// Created by Timothy Herchen on 4/7/18.
//

#ifndef VISUALIZATION_POLYGON_H
#define VISUALIZATION_POLYGON_H


#include "segmentchain.h"
#include "cycle.h"

namespace Sine::Math {
    class Polygon : public Cycle {
    private:
        std::vector<Vec2d> points;
    public:
        explicit Polygon(const std::vector<Vec2d> &pts);

        int count();

        Vec2d start() override;

        Vec2d end() override;

        double length() override;

        BoundingBox boundingBox() override;

        void draw(Graphics::Canvas &c, Graphics::Pen &pen) override;

        void addPoint(const Vec2d &c);

        void translateBy(const Vec2d &a) override;

        void rotateBy(GeometryUtils::radians theta, const Vec2d &a) override;

        void fillDraw(Graphics::Canvas &c, Graphics::Pen &pen) override;

        template<typename C>
        inline void drawToFunc(C func);
    };

    template<typename C>
    inline void Polygon::drawToFunc(C func) {
        const auto box = boundingBox();

        for (int x = box.c1.x - 1; x < box.c2.x + 1; x++) {
            for (int y = box.c1.y - 1; y < box.c2.y + 1; y++) {

            }
        }
    }
}

#endif //VISUALIZATION_POLYGON_H
