#pragma once

struct Point  {
    int x;
    int y;

    Point() : x(0), y(0) {}

    Point(int x_, int y_) : x(x_), y(y_) {}

    Point(const Point& other) {
        x = other.x;
        y = other.y;
    }

    Point& operator = (const Point& other) = default;

    Point& operator += (const Point& other) {
        x += other.x;
        y += other.y;
        return (*this);
    }

    Point operator + (const Point& other) const {
        Point p(*this);
        p += other;
        return p;
    }

    bool operator == (const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator != (const Point& other) const {
        return !(*this == other);
    }

    bool operator < (const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};