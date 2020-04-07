/**
 *
 */
#pragma once

#include "assert.h"

#include <cmath>
#include <cstdio>

class Vec2
{
public:
    Vec2() {}
    Vec2(float x, float y) : m_x(x), m_y(y) {}

    float magnitude() const { return sqrt((m_x * m_x) + (m_y * m_y)); }

    float angle() { return atan(m_y / m_x); }

    float x() { return m_x; }
    float y() { return m_y; }

    Vec2 operator+(const Vec2& rhs)
    {
        return Vec2(m_x + rhs.m_x, m_y + rhs.m_y);
    }

    Vec2 operator-(const Vec2& rhs)
    {
        return Vec2(m_x - rhs.m_x, m_y - rhs.m_y);
    }

    Vec2 operator*(const float scalar)
    {
        return Vec2(m_x * scalar, m_y * scalar);
    }

    Vec2 operator/(const float scalar)
    {
        return Vec2(m_x / scalar, m_y / scalar);
    }

    Vec2& operator+=(const Vec2& rhs)
    {
        m_x += rhs.m_x;
        m_y += rhs.m_y;
        return *this;
    }

    Vec2& operator-=(const Vec2& rhs)
    {
        m_x -= rhs.m_x;
        m_y -= rhs.m_y;
        return *this;
    }

    Vec2& operator*=(const float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        return *this;
    }

    Vec2& operator/=(const float scalar)
    {
        m_x /= scalar;
        m_y /= scalar;
        return *this;
    }

    float dot(const Vec2& b) const { return m_x * b.m_x + m_y * b.m_y; }

    void print() const { std::printf("[%.4f %.4f]\n", m_x, m_y); }

private:
    float m_x;
    float m_y;
};