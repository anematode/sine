#ifndef VEC3_DEFINED_
#define VEC3_DEFINED_

#include <cmath>
#include <ostream>

namespace Sine {

    template<typename T = double>
    struct Vec3 {
        T x;
        T y;
        T z;

        Vec3() {
            x = 0;
            y = 0;
            z = 0;
        }

        Vec3(T x, T y, T z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        T distance() const;

        T distance(T, T, T) const;

        T distance(const Vec3 &) const;

        T distanceSquared() const;

        T distanceSquared(T, T, T) const;

        T distanceSquared(const Vec3 &) const;

        bool operator==(const Vec3 &) const;

        Vec3 operator+(const Vec3 &) const;

        Vec3 operator-(const Vec3 &) const;

        Vec3 operator*(T) const;

        Vec3 operator/(T) const;

        template<typename U>
        friend std::ostream &operator<<(std::ostream &, const Vec3<U> &);

        template<typename U, typename V>
        friend Vec3<U> operator*(V, const Vec3<U> &);

        template<typename U, typename V>
        friend Vec3<U> operator/(V, const Vec3<U> &);

        std::string toString() const;

        void operator+=(const Vec3 &);

        void operator-=(const Vec3 &);

        void operator*=(T);

        void operator/=(T);

        void add(T, T, T);

        void sub(T, T, T);

        void stretch(T);

        void squish(T);
    };

    template<typename T>
    T Vec3<T>::distance() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    template<typename T>
    T Vec3<T>::distance(T xx, T yy, T zz) const {
        T a = x - xx;
        T b = y - yy;
        T c = z - zz;

        return std::sqrt(a * a + b * b + c * c);
    }

    template<typename T>
    T Vec3<T>::distance(const Vec3 &vec) const {
        return distance(vec.x, vec.y, vec.z);
    }

    template<typename T>
    T Vec3<T>::distanceSquared(T xx, T yy, T zz) const {
        T a = x - xx;
        T b = y - yy;
        T c = z - zz;

        return a * a + b * b + c * c;
    }

    template<typename T>
    T Vec3<T>::distanceSquared(const Vec3 &vec) const {
        return distanceSquared(vec.x, vec.y, vec.z);
    }

    template<typename T>
    bool Vec3<T>::operator==(const Vec3 &vec) const {
        return (x == vec.x && y == vec.y && z == vec.z);
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator+(const Vec3 &vec) const {
        Vec3 result;

        result.x = vec.x + x;
        result.y = vec.y + y;
        result.z = vec.z + z;

        return result;
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator-(const Vec3 &vec) const {
        Vec3 result;

        result.x = vec.x - x;
        result.y = vec.y - y;
        result.z = vec.z - z;

        return result;
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator*(T a) const {
        Vec3 result;

        result.x = x * a;
        result.y = y * a;
        result.z = z * a;

        return result;
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator/(T a) const {
        Vec3 result;

        result.x = x / a;
        result.y = y / a;
        result.z = z / a;

        return result;
    }

    template<typename T>
    void Vec3<T>::operator+=(const Vec3 &vec) {
        x += vec.x;
        y += vec.y;
        z += vec.z;
    }

    template<typename T>
    void Vec3<T>::operator-=(const Vec3 &vec) {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
    }

    template<typename T>
    void Vec3<T>::operator*=(T a) {
        x *= a;
        y *= a;
        z *= a;
    }

    template<typename T>
    void Vec3<T>::operator/=(T a) {
        x /= a;
        y /= a;
        z /= a;
    }

    template<typename T>
    void Vec3<T>::add(T x, T y, T z) {
        this->x += x;
        this->y += y;
        this->z += z;
    }

    template<typename T>
    void Vec3<T>::sub(T x, T y, T z) {
        this->x -= x;
        this->y -= y;
        this->z -= z;
    }

    template<typename T>
    void Vec3<T>::stretch(T s) {
        this->x *= s;
        this->y *= s;
        this->z *= s;
    }

    template<typename T>
    void Vec3<T>::squish(T s) {
        this->x /= s;
        this->y /= s;
        this->z /= s;
    }

    template<typename T>
    std::string Vec3<T>::toString() const {
        return '(' + std::to_string(x) + ',' + std::to_string(y) + ',' + std::to_string(z) + ')';
    }

    template<typename T, typename U>
    Vec3<T> operator*(U n, const Vec3<T> &vec) {
        return Vec3<T>(vec.x * n, vec.y * n, vec.z * n);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const Vec3<T> &v) {
        os << v.x << ", " << v.y << ", " << v.z;
        return os;
    }

    typedef Vec3<float> Vec3f;
    typedef Vec3<double> Vec3d;

} // namespace Sine

#endif
