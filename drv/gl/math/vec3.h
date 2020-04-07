/**
 *
 */
#pragma once

#include "assert.h"

#include <cmath>
#include <cstdio>

class Vec3
{
public:
    Vec3() {}
    Vec3(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}
    Vec3(const float data[3]) : m_x(data[0]), m_y(data[1]), m_z(data[2]) {}

    float magnitude() const
    {
        return sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
    }

    float angle()
    {
        ASSERT(m_x);
        return atan(m_y / m_x);
    }

    float        x() const { return m_x; }
    float        y() const { return m_y; }
    float        z() const { return m_z; }
    const float* position()
    {
        m_array[0] = m_x;
        m_array[1] = m_y;
        m_array[2] = m_z;

        return m_array;
    }

    Vec3 operator+(const Vec3& rhs)
    {
        return Vec3(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z);
    }

    Vec3 operator-(const Vec3& rhs)
    {
        return Vec3(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z);
    }

    Vec3 operator*(const float scalar)
    {
        return Vec3(m_x * scalar, m_y * scalar, m_z * scalar);
    }

    Vec3 operator/(const float scalar)
    {
        ASSERT(scalar);
        return Vec3(m_x / scalar, m_y / scalar, m_z / scalar);
    }

    Vec3& operator+=(const Vec3& rhs)
    {
        m_x += rhs.m_x;
        m_y += rhs.m_y;
        m_z += rhs.m_z;
        return *this;
    }

    Vec3& operator-=(const Vec3& rhs)
    {
        m_x -= rhs.m_x;
        m_y -= rhs.m_y;
        m_z -= rhs.m_z;
        return *this;
    }

    Vec3& operator*=(const float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
        return *this;
    }

    Vec3& operator/=(const float scalar)
    {
        ASSERT(scalar);

        m_x /= scalar;
        m_y /= scalar;
        m_z /= scalar;
        return *this;
    }

    float dot(const Vec3& b) const
    {
        return m_x * b.m_x + m_y * b.m_y + m_z * b.m_z;
    }

    Vec3 cross(const Vec3& b) const
    {
        return Vec3((m_y * b.m_z) - (m_z * b.m_y),
                    (m_z * b.m_x) - (m_x * b.m_z),
                    (m_x * b.m_y) - (m_y * b.m_x));
    }

    static Vec3 cross(const Vec3& a, const Vec3& b)
    {
        return Vec3((a.m_y * b.m_z) - (a.m_z * b.m_y),
                    (a.m_z * b.m_x) - (a.m_x * b.m_z),
                    (a.m_x * b.m_y) - (a.m_y * b.m_x));
    }

    Vec3& normalize()
    {
        float mag = magnitude();

        m_x /= mag;
        m_y /= mag;
        m_z /= mag;
        return *this;
    }

    static Vec3& normalize(Vec3& vec)
    {
        float mag = vec.magnitude();

        vec.m_x /= mag;
        vec.m_y /= mag;
        vec.m_z /= mag;
        return vec;
    }

    void print() const { std::printf("[%.4f %.4f %.4f]\n", m_x, m_y, m_z); }

private:
    float m_x;
    float m_y;
    float m_z;
    float m_array[3];
};