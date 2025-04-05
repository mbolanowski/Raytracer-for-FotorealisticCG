//
// Created by cheily on 24.03.2025.
//

#pragma once
#include <algorithm>
#include <iostream>

namespace mathgik {

    template<typename T, int size>
    struct vec;

    template<typename T>
    union vec2 {
        struct {
            T x, y;
        };
        struct {
            T a, b;
        };
        vec<T, 2> data;

        vec2() : x(0), y(0) {}
        vec2(T x, T y) : x(x), y(y) {}
        vec2(T scalar) : x(scalar), y(scalar) {}
        vec2(vec<T, 2> vector) : data(vector) {}
    };

    template<typename T>
    union vec3 {
        struct {
            T x, y, z;
        };
        struct {
            T r, g, b;
        };
        vec<T, 3> data;

        vec3() : x(0), y(0), z(0) {}
        vec3(T x, T y, T z) : x(x), y(y), z(z) {}
        vec3(T scalar) : x(scalar), y(scalar), z(scalar) {}
        vec3(vec<T, 3> vector) : data(vector) {}
    };

    template<typename T>
    union vec4 {
        struct {
            T r, g, b, a;
        };
        struct {
            T x, y, z, w;
        };
        vec<T, 4> data;

        vec4() : x(0), y(0), z(0), w(0) {}
        vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
        vec4(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}
        vec4(vec<T, 4> vector) : data(vector) {}

        vec4 & operator=(const vec4 &v) {
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
            return *this;
        }
    };

    using i2 = vec2<int>;
    using i3 = vec3<int>;
    using i4 = vec4<int>;

    using f2 = vec2<float>;
    using f3 = vec3<float>;
    using f4 = vec4<float>;

    using b2 = vec2<bool>;
    using b3 = vec3<bool>;
    using b4 = vec4<bool>;

    template<typename T, int size>
    struct vec {
        T data[size];

        T mag() const {
            T sum = 0;
            for (int i = 0; i < size; i++) {
                sum += data[i] * data[i];
            }
            return std::sqrt(sum);
        }

        vec<T, size> norm() const {
            return *this / mag();
        }

        vec & operator-() {
            for (int i = 0; i < size; i++) {
                data[i] = -data[i];
            }
            return *this;
        }

        vec operator-() const {
            vec result;
            for (int i = 0; i < size; i++) {
                result[i] = -data[i];
            }
            return result;
        }

        T &operator[](int i) {
            return data[i];
        }

        const T &operator[](int i) const {
            return data[i];
        }

        vec operator+(const vec &v) const {
            vec result;
            for (int i = 0; i < size; i++) {
                result[i] = data[i] + v[i];
            }
            return result;
        }

        vec &operator+=(const vec &v) {
            for (int i = 0; i < size; i++) {
                data[i] += v[i];
            }
            return *this;
        }

        vec operator-(const vec &v) const {
            vec result;
            for (int i = 0; i < size; i++) {
                result[i] = data[i] - v[i];
            }
            return result;
        }

        vec &operator-=(const vec &v) {
            for (int i = 0; i < size; i++) {
                data[i] -= v[i];
            }
            return *this;
        }

        vec operator*(T s) const {
            vec result;
            for (int i = 0; i < size; i++) {
                result[i] = data[i] * s;
            }
            return result;
        }

        vec &operator*=(T s) {
            for (int i = 0; i < size; i++) {
                data[i] *= s;
            }
            return *this;
        }

        vec operator*(const vec &v) const {
            vec result;
            for (int i = 0; i < size; i++) {
                result[i] = data[i] * v[i];
            }
            return result;
        }

        vec &operator*=(const vec &v) {
            for (int i = 0; i < size; i++) {
                data[i] *= v[i];
            }
            return *this;
        }

        vec operator/(T s) const {
            vec result;
            for (int i = 0; i < size; i++) {
                result[i] = data[i] / s;
            }
            return result;
        }

        vec &operator/=(T s) {
            for (int i = 0; i < size; i++) {
                data[i] /= s;
            }
            return *this;
        }

        vec operator/(const vec &v) const {
            vec result;
            for (int i = 0; i < size; i++) {
                result[i] = data[i] / v[i];
            }
            return result;
        }

        vec &operator/=(const vec &v) {
            for (int i = 0; i < size; i++) {
                data[i] /= v[i];
            }
            return *this;
        }
    };

    template<typename T, int size>
    std::ostream &operator<<(std::ostream &os, const vec<T, size> &v) {
        os << "[";
        for (int i = 0; i < size; i++) {
            os << +v.data[i];
            if (i < size - 1) os << ",";
        }
        os << "]";
        return os;
    }
} // mathgik
