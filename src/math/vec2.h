#ifndef VEC2_DEFINED_
#define VEC2_DEFINED_

#include <cmath>
#include <ostream>
#include <cstdlib>
#include <complex>

namespace Sine::Math {

    /**
     * 2D Vector class.
     * @tparam T Internal type.
     */
    template<typename T = double>
    struct Vec2 {
        T x;
        T y;

        /**
         * Default constructor.
         */
        Vec2() {
            x = 0;
            y = 0;
        }

        /**
         * Simple constructor.
         * @param x X component
         * @param y Y component
         */
        Vec2(T x, T y) {
            this->x = x;
            this->y = y;
        }

        /**
         * Copy constructor.
         * @param v vector
         */
        Vec2(const Vec2 &v) {
            x = v.x;
            y = v.y;
        }

        /**
         * Distance from origin (i.e. magnitude).
         * @return sqrt(x * x + y * y)
         */
        T distance() const;

        /**
         * Distance to (_x, _y).
         * @param xx x
         * @param yy y
         * @return distance
         */
        T distance(T xx, T yy) const;

        /**
         * Distance to vec.
         * @param vec Vec2 instance.
         * @return distance
         */
        T distance(const Vec2 &vec) const;

        /**
         * Distance squared from origin (i.e. magnitude squared).
         * @return distance squared
         */
        T distanceSquared() const;

        /**
         * Distance squared from (_x, _y).
         * @param _x x
         * @param _y y
         * @return distance squared
         */
        T distanceSquared(T, T) const;

        /**
         * Distance squared from vec.
         * @param vec vector
         * @return distance squared
         */
        T distanceSquared(const Vec2 &vec) const;

        /**
         * Equality comparison.
         * @param vec vector
         * @return Whether the two are equal.
         */
        bool operator==(const Vec2 &vec) const;

        /**
         * Addition operation.
         * @param vec vector
         * @return *this + vector
         */
        Vec2 operator+(const Vec2 &vec) const;

        /**
         * Addition operation.
         * @param vec vector
         * @return *this - vector
         */
        Vec2 operator-(const Vec2 &vec) const;

        /**
         * Multiplication operation.
         * @param d scale factor
         * @return *this * d
         */
        Vec2 operator*(T d) const;

        /**
         * Dot product
         */
        T operator*(const Vec2 &vec) const;

        /**
         * Division operation.
         * @param d scale factor
         * @return *this / d
         */
        Vec2 operator/(T d) const;

        // I won't document this stuff because it's pretty obvious at this point. Maybe later.
        // TODO: Document Sine::Vec2, Sine::Vec3

        template<typename U>
        friend std::ostream &operator<<(std::ostream &os, const Vec2<U> &vec);

        template<typename U, typename V>
        friend Vec2<U> operator*(V, const Vec2<U> &vec);

        template<typename U, typename V>
        friend Vec2<U> operator/(V, const Vec2<U> &vec);

        std::string toString() const;

        template<typename U>
        inline explicit operator std::complex<U>() const {
            return std::complex<U>(x, y);
        }

        Vec2 &operator+=(const Vec2 &);

        Vec2 &operator-=(const Vec2 &);

        Vec2 &operator*=(T);

        Vec2 &operator/=(T);

        void add(T, T);

        void sub(T, T);

        void stretch(T);

        void squish(T);
    };

    template<typename T>
    inline T Vec2<T>::distance() const {
        return std::sqrt(x * x + y * y);
    }

    template<typename T>
    inline T Vec2<T>::distance(T xx, T yy) const {
        T a = x - xx;
        T b = y - yy;

        return std::sqrt(a * a + b * b);
    }

    template<typename T>
    inline T Vec2<T>::operator*(const Vec2 &vec) const {
        return vec.x * x + vec.y * y;
    }

    template<typename T>
    inline T Vec2<T>::distance(const Vec2 &vec) const {
        return distance(vec.x, vec.y);
    }

    template<typename T>
    inline T Vec2<T>::distanceSquared() const {
        return x * x + y * y;
    }

    template<typename T>
    inline T Vec2<T>::distanceSquared(T xx, T yy) const {
        T a = x - xx;
        T b = y - yy;

        return a * a + b * b;
    }

    template<typename T>
    inline T Vec2<T>::distanceSquared(const Vec2 &vec) const {
        return distanceSquared(vec.x, vec.y);
    }

    template<typename T>
    inline bool Vec2<T>::operator==(const Vec2 &vec) const {
        return (x == vec.x && y == vec.y);
    }

    template<typename T>
    inline Vec2<T> Vec2<T>::operator+(const Vec2 &vec) const {
        Vec2 result;

        result.x = vec.x + x;
        result.y = vec.y + y;

        return result;
    }

    template<typename T>
    inline Vec2<T> Vec2<T>::operator-(const Vec2 &vec) const {
        Vec2 result;

        result.x = x - vec.x;
        result.y = y - vec.y;

        return result;
    }

    template<typename T>
    inline Vec2<T> Vec2<T>::operator*(T a) const {
        Vec2 result;

        result.x = x * a;
        result.y = y * a;

        return result;
    }

    template<typename T>
    inline Vec2<T> Vec2<T>::operator/(T a) const {
        Vec2 result;

        result.x = x / a;
        result.y = y / a;

        return result;
    }

    template<typename T>
    inline Vec2<T> &Vec2<T>::operator+=(const Vec2 &vec) {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    template<typename T>
    inline Vec2<T> &Vec2<T>::operator-=(const Vec2 &vec) {
        x -= vec.x;
        y -= vec.y;
        return *this;
    }

    template<typename T>
    inline Vec2<T> &Vec2<T>::operator*=(T a) {
        x *= a;
        y *= a;
        return *this;
    }

    template<typename T>
    inline Vec2<T> &Vec2<T>::operator/=(T a) {
        x /= a;
        y /= a;
        return *this;
    }

    template<typename T>
    inline void Vec2<T>::add(T x, T y) {
        this->x += x;
        this->y += y;
    }

    template<typename T>
    inline void Vec2<T>::sub(T x, T y) {
        this->x -= x;
        this->y -= y;
    }

    template<typename T>
    inline void Vec2<T>::stretch(T s) {
        this->x *= s;
        this->y *= s;
    }

    template<typename T>
    inline void Vec2<T>::squish(T s) {
        this->x /= s;
        this->y /= s;
    }

    template<typename T>
    inline std::string Vec2<T>::toString() const {
        return '(' + std::to_string(x) + ',' + std::to_string(y) + ')';
    }

    template<typename T, typename U>
    inline Vec2<T> operator*(U n, const Vec2<T> &vec) {
        return Vec2<T>(vec.x * n, vec.y * n);
    }

    template<typename T, typename U>
    inline Vec2<T> operator/(U n, const Vec2<T> &vec) {
        return Vec2<T>(vec.x / n, vec.y / n);
    }

    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const Vec2<T> &v) {
        os << '(' << v.x << ',' << v.y << ')';
        return os;
    }

    typedef Vec2<float> Vec2f;
    typedef Vec2<double> Vec2d;

} // namespace Sine

#endif
