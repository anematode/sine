#ifndef PIXMAP_DEFINED_
#define PIXMAP_DEFINED_

#include <string>

#include <algorithm>
#include <exception>
#include <iostream>

#include "imageutils.h"
#include "color.h"
#include <fstream>

#include "stb_image_write.h"
#include "colorutils.h"

#include <cmath>
#include <functional>

namespace Sine::Graphics {
    namespace {
        /**
         * Helper function which isolates the return value of a functor.
         * @tparam F Functor type.
         * @tparam Ret Return value type.
         * @tparam Rest The rest of the parameters.
         * @return Type of return is return value of functor.
         */
        template<typename F, typename Ret, typename... Rest>
        Ret helper_get_return_type(Ret (F::*)(Rest...));

        /**
         * Helper function which isolates the return value of a functor.
         * @tparam F Functor type.
         * @tparam Ret Return value type.
         * @tparam Rest The rest of the parameters.
         * @return Type of return is return value of functor.
         */
        template<typename F, typename Ret, typename... Rest>
        Ret helper_get_return_type(Ret (F::*)(Rest...) const);

        /**
         * Helper function which isolates the number of arguments of a functor.
         * @tparam F Functor type.
         * @tparam Ret Return value type.
         * @tparam Rest The rest of the parameters.
         * @return Argument count.
         */
        template<typename F, typename Ret, typename... Rest>
        constexpr size_t helper_get_arg_count(Ret (F::*)(Rest...)) {
            return sizeof...(Rest);
        };

        /**
         * Helper function which isolates the number of arguments of a functor.
         * @tparam F Functor type.
         * @tparam Ret Return value type.
         * @tparam Rest The rest of the parameters.
         * @return Argument count.
         */
        template<typename F, typename Ret, typename... Rest>
        constexpr size_t helper_get_arg_count(Ret (F::*)(Rest...) const) {
            return sizeof...(Rest);
        };

        /**
         * Helper struct which isolates certain properties of a functor.
         * @tparam F Functor type.
         */
        template<typename F>
        struct get_functor_traits {
            typedef decltype(helper_get_return_type(&F::operator())) return_type;
            static const size_t arg_count = helper_get_arg_count(&F::operator());
        };

        /**
         * Set of constants allowing simple expression of how a functor should be applied.
         */
        namespace PixmapApply {
            const unsigned char NORETURN = 0,
                    RETURN = 1,
                    NOPASSINDEX = 0,
                    PASSINDEX = (1 << 1),
                    NOPASSPAIR = 0,
                    PASSPAIR = (1 << 2);
        };
    }

    /**
     * Pixmap is the base class for Graymap, Bitmap, RGBMap and RGBMap.
  It just abstracts a 2D array of pixels, given a template argument for the pixel type itself.
     * @tparam PixelColor Pixel type.
     */
    template<typename PixelColor>
    class Pixmap {
    private:
        /**
         * Applies a functor in a specified manner to all pixels of a Pixmap.
         * @tparam T Type of functor.
         * @tparam app Manner of application of functor.
         * @param func Functor itself.
         */
        template<typename T, unsigned char app = PixmapApply::NORETURN>
        inline void _apply(T func) {
            using namespace PixmapApply; // Pull the PixmapApply settings into here

            // "if constexpr" is a C++17 feature! No SFINAE needed here.
            if constexpr (app == (NORETURN | NOPASSINDEX | NOPASSPAIR)) {
                // Simply iterate through all pixels, passing them as a reference.
                for (auto &pix : *this) {
                    func(pix);
                }
            } else if constexpr ((app == (NORETURN | NOPASSINDEX | PASSPAIR)) ||
                                 (app == (NORETURN | PASSINDEX | PASSPAIR))) {
                // Pass pixel reference and pair (x, y)

                int index = 0;
                for (int j = 0; j < height; j++) {
                    for (int i = 0; i <
                                    width; i++) { // Notice the iteration is switched, so that index matches up correctly with i, j
                        func(getPixelUnsafe(index), i, j);
                        index++;
                    }
                }
            } else if constexpr (app == (NORETURN | PASSINDEX | NOPASSPAIR)) {
                // Iterate through all pixels, passing index.
                int index = 0;
                for (auto &pix : *this) {
                    func(pix, index);
                    index++;
                }
            } else if constexpr (app == (RETURN | NOPASSINDEX | NOPASSPAIR)) {
                // Iterate through all pixels, setting the pixel to the result of func
                for (auto &pix : *this) {
                    pix = func(pix);
                }
            } else if constexpr ((app == (RETURN | NOPASSINDEX | PASSPAIR)) ||
                                 (app == (RETURN | PASSINDEX | PASSPAIR))) {
                // Iterate through all pixels, pass pair, and set the pixel to the result of func
                int index = 0;

                for (int j = 0; j < height; j++) {
                    for (int i = 0; i < width; i++) {
                        setPixelUnsafe(index, func(getPixelUnsafe(index), i, j));
                        index++;
                    }
                }
            } else if constexpr (app == (RETURN | PASSINDEX | NOPASSPAIR)) {
                // Iterate through all pixels, pass index, and set the pixel to the result of func
                for (int i = 0; i < area; i++) {
                    setPixelUnsafe(i, func(getPixelUnsafe(i), i));
                }
            }
        }

