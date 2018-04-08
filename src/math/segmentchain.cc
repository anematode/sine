//
// Created by Timothy Herchen on 3/1/18.
//

#include "segmentchain.h"
#include "../../tests/print.h"

namespace Sine {
    namespace Math {

        SegmentChain::SegmentChain() {

        }

        SegmentChain::SegmentChain(const std::vector<Vec2d> &pts) {
            points = pts;
        }

        int SegmentChain::count() {
            return points.size();
        }

        Vec2d SegmentChain::start() {
            return points[0];
        }

        Vec2d SegmentChain::end() {
            return points[count() - 1];
        }

        double SegmentChain::length() {
            double total_length = 0;

            Vec2d prevPoint = start();
            for (const Vec2d &c : points) {
                total_length += GeometryUtils::distance(c, prevPoint);
                prevPoint = c;
            }

            return total_length;
        }

        BoundingBox SegmentChain::boundingBox() {
            BoundingBox output{0, 0, 0, 0};

            Vec2d prevPoint = start();
            for (const Vec2d &c : points) {
                output = unionize(output, LineSegment(c, prevPoint).boundingBox());
                prevPoint = c;
            }

            return output;
        }

        void SegmentChain::draw(Graphics::Canvas &c, Graphics::Pen &pen) {
            Vec2d prevPoint = start();
            for (const Vec2d &a : points) {
                LineSegment(a, prevPoint).draw(c, pen);
                prevPoint = a;
            }
        }

        void SegmentChain::addPoint(const Vec2d &c) {
            points.push_back(c);
        }

        void SegmentChain::translateBy(const Vec2d &a) {
            for (Vec2d &w : points) {
                w += a;
            }
        }

        void SegmentChain::rotateBy(GeometryUtils::radians theta, const Vec2d &a) {
            for (Vec2d &w : points) {
                w = GeometryUtils::rotate(w, theta, a);
            }
        }

        double SegmentChain::area() {
            return 0;
        }

        std::vector<Vec2d> SegmentChain::sample(int count) {
            double inter_delta = length() / (count - 1);

            std::vector<Vec2d> out;

            Vec2d prev = start();

            out.push_back(prev);
            bool s_first = true;

            double length_until_next = inter_delta;

            double udd_sum = 0;

            for (const Vec2d &w : points) {

                if (s_first) {
                    s_first = false;
                    continue;
                }

                exd:

                double seg_length = LineSegment(prev, w).length();
                udd_sum += seg_length;

                if (length_until_next >= seg_length) {
                    length_until_next -= seg_length;
                } else {
                    double dim_ratio = length_until_next / seg_length;
                    double delta_x = w.x - prev.x;
                    double delta_y = w.y - prev.y;
                    length_until_next = inter_delta;

                    Vec2d next_sample{prev.x + dim_ratio * delta_x, prev.y + dim_ratio * delta_y};

                    out.push_back(next_sample);
                    double remaining = seg_length * (1 - dim_ratio);
                    if (length_until_next < remaining) {
                        prev = next_sample;
                        goto exd;
                    } else {
                        length_until_next -= remaining;
                    }
                }

                prev = w;
            }

            out.push_back(end());

            return out;
        }
    }
}