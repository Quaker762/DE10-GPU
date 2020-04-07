/**
 *
 */
#pragma once

#include "assert.h"

#include <cstdio>
#include <cstring>

class Mat4 final
{
public:
    Mat4() { memset(m_data, 0, sizeof(float) * 16); }

    Mat4(float val) { memset(m_data, val, sizeof(float) * 16); }

    Mat4(const float data[4][4]) { memcpy(m_data, data, sizeof(float) * 16); }

    Mat4 operator+(const Mat4& rhs)
    {
        Mat4 ret;

        ret.m_data[0][0] = m_data[0][0] + rhs.m_data[0][0];
        ret.m_data[0][1] = m_data[0][1] + rhs.m_data[0][1];
        ret.m_data[0][2] = m_data[0][2] + rhs.m_data[0][2];
        ret.m_data[0][3] = m_data[0][3] + rhs.m_data[0][3];

        ret.m_data[1][0] = m_data[1][0] + rhs.m_data[1][0];
        ret.m_data[1][1] = m_data[1][1] + rhs.m_data[1][1];
        ret.m_data[1][2] = m_data[1][2] + rhs.m_data[1][2];
        ret.m_data[1][3] = m_data[1][3] + rhs.m_data[1][3];

        ret.m_data[2][0] = m_data[2][0] + rhs.m_data[2][0];
        ret.m_data[2][1] = m_data[2][1] + rhs.m_data[2][1];
        ret.m_data[2][2] = m_data[2][2] + rhs.m_data[2][2];
        ret.m_data[2][3] = m_data[2][3] + rhs.m_data[2][3];

        ret.m_data[3][0] = m_data[3][0] + rhs.m_data[3][0];
        ret.m_data[3][1] = m_data[3][1] + rhs.m_data[3][1];
        ret.m_data[3][2] = m_data[3][2] + rhs.m_data[3][2];
        ret.m_data[3][3] = m_data[3][3] + rhs.m_data[3][3];

        return ret;
    }

    Mat4& operator+=(const Mat4& rhs)
    {
        m_data[0][0] += rhs.m_data[0][0];
        m_data[0][1] += rhs.m_data[0][1];
        m_data[0][2] += rhs.m_data[0][2];
        m_data[0][3] += rhs.m_data[0][3];

        m_data[1][0] += rhs.m_data[1][0];
        m_data[1][1] += rhs.m_data[1][1];
        m_data[1][2] += rhs.m_data[1][2];
        m_data[1][3] += rhs.m_data[1][3];

        m_data[2][0] += rhs.m_data[2][0];
        m_data[2][1] += rhs.m_data[2][1];
        m_data[2][2] += rhs.m_data[2][2];
        m_data[2][3] += rhs.m_data[2][3];

        m_data[3][0] += rhs.m_data[3][0];
        m_data[3][1] += rhs.m_data[3][1];
        m_data[3][2] += rhs.m_data[3][2];
        m_data[3][3] += rhs.m_data[3][3];

        return *this;
    }

    Mat4 operator-(const Mat4& rhs)
    {
        Mat4 ret;

        ret.m_data[0][0] = m_data[0][0] - rhs.m_data[0][0];
        ret.m_data[0][1] = m_data[0][1] - rhs.m_data[0][1];
        ret.m_data[0][2] = m_data[0][2] - rhs.m_data[0][2];
        ret.m_data[0][3] = m_data[0][3] - rhs.m_data[0][3];

        ret.m_data[1][0] = m_data[1][0] - rhs.m_data[1][0];
        ret.m_data[1][1] = m_data[1][1] - rhs.m_data[1][1];
        ret.m_data[1][2] = m_data[1][2] - rhs.m_data[1][2];
        ret.m_data[1][3] = m_data[1][3] - rhs.m_data[1][3];

        ret.m_data[2][0] = m_data[2][0] - rhs.m_data[2][0];
        ret.m_data[2][1] = m_data[2][1] - rhs.m_data[2][1];
        ret.m_data[2][2] = m_data[2][2] - rhs.m_data[2][2];
        ret.m_data[2][3] = m_data[2][3] - rhs.m_data[2][3];

        ret.m_data[3][0] = m_data[3][0] - rhs.m_data[3][0];
        ret.m_data[3][1] = m_data[3][1] - rhs.m_data[3][1];
        ret.m_data[3][2] = m_data[3][2] - rhs.m_data[3][2];
        ret.m_data[3][3] = m_data[3][3] - rhs.m_data[3][3];

        return ret;
    }

    Mat4& operator-=(const Mat4& rhs)
    {
        m_data[0][0] -= rhs.m_data[0][0];
        m_data[0][1] -= rhs.m_data[0][1];
        m_data[0][2] -= rhs.m_data[0][2];
        m_data[0][3] -= rhs.m_data[0][3];

        m_data[1][0] -= rhs.m_data[1][0];
        m_data[1][1] -= rhs.m_data[1][1];
        m_data[1][2] -= rhs.m_data[1][2];
        m_data[1][3] -= rhs.m_data[1][3];

        m_data[2][0] -= rhs.m_data[2][0];
        m_data[2][1] -= rhs.m_data[2][1];
        m_data[2][2] -= rhs.m_data[2][2];
        m_data[2][2] -= rhs.m_data[2][2];

        m_data[3][0] -= rhs.m_data[3][0];
        m_data[3][1] -= rhs.m_data[3][1];
        m_data[3][2] -= rhs.m_data[3][2];
        m_data[3][2] -= rhs.m_data[3][2];

        return *this;
    }

    Mat4 operator*(const Mat4& rhs)
    {
        Mat4 ret;

        ret.m_data[0][0] = (m_data[0][0] * rhs.m_data[0][0]) +
                           (m_data[0][1] * rhs.m_data[1][0]) +
                           (m_data[0][2] * rhs.m_data[2][0]) +
                           (m_data[0][3] * rhs.m_data[3][0]);
        ret.m_data[0][1] = (m_data[0][0] * rhs.m_data[0][1]) +
                           (m_data[0][1] * rhs.m_data[1][1]) +
                           (m_data[0][2] * rhs.m_data[2][1]) +
                           (m_data[0][3] * rhs.m_data[3][1]);
        ret.m_data[0][2] = (m_data[0][0] * rhs.m_data[0][2]) +
                           (m_data[0][1] * rhs.m_data[1][2]) +
                           (m_data[0][2] * rhs.m_data[2][2]) +
                           (m_data[0][3] * rhs.m_data[3][2]);
        ret.m_data[0][3] = (m_data[0][0] * rhs.m_data[0][3]) +
                           (m_data[0][1] * rhs.m_data[1][3]) +
                           (m_data[0][2] * rhs.m_data[2][3]) +
                           (m_data[0][3] * rhs.m_data[3][3]);

        ret.m_data[1][0] = (m_data[1][0] * rhs.m_data[0][0]) +
                           (m_data[1][1] * rhs.m_data[1][0]) +
                           (m_data[1][2] * rhs.m_data[2][0]) +
                           (m_data[1][3] * rhs.m_data[3][0]);
        ret.m_data[1][1] = (m_data[1][0] * rhs.m_data[0][1]) +
                           (m_data[1][1] * rhs.m_data[1][1]) +
                           (m_data[1][2] * rhs.m_data[2][1]) +
                           (m_data[1][3] * rhs.m_data[3][1]);
        ret.m_data[1][2] = (m_data[1][0] * rhs.m_data[0][2]) +
                           (m_data[1][1] * rhs.m_data[1][2]) +
                           (m_data[1][2] * rhs.m_data[2][2]) +
                           (m_data[1][3] * rhs.m_data[3][2]);
        ret.m_data[1][3] = (m_data[1][0] * rhs.m_data[0][3]) +
                           (m_data[1][1] * rhs.m_data[1][3]) +
                           (m_data[1][2] * rhs.m_data[2][3]) +
                           (m_data[1][3] * rhs.m_data[3][3]);

        ret.m_data[2][0] = (m_data[2][0] * rhs.m_data[0][0]) +
                           (m_data[2][1] * rhs.m_data[1][0]) +
                           (m_data[2][2] * rhs.m_data[2][0]) +
                           (m_data[2][3] * rhs.m_data[3][0]);
        ret.m_data[2][1] = (m_data[2][0] * rhs.m_data[0][1]) +
                           (m_data[2][1] * rhs.m_data[1][1]) +
                           (m_data[2][2] * rhs.m_data[2][1]) +
                           (m_data[2][3] * rhs.m_data[3][1]);
        ret.m_data[2][2] = (m_data[2][0] * rhs.m_data[0][2]) +
                           (m_data[2][1] * rhs.m_data[1][2]) +
                           (m_data[2][2] * rhs.m_data[2][2]) +
                           (m_data[2][3] * rhs.m_data[3][2]);
        ret.m_data[2][3] = (m_data[2][0] * rhs.m_data[0][3]) +
                           (m_data[2][1] * rhs.m_data[1][3]) +
                           (m_data[2][2] * rhs.m_data[2][3]) +
                           (m_data[2][3] * rhs.m_data[3][3]);

        ret.m_data[3][0] = (m_data[3][0] * rhs.m_data[0][0]) +
                           (m_data[3][1] * rhs.m_data[1][0]) +
                           (m_data[3][2] * rhs.m_data[2][0]) +
                           (m_data[3][3] * rhs.m_data[3][0]);
        ret.m_data[3][1] = (m_data[3][0] * rhs.m_data[0][1]) +
                           (m_data[3][1] * rhs.m_data[1][1]) +
                           (m_data[3][2] * rhs.m_data[2][1]) +
                           (m_data[3][3] * rhs.m_data[3][1]);
        ret.m_data[3][2] = (m_data[3][0] * rhs.m_data[0][2]) +
                           (m_data[3][1] * rhs.m_data[1][2]) +
                           (m_data[3][2] * rhs.m_data[2][2]) +
                           (m_data[3][3] * rhs.m_data[3][2]);
        ret.m_data[3][3] = (m_data[3][0] * rhs.m_data[0][3]) +
                           (m_data[3][1] * rhs.m_data[1][3]) +
                           (m_data[3][2] * rhs.m_data[2][3]) +
                           (m_data[3][3] * rhs.m_data[3][3]);

        return ret;
    }

    Mat4& operator*=(float val)
    {
        m_data[0][0] *= val;
        m_data[0][1] *= val;
        m_data[0][2] *= val;
        m_data[0][3] *= val;

        m_data[1][0] *= val;
        m_data[1][1] *= val;
        m_data[1][2] *= val;
        m_data[1][3] *= val;

        m_data[2][0] *= val;
        m_data[2][1] *= val;
        m_data[2][2] *= val;
        m_data[2][3] *= val;

        m_data[3][0] *= val;
        m_data[3][1] *= val;
        m_data[3][2] *= val;
        m_data[3][3] *= val;

        return *this;
    }

    float operator()(int row, int col) const
    {
        ASSERT(row >= 0 && col >= 0);
        ASSERT(row < 4 && col < 4);
        return m_data[row][col];
    }

    void operator()(int row, int col, float val)
    {
        ASSERT(row >= 0 && col >= 0);
        ASSERT(row < 4 && col < 4);
        m_data[row][col] = val;
    }

    void print() const
    {
        for(int row = 0; row < 4; row++)
        {
            std::printf("[ ");
            for(int col = 0; col < 4; col++)
            {
                std::printf("%.4f ", m_data[row][col]);
            }

            std::printf("]\n");
        }
    }

private:
    float m_data[4][4]; // row x column
};