#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <exception>

class shape2 {
public:
    using point = std::pair<float, float>;

    shape2(float x = 0.0f, float y = 0.0f) : m_pos(x, y) {

    }

    shape2(point pos) : m_pos(pos) {

    }

    point pos() const {
        return m_pos;
    }
    
    float x() const { return m_pos.first; }
    float y() const { return m_pos.second;}
    virtual void draw();
    virtual float area() = 0;
protected:
    point m_pos;
};

class rect2 : public shape2 {
public:
    using side_data = std::pair<float, float>;
    
    rect2(float x = 0.0f, float y = 0.0f, float length = 1.0f, float width = 1.0f) : shape2(length, width), m_sides(length, width) {

    }
    
    rect2(shape2::point pos, side_data sides) : shape2(pos), m_sides(sides) {

    }

    side_data sides() const { return m_sides; }

    float length() const { return m_sides.first; }
    float width() const { return m_sides.second; }

    void draw();
    float area();
private:
    side_data m_sides;
};

class eqtri2 : public shape2 {
public:
    eqtri2(float x = 0.0, float y = 0.0, float side = 1.0) : shape2(x, y), m_side(side) {
    }

    eqtri2(shape2::point pos = {0, 0}, float side = 1.0) : shape2(pos), m_side(side) {
    }

    float side() const { return m_side; }

    void draw();
    float area();
private:
    float m_side;
};

#endif /* HEADER_HPP */

