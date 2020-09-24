/**
 *
 */
#pragma once

#include "assertions.h"
#include "mat4.h"

#include <cmath>
#include <cstdio>

#ifdef USE_NEON
    #include <arm_neon.h>
    #include <array>
#endif

#define UNUSED_VAR(x) (void)x

class Mat4;

#ifdef USE_NEON
union udata
{
    struct
    {
        float32_t x, y, z, w;
    };

    struct
    {
        float32_t r, g, b, a;
    };

    float32_t raw[4];
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
    void set_vec(float32x4_t data) { m_vec = data; }

    float32_t x() const { return vgetq_lane_f32(m_vec, 0); }

    float32_t y() const { return vgetq_lane_f32(m_vec, 1); }

    float32_t z() const { return vgetq_lane_f32(m_vec, 2); }

    float32_t w() const { return vgetq_lane_f32(m_vec, 3); }

    void x(float32_t x) { m_vec[0] = x; }
    void y(float32_t y) { m_vec[1] = y; }
    void z(float32_t z) { m_vec[2] = z; }
    void w(float32_t w) { m_vec[3] = w; }

    ////////////////////////////////////
    float32_t r() const { return vgetq_lane_f32(m_vec, 0); }

    float32_t g() const { return vgetq_lane_f32(m_vec, 1); }

    float32_t b() const { return vgetq_lane_f32(m_vec, 2); }

    float32_t a() const { return vgetq_lane_f32(m_vec, 3); }
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

    // I'd just like thank ARM for not including any kind of lane summation or
    // vector dot product in the ARMv7 NEON instruction set.
    float32_t dot(const Vec4& b) const
    {
        float32x4_t product = vmulq_f32(m_vec, b.m_vec);
        float32_t ret = 0.0f;

        ret += vgetq_lane_f32(product, 0);
        ret += vgetq_lane_f32(product, 1);
        ret += vgetq_lane_f32(product, 2);
        ret += vgetq_lane_f32(product, 3);

        return ret;
    }

    float32_t cross(const Vec4& b) const
    {
        UNUSED_VAR(b);
        std::printf("WARNING: Vec4::cross() is unimplemented!!!!!!!!!!\n");
        return 0.0f;
    }

    void normalize()
    {
        float32x4_t div_vec = vmovq_n_f32(length()); // Create a new vector in which all elements are the length of the vector
        div_vec = vrecpeq_f32(div_vec);              // Calculate the reciprocal
        m_vec = vmulq_f32(m_vec, div_vec);           // Multiply the vector by the reciprocal (which is a division)
    }

    float32_t length() const
    {
        float32x4_t product = vmulq_f32(m_vec, m_vec); // Multiply vector parts by themselves
        float32_t sum = 0.0f;

        sum += vgetq_lane_f32(product, 0);
        sum += vgetq_lane_f32(product, 1);
        sum += vgetq_lane_f32(product, 2);
        sum += vgetq_lane_f32(product, 3);

        return sqrt(sum); // TODO: Can this be an intrinsic???
    }

    void print() const
    {
        float32_t data[4];
        vst1q_f32(data, m_vec);
        std::printf("[%.4f %.4f %.4f %.4f]\n", data[0], data[1], data[2], data[3]);
    }

private:
    float32x4_t m_vec = { 0 };
    udata m_data;
};
#else
class Vec4
{
public:
    Vec4() {}
    Vec4(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}

    float length() const { return sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z) + (m_w * m_w)); }

    void normalize()
    {
        float len = length();
        m_x /= len;
        m_y /= len;
        m_z /= len;
        m_w /= len;
    }

    // float angle() { return atan(m_y / m_x); }

    float x() const { return m_x; }
    float y() const { return m_y; }
    float z() const { return m_z; }
    float w() const { return m_w; }

    void x(float x) { m_x = x; }
    void y(float y) { m_y = y; }
    void z(float z) { m_z = z; }
    void w(float w) { m_w = w; }

    Vec4 operator+(const Vec4& rhs) { return Vec4(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z, m_w + rhs.m_w); }
    Vec4 operator-(const Vec4& rhs) { return Vec4(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z, m_w - rhs.m_w); }
    Vec4 operator*(const float scalar) { return Vec4(m_x * scalar, m_y * scalar, m_z * scalar, m_w * scalar); }
    Vec4 operator/(const float scalar) { return Vec4(m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar); }

    /**
        Vec4 operator*(const Mat4& rhs)
        {
            Vec4 ret;

            ret.m_x = m_x * rhs(0, 0) + m_y * rhs(1, 0) + m_z * rhs(2, 0) + m_w * rhs(3, 0);
            ret.m_y = m_x * rhs(0, 1) + m_y * rhs(1, 1) + m_z * rhs(2, 1) + m_w * rhs(3, 1);
            ret.m_z = m_x * rhs(0, 2) + m_y * rhs(1, 2) + m_z * rhs(2, 2) + m_w * rhs(3, 2);
            ret.m_w = m_x * rhs(0, 3) + m_y * rhs(1, 3) + m_z * rhs(2, 3) + m_w * rhs(3, 3);

            return ret;
        }
    */

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