        /**
         * Helper function which enables the RETURN attribute if the functor returns PixelColor, then forwards to _apply_a
         * @tparam T Functor type.
         * @param func Functor itself.
         */
        template<typename T,
                typename = typename std::enable_if<
                        std::is_same<typename get_functor_traits<T>::return_type,
                                PixelColor> // Check return type of functor with PixelColor
                        ::value>::type>
        inline void _apply_l(T func, int = 0) {

            _apply_a<T, PixmapApply::RETURN>(func); // Forwarding to _apply_a with enabled RETURN
        };

        template<typename T, typename = typename std::enable_if<
                !std::is_same<typename get_functor_traits<T>::return_type,
                        PixelColor> // Check return type of functor with PixelColor
                ::value>::type>
        // Accept if types are same
        inline void _apply_l(T func, double = 0) {

            _apply_a<T, PixmapApply::NORETURN>(func); // Forwarding to _apply_a with disabled RETURN
        };

        template<typename T, unsigned char opts, typename = typename std::enable_if<
                get_functor_traits<T>::arg_count == 1>::type>
        // Enable if only one argument is passed
        inline void _apply_a(T func, int = 0) {
            _apply<T, opts>(func); // Forward to _apply
        };

        template<typename T, unsigned char opts, typename = typename std::enable_if<
                get_functor_traits<T>::arg_count == 2>::type>
        // Enable if two arguments are passed
        inline void _apply_a(T func, double = 0) {
            _apply<T, opts | PixmapApply::PASSINDEX>(func); // Forward to _apply with PASSINDEX
        };

        template<typename T, unsigned char opts, typename = typename std::enable_if<
                get_functor_traits<T>::arg_count == 3>::type>
        // Enable if three arguments are passed
        inline void _apply_a(T func, long = 0) {
            _apply<T, opts | PixmapApply::PASSPAIR>(func); // Forward to _apply with PASSPAIR
        };

    protected:

        /*
         * Raw pixel pointer.
         */
        PixelColor *pixels;

        /*
         * Width of pixmap.
         */
        int width;

        /*
         * Height of pixmap.
         */
        int height;

        /*
         * Area of pixmap (i.e. width * height).
         */
        long area;

    public:
        using PixelType = PixelColor;

        /**
         * Size of PixelColor in bytes, used for interface to C libraries stbi_image and stbi_image_write.
         */
        const static int ColorSize = sizeof(PixelColor);

        /**
         * Pixmap constructor initializing a blank canvas with dimensions width x height.
         * @param width Pixmap width.
         * @param height Pixmap height.
         */
        Pixmap(int width, int height);

        /**
         * Pixmap copy constructor.
         * @param pixmap Copied Pixmap instance.
         */
        Pixmap(const Pixmap<PixelColor> &pixmap);

        /**
         * Pixmap move constructor.
         * @param pixmap Moved Pixmap instance.
         */
        Pixmap(Pixmap<PixelColor> &&pixmap) noexcept;

        /**
         * Pixmap move assignment operator.
         * @param pixmap Moved pixmap instance.
         * @return Returns *this.
         */
        Pixmap<PixelColor> &operator=(Pixmap<PixelColor> &&pixmap) noexcept;

        /**
         * Pointer used for C++11-style iteration.
         * @return Pointer to first element.
         */
        PixelColor *begin();

        /**
         * Pointer used for C++11-style iteration.
         * @return Pointer to one element-size past last element.
         */
        PixelColor *end();

        /**
         * Destructor which delete[]s pixels.
         */
        ~Pixmap();

        /**
         * Throws an error if index is out of bounds, or does nothing.
         * @param index Checked index.
         */
        void checkIndex(int index) const;

        /**
         * Throws an error if pair is out of bounds, or does nothing.
         * @param x Checked x coordinate.
         * @param y Checked y coordinate.
         */
        void checkPair(int x, int y) const;

        /**
         * Getter for width.
         * @return Pixmap width.
         */
        int getWidth() const;

        /**
         * Getter for height.
         * @return Pixmap height.
         */
        int getHeight() const;

        /**
         * Getter for raw pixel pointer, used for stbi interfacing.
         * @return Pixmap pixel pointer.
         */
        PixelColor *getPixels() const;

        /**
         * Getter for area.
         * @return Pixmap area.
         */
        long getArea() const;

        /**
         * Sets raw pixel pointer for stbi interfacing.
         * @param p New pixel pointer.
         */
        void setPixelPointer(void *p);

        /**
         * Returns whether an index is contained in the Pixmap.
         * @param index Checked index.
         * @return Whether the index is contained.
         */
        bool indexContained(int index) const;

        /**
         * Returns whether a point is contained in the Pixmap.
         * @param x Checked x coordinate.
         * @param y Checked y coordinate.
         * @return Whether the point is contained.
         */
        bool pairContained(int x, int y) const;

        /**
         * Converts a pair (x, y) to corresponding index in pixels.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @return Corresponding index.
         */
        int pairToIndex(int x, int y) const;

        /**
         * Overloaded operator() for ease of access to members without setPixel.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @return Reference to pixel at (x, y), or pixels[x * width + y].
         */
        PixelColor &operator()(int x, int y);

        /**
         * Overloaded operator() for ease of access to members without setPixel.
         *
         * Performs bounds checking.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @return Value of pixel at (x, y), or pixels[x * width + y].
         */
        PixelColor operator()(int x, int y) const;

        /**
         * Overloaded operator() for ease of access to members without setPixel.
         *
         * Performs bounds checking.
         * @param index Index of pixel
         * @return Reference to pixel at index, or pixels[index].
         */
        PixelColor &operator()(int index);

        /**
         * Overloaded operator() for ease of access to members without setPixel.
         *
         * Performs bounds checking.
         * @param index Index of pixel
         * @return Value of pixel at index, or pixels[index].
         */
        PixelColor operator()(int index) const;

        /**
         * Returns pixel at index index.
         *
         * Performs bounds checking.
         * @param index Accessed index.
         * @return Value of pixel at index.
         */
        PixelColor getPixel(int index) const;

        /**
         * Returns pixel at (x, y).
         *
         * Performs bounds checking.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @return Value of pixel at (x, y).
         */
        PixelColor getPixel(int x, int y) const;

        /**
         * Returns pixel at index index.
         *
         * Performs bounds checking.
         * @param index Accessed index.
         * @return Reference to pixel at index.
         */
        PixelColor &getPixel(int index);

        /**
         * Returns reference to pixel at (x, y).
         *
         * Performs bounds checking.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @return Reference to pixel at (x, y).
         */
        PixelColor &getPixel(int x, int y);

        /**
         * Sets pixel at index index to c.
         *
         * Performs bounds checking.
         * @param index Index of pixel to set.
         * @param c Value to set.
         */
        void setPixel(int index, PixelColor c);

        /**
         * Sets pixel at (x, y) to c.
         *
         * Performs bounds checking.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @param c Value to set.
         */
        void setPixel(int x, int y, PixelColor c);

        /**
         * Sets pixel at index index to c.
         *
         * Performs bounds checking.
         * @param index Index of pixel to set.
         * @param c Value to set.
         */
        void setPixelNoThrow(int index, PixelColor c);

        /**
         * Sets pixel at (x, y) to c.
         *
         * Performs bounds checking.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @param c Value to set.
         */
        void setPixelNoThrow(int x, int y, PixelColor c);

        /**
         * Gets pixel at index index.
         *
         * No bounds checking.
         * @param index Index to access.
         * @return Value of pixel.
         */
        PixelColor getPixelUnsafe(int index) const;

        /**
         * Gets pixel at (x, y).
         *
         * No bounds checking.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @return Value of pixel at (x, y)
         */
        PixelColor getPixelUnsafe(int x, int y) const;

        /**
         * Gets pixel at index index.
         *
         * No bounds checking.
         * @param index Index to access.
         * @return Reference to pixel.
         */
        PixelColor &getPixelUnsafe(int index);

        /**
         * Gets pixel at (x, y).
         *
         * No bounds checking.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @return Reference to pixel at (x, y)
         */
        PixelColor &getPixelUnsafe(int x, int y);

        /**
         * Sets pixel at index index to c.
         *
         * No bounds checking.
         * @param index Index to access.
         * @param c Value to set.
         */
        void setPixelUnsafe(int index, PixelColor c);

        /**
         * Sets pixel at (x, y) to c.
         *
         * No bounds checking.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @param c Value to set.
         */
        void setPixelUnsafe(int x, int y, PixelColor c);

        /**
         * Export to file, automatically deducing image type.
         * @param filename Path of exported file.
         * @param type Type of image, default deduced from filename.
         * @return Whether the export succeeded.
         */
        bool exportToFile(std::string filename,
                          ImageType type = ImageType::UNKNOWN);

        /**
         * Subsample the Pixmap and return a new Pixmap.
         * @param x Factor to subsample by.
         * @return Subsampled Pixmap.
         */
        Pixmap sample(double x) const;

        /**
         * Export to BMP.
         * @param file Path to file.
         */
        void exportToBMP(std::string file);

        /**
         * Export to JPG.
         * @param file Path to file.
         * @param quality Quality of JPG output as a percentage (i.e. lossiness of compression).
         */
        void exportToJPEG(std::string file, int quality = 90);

        /**
         * Export to GIF.
         * @param file Path to file.
         */
        void exportToGIF(std::string file);

        /**
         * Export to PNG.
         * @param file Path to file.
         */
        void exportToPNG(std::string file);

        /**
         * Export to PBM.
         * @param file Path to file.
         */
        void exportToPBM(std::string file);

        /**
         * Export to PPM.
         * @param file Path to file.
         */
        void exportToPPM(std::string file);

        /**
         * Export to PGM.
         * @param file Path to file.
         */
        void exportToPGM(std::string file);

        /**
         * Applies a functor to the Pixmap with automatic deduction of how it should be applied.
         *
         * The functor can accept PixelColor and return PixelColor, or accept a reference to PixelColor and be void.
         * It can also accept one additional argument, the index, or two additional arguments, which are x and y of each pixel.
         * @tparam T Type of functor, which is automatically deduced most of the time so no decltype is needed.
         * @param func The functor itself.
         */
        template<typename T>
        inline void apply(T func) {
            _apply_l<T>(func); // Forward to _apply_l so that it can be handled with SFINAE internally
        }


        /**
         * Safely pastes a Pixmap at position (x, y), with the top left of the Bitmap coinciding with (x, y).
         * @tparam T Pixel type of Pixmap.
         * @param image Pixmap<T> instance.
         * @param x X coordinate of paste point.
         * @param y Y coordinate of paste point.
         */
        template<typename T>
        inline void pasteImage(const Pixmap<T> &image, int x = 0, int y = 0) {
            int minHeight = std::min(height, image.getHeight() + y); // Height to start iterating from
            int minWidth = std::min(width, image.getWidth() + x); // Width to start iterating from

            int sample_x = -std::min(x, 0); // Height to start iterating from in image
            int sample_y; // Width to start iterating from in image

            for (int i = std::max(x, 0); i < minWidth; i++) {
                sample_y = -std::min(y, 0);
                for (int j = std::max(y, 0); j < minHeight; j++) {
                    setPixelUnsafe(i, j, ColorUtils::getColor<PixelColor>(
                            image.getPixelUnsafe(sample_x, sample_y))); // Set to pure white or pure black
                    sample_y++;
                }
                sample_x++;
            }
        }

        /**
         * Copies from Pixmap<T>
         * @tparam T Internal type of Pixmap
         * @param pixmap Pixmap instance.
         * @param opacity Opacity of Canvas after copying.
         */
        template<typename T>
        inline void copyFrom(const Pixmap<T> &pixmap) {
            if (pixmap.getWidth() != width || pixmap.getHeight() != height) {
                throw std::logic_error("Pixmaps must be of the same dimensions for copying.");
            } else {
                int index = 0;
                for (auto &i : *this) {
                    i = ColorUtils::getColor<PixelColor>(pixmap.getPixelUnsafe(index));
                    index++;
                }
            }
        }
    };

    // Convenient typedefs for ease of reading
    typedef Pixmap<bool> Bitmap;
    typedef Pixmap<RGB> RGBMap;
    typedef Pixmap<uint8_t> Graymap;
    typedef Pixmap<RGBA> RGBAMap;

} // namespace Sine


#endif
