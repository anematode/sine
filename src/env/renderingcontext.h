//
// Created by Timothy Herchen on 1/29/18.
//

#ifndef VISUALIZATION_RENDERINGCONTEXT_H
#define VISUALIZATION_RENDERINGCONTEXT_H

#include "graphics/canvas.h"
#include "graphic.h"
#include "graphics/colorutils.h"
#include <vector>
#include <map>

namespace Sine::Env {
    using namespace Sine::Graphics;

    /**
     * Class representing a rendering context which supports graphic children.
     */
    class RenderingContext : public Canvas {
    private:
        std::map<std::string, Graphic *> graphics;
    public:
        /**
         * Basic constructor given width and height
         * @param width Context width.
         * @param height Context height.
         */
        RenderingContext(int width, int height);

        /**
         * Constructor from Bitmap.
         * @param p Bitmap instance.
         */
        explicit RenderingContext(const Bitmap &p);

        /**
         * Constructor from Graymap.
         * @param p Graymap instance.
         */
        explicit RenderingContext(const Graymap &p);

        /**
         * Constructor from RGBMap.
         * @param p RGBMap instance.
         */
        explicit RenderingContext(const RGBMap &p);

        /**
         * Constructor from RGBAMap.
         * @param p RGBAMap instance.
         */
        explicit RenderingContext(const RGBAMap &p);

        /**
         * Constructor from Canvas.
         * @param p Canvas instance.
         */
        explicit RenderingContext(const Canvas &p);

        /**
         * Function called to render the context.
         */
        void render();

        /**
         * Add a graphic instance. Note that RenderingContext does not participate in destruction of Graphics.
         * @param id Name of the graphic.
         * @param graphic Instance of graphic as pointer.
         */
        void addGraphic(std::string id, Graphic *graphic);

        /**
         * Add a graphic instance. Note that RenderingContext does not participate in destruction of Graphics.
         * @param id Name of the graphic.
         * @param graphic Instance of graphic as reference.
         */
        void addGraphic(std::string id, Graphic &graphic);

        /**
         * Gets graphic with name id.
         * @param id Name of graphic to find.
         * @return Reference to graphic.
         */
        Graphic &getGraphic(std::string id);

        /**
         * Remove graphic from context with name id.
         * @param id Name of graphic.
         */
        void removeGraphic(std::string id);
    };
}


#endif //VISUALIZATION_RENDERINGCONTEXT_H
