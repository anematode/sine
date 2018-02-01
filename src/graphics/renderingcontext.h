//
// Created by Timothy Herchen on 1/29/18.
//

#ifndef VISUALIZATION_RENDERINGCONTEXT_H
#define VISUALIZATION_RENDERINGCONTEXT_H

#include "canvas.h"
#include "graphic.h"
#include "colorutils.h"
#include <vector>
#include <map>

namespace Sine {
    class RenderingContext : public Canvas {
    private:
        typedef long Pref;

        std::map<std::string, Graphic *> graphics;
        std::map<std::string, Pref> prefs;
    public:
        RenderingContext(int width, int height);

        explicit RenderingContext(const Bitmap &p);

        explicit RenderingContext(const Graymap &p);

        explicit RenderingContext(const RGBMap &p);

        explicit RenderingContext(const RGBAMap &p);

        explicit RenderingContext(const Canvas &p);

        void render();

        void addGraphic(std::string id, Graphic *graphic);

        void addGraphic(std::string id, Graphic &graphic);

        Graphic &getGraphic(std::string id);

        void removeGraphic(std::string id);

        void setPref(const std::string &id, Pref pref);

        bool hasPref(const std::string &id);

        Pref getPref(const std::string &id);

        void removePref(const std::string &id);
    };
}


#endif //VISUALIZATION_RENDERINGCONTEXT_H
