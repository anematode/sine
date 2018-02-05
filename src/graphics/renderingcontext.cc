//g
// Created by Timothy Herchen on 1/29/18.
//

#include "renderingcontext.h"

namespace Sine::Graphics {
    RenderingContext::RenderingContext(int width, int height) : Canvas(width, height) {

    }

    RenderingContext::RenderingContext(const Bitmap &p) : Canvas(p) {

    }

    RenderingContext::RenderingContext(const Graymap &p) : Canvas(p) {

    }

    RenderingContext::RenderingContext(const RGBMap &p) : Canvas(p) {

    }

    RenderingContext::RenderingContext(const RGBAMap &p) : Canvas(p) {

    }

    RenderingContext::RenderingContext(const Canvas &p) : Canvas(p) {

    }

    void RenderingContext::render() {
        for (auto g: graphics) {
            g.second->render(*this);
        }
    }

    void RenderingContext::removeGraphic(std::string id) {
        graphics.erase(id);
    }

    void RenderingContext::addGraphic(std::string id, Graphic &graphic) {
        graphics[id] = &graphic;
    }

    void RenderingContext::addGraphic(std::string id, Graphic *graphic) {
        graphics[id] = graphic;
    }

    Graphic &RenderingContext::getGraphic(std::string id) {
        return *graphics[id];
    }
}
