#ifndef FILTER_DEFINED_
#define FILTER_DEFINED_

#include "../pixmap.h"

namespace Sine::Graphics {
    /**
     * Namespace containing all filters, which can be applied to Pixmaps.
     */
    namespace Filters {
        /**
         * Abstract base class for all filters.
         */
        class Filter {
            /**
             * Apply filter to Bitmap.
             * @param map Bitmap instance.
             */
            virtual void applyTo(Bitmap &map) = 0;

            /**
             * Apply filter to Graymap.
             * @param map Graymap instance.
             */
            virtual void applyTo(Graymap &map) = 0;

            /**
             * Apply filter to RGBMap.
             * @param map RGBMap instance.
             */
            virtual void applyTo(RGBMap &map) = 0;

            /**
             * Apply filter to RGBAMap.
             * @param map RGBAMap instance.
             */
            virtual void applyTo(RGBAMap &map) = 0;
        };

        /*template <typename T, typename Func>
        class FunctorFilter : public Filter {
        public:
            void applyTo(Bitmap &p);

            void applyTo(Graymap &p);

            void applyTo(RGBMap &p);

            void applyTo(RGBAMap &p);
        };*/
    }
}

#endif
