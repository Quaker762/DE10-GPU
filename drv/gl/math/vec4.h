/**
 *
 */
#pragma once

#include "assertions.h"
#include "math/mat4.h"

#include <cmath>
#include <cstdio>

#ifdef USE_NEON
    #include <arm_neon.h>
    #include <array>
#endif

#ifdef USE_NEON
union data
{
    struct
    {
        float32_t x, y, z, w;
    };

    struct
    {
        float32_t r, g, b, a;
    }

    float32_t data[4];
};

class Vec4
{
public:
    Vec4() {}
    Vec4(const std::array<float32_t, 4>& data) : m_vec(vld1q_f32(data.data())) {}
    Vec4(const float32x4_t vec) : m_vec(vec) {}

    // float magnitude() const { return sqrt((m_x * m_x) + (m_y * m_y)); }

    // float angle() { return atan(m_y / m_x); }

    float32x4_t data() const { return m_vec; }

    float32_t x() const
    {
        vst1q_f32(data, m_vec);

        return data.x;
    }

    float32_t y() const
    {
        vst1q_f32(data, m_vec);

        return data.y;
    }

    float32_t z() const
    {
        vst1q_f32(data, m_vec);

        return data.z;
    }

    float32_t w() const
    {
        vst1q_f32(data, m_vec);

        return m_data.w;
    }

    ////////////////////////////////////
    float32_t r() const
    {
        vst1q_f32(data, m_vec);

        return data.r;
    }

    float32_t g() const
    {
        vst1q_f32(data, m_vec);

        return data.g;
    }

    float32_t b() const
    {
        vst1q_f32(data, m_vec);

        return data.b;
    }

    float32_t a() const
    {
        vst1q_f32(data, m_vec);

        return m_data.a;
    }
    ////////////////////////////////////

    Vec4 operator+(const Vec4& rhs)
    {
        float32x4_t ret = vaddq_f32(m_vec, rhs.m_vec);
        return Vec4(ret);
    }

    Vec4 operator-(const Vec4& rhs)
    {
        float32x4_t ret = vsubq_f32(m_vec, rhs.m_vec);
        return Vec4(ret);
    }

    Vec4 operator*(const float32_t scalar)
    {
        float32x4_t ret = vmulq_n_f32(m_vec, scalar);
        return Vec4(ret);
    }

    Vec4& operator+=(const Vec4& rhs)
    {
        m_vec = vaddq_f32(m_vec, rhs.m_vec);
        return *this;
    }

    Vec4& operator-=(const Vec4& rhs)
    {
        m_vec = vsubq_f32(m_vec, rhs.m_vec);
        return *this;
    }

    Vec4& operator*=(const float32_t scalar)
    {
        m_vec = vmulq_n_f32(m_vec, scalar);
        return *this;
    }

    float dot(const Vec4& b) const { return 0; }

    float cross(const Vec4& b) const {}

    void print() const
    {
        float32_t data[4];
        vst1q_f32(data, m_vec);
        std::printf("[%.4f %.4f %.4f %.4f]\n", data[0], data[1], data[2], data[3]);
    }

private:
    float32x4_t m_vec = { 0 };
    data m_data;
};
#else
class Vec4
{
public:
    Vec4() {}
    Vec4(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}

    // float magnitude() const { return sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z) + (m_w * m_w)); }

    // float angle() { return atan(m_y / m_x); }

    float x() { return m_x; }
    float y() { return m_y; }
    float z() { return m_z; }
    float w() { return m_w; }

    Vec4 operator+(const Vec4& rhs) { return Vec4(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z, m_w + rhs.m_w); }

    Vec4 operator-(const Vec4& rhs) { return Vec4(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z, m_w - rhs.m_w); }

    Vec4 operator*(const float scalar) { return Vec4(m_x * scalar, m_y * scalar, m_z * scalar, m_w * scalar); }

    Vec4 operator/(const float scalar) { return Vec4(m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar); }

    Vec4 operator*(const Mat4& rhs)
    {
        Vec4 ret;

        ret.m_x = m_x * rhs(0, 0) + m_y * rhs(1, 0) + m_z * rhs(2, 0) + m_w * rhs(3, 0);
        ret.m_y = m_x * rhs(0, 1) + m_y * rhs(1, 1) + m_z * rhs(2, 1) + m_w * rhs(3, 1);
        ret.m_z = m_x * rhs(0, 2) + m_y * rhs(1, 2) + m_z * rhs(2, 2) + m_w * rhs(3, 2);
        ret.m_w = m_x * rhs(0, 3) + m_y * rhs(1, 3) + m_z * rhs(2, 3) + m_w * rhs(3, 3);

        return ret;
    }

    Vec4& operator+=(const Vec4& rhs)
    {
        m_x += rhs.m_x;
        m_y += rhs.m_y;
        m_z += rhs.m_z;
        m_w += rhs.m_w;
        return *this;
    }

    Vec4& operator-=(const Vec4& rhs)
    {
        m_x -= rhs.m_x;
        m_y -= rhs.m_y;
        m_z -= rhs.m_z;
        m_w -= rhs.m_w;
        return *this;
    }

    Vec4& operator*=(const float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
        m_w *= scalar;
        return *this;
    }

    Vec4& operator/=(const float scalar)
    {
        ASSERT(scalar > 0.0f || scalar < 0.0f);
        m_x /= scalar;
        m_y /= scalar;
        m_z /= scalar;
        m_w /= scalar;
        return *this;
    }

    float dot(const Vec4& b) const { return m_x * b.m_x + m_y * b.m_y + m_z * b.m_z + m_w * b.m_w; }

    void print() const { std::printf("[%.4f %.4f %.4f %.4f]\n", m_x, m_y, m_z, m_w); }

private:
    float m_x = { 0 };
    float m_y = { 0 };
    float m_z = { 0 };
    float m_w = { 0 };
};
#endif
