//
// Created by cheily on 26.03.2025.
//

#pragma once

namespace mathgik {

    inline int sign(int x) {
        return x < 0 ? -1 : x > 0 ? 1 : 0;
    }

    template<typename T, int size>
    vec<T, size> vlerp(const vec<T, size> &a, const vec<T, size> &b, float t) {
        vec<T, size> result;
        for (int i = 0; i < size; i++) {
            result[i] = a[i] + (b[i] - a[i]) * t;
        }
        return result;
    }

}