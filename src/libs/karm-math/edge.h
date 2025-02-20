#pragma once

#include "rect.h"
#include "vec.h"

namespace Karm::Math {

template <typename T>
union Edge {
    struct {
        Vec2<T> start{}, end{};
    };

    struct {
        T sx, sy, ex, ey;
    };

    Array<T, 4> _els;

    constexpr Edge()
        : _els{} {};

    constexpr Edge(Vec2<T> start, Vec2<T> end)
        : start(start), end(end) {}

    constexpr Edge(T x1, T y1, T x2, T y2)
        : start(x1, y1), end(x2, y2) {}

    constexpr Vec<T> delta() const {
        return {end.x - start.x, end.y - start.y};
    }

    constexpr Rect<T> bound() const {
        return Rect<T>::fromTwoPoint(start, end);
    }

    constexpr Edge<T> offset(T offset) {
        auto d = end - start;
        f64 scale = offset / d.len();
        Vec2<T> o = {-d.y * scale, d.x * scale};
        auto s = start + o;
        auto e = end + o;
        return {s, e};
    }

    constexpr Vec2<T> dir() const {
        return end - start;
    }

    constexpr Vec2<T> invDir() const {
        return start - end;
    }

    constexpr T len() const {
        return dir().len();
    }

    constexpr T lenSq() const {
        return dir().lenSq();
    }

    constexpr T operator[](isize i) const {
        return _els[i];
    }

    constexpr Edge operator+(Vec2<T> other) const {
        return {start + other, end + other};
    }

    constexpr Edge operator-(Vec2<T> other) const {
        return {start - other, end - other};
    }

    template <typename U>
    constexpr Edge<U> cast() const {
        return {
            start.template cast<U>(),
            end.template cast<U>(),
        };
    }

    constexpr Edge<T> swap() const {
        return {end, start};
    }

    constexpr bool hasNan() const {
        return start.hasNan() or end.hasNan();
    }

    constexpr bool degenerated() const {
        return start == end;
    }
};

using Edgei = Edge<isize>;

using Edgef = Edge<f64>;

} // namespace Karm::Math

template <typename T>
ReflectableTemplate$(Math::Edge<T>, sx, sy, ex, ey);
