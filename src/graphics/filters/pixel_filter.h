#ifndef PIXEL_FILTER_DEFINED_
#define PIXEL_FILTER_DEFINED_

#include "filter.h"

namespace Vis {
    namespace Filters {
        namespace {
            template<typename T>
            using Func_NoRef = T (*)(T);

            template<typename T>
            using Func_Ref = void (*)(T &);
        }

        template<typename T, typename Func_Type>
        class PixelFilter : public Filter {
        private:
            Func_Type func;
        public:
            PixelFilter(Func_Type &);

            void applyTo(Pixmap<T> &p);
        };

        template<typename T>
        class PixelFilter<T, Func_Ref<T>> {
        private:
            void (*func)(T &);

        public:
            PixelFilter(void (*)(T &));

            void applyTo(Pixmap<T> &p);
        };

        template<typename T>
        class PixelFilter<T, Func_NoRef<T>> {
        private:
            T (*func)(T);

        public:
            PixelFilter(T (*)(T));

            void applyTo(Pixmap<T> &p);
        };

        template<typename T>
        void PixelFilter<T, Func_Ref<T>>::applyTo(Pixmap<T> &p) {
            for (T &a : p) {
                func(a);
            }
        }

        template<typename T>
        void PixelFilter<T, Func_NoRef<T>>::applyTo(Pixmap<T> &p) {
            for (T &a : p) {
                a = func(a);
            }
        }

        template<typename T, typename Func_Type>
        PixelFilter<T, Func_Type>::PixelFilter(Func_Type &f) {
            func = f;
        }

        template<typename T, typename Func_Type>
        void PixelFilter<T, Func_Type>::applyTo(Pixmap<T> &p) {
            for (T &a : p) {
                func(a);
            }
        }

        template<typename T>
        PixelFilter<T, Func_Ref<T>> makePixelFilter(void (*f)(T &)) {
            return PixelFilter<T, Func_Ref<T>>(f);
        }

        template<typename T>
        PixelFilter<T, Func_NoRef<T>> makePixelFilter(T (*f)(T)) {
            return PixelFilter<T, Func_NoRef<T>>(f);
        }
    }
}

#endif
