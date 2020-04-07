/**
 *
 */
#pragma once

#include "assert.h"

#include <cstdio>
#include <cstring>

class Mat3 final
{
public:
    Mat3() { memset(m_data, 0, sizeof(float) * 9); }

    Mat3(float val) { memset(m_data, val, sizeof(float) * 9); }

    Mat3(const float data[3][3]) { memcpy(m_data, data, sizeof(float) * 9); }

    Mat3 operator+(const Mat3& rhs)
    {
        Mat3 ret;

        ret.m_data[0][0] = m_data[0][0] + rhs.m_data[0][0];
        ret.m_data[0][1] = m_data[0][1] + rhs.m_data[0][1];
        ret.m_data[0][2] = m_data[0][2] + rhs.m_data[0][2];

        ret.m_data[1][0] = m_data[1][0] + rhs.m_data[1][0];
        ret.m_data[1][1] = m_data[1][1] + rhs.m_data[1][1];
        ret.m_data[1][2] = m_data[1][2] + rhs.m_data[1][2];

        ret.m_data[2][0] = m_data[2][0] + rhs.m_data[2][0];
        ret.m_data[2][1] = m_data[2][1] + rhs.m_data[2][1];
        ret.m_data[2][2] = m_data[2][2] + rhs.m_data[2][2];

        return ret;
    }

    Mat3& operator+=(const Mat3& rhs)
    {
        m_data[0][0] += rhs.m_data[0][0];
        m_data[0][1] += rhs.m_data[0][1];
        m_data[0][2] += rhs.m_data[0][2];

        m_data[1][0] += rhs.m_data[1][0];
        m_data[1][1] += rhs.m_data[1][1];
        m_data[1][2] += rhs.m_data[1][2];

        m_data[2][0] += rhs.m_data[2][0];
        m_data[2][1] += rhs.m_data[2][1];
        m_data[2][2] += rhs.m_data[2][2];

        return *this;
    }

    Mat3 operator-(const Mat3& rhs)
    {
        Mat3 ret;

        ret.m_data[0][0] = m_data[0][0] - rhs.m_data[0][0];
        ret.m_data[0][1] = m_data[0][1] - rhs.m_data[0][1];
        ret.m_data[0][2] = m_data[0][2] - rhs.m_data[0][2];

        ret.m_data[1][0] = m_data[1][0] - rhs.m_data[1][0];
        ret.m_data[1][1] = m_data[1][1] - rhs.m_data[1][1];
        ret.m_data[1][2] = m_data[1][2] - rhs.m_data[1][2];

        ret.m_data[2][0] = m_data[2][0] - rhs.m_data[2][0];
        ret.m_data[2][1] = m_data[2][1] - rhs.m_data[2][1];
        ret.m_data[2][2] = m_data[2][2] - rhs.m_data[2][2];

        return ret;
    }

    Mat3& operator-=(const Mat3& rhs)
    {
        m_data[0][0] -= rhs.m_data[0][0];
        m_data[0][1] -= rhs.m_data[0][1];
        m_data[0][2] -= rhs.m_data[0][2];

        m_data[1][0] -= rhs.m_data[1][0];
        m_data[1][1] -= rhs.m_data[1][1];
        m_data[1][2] -= rhs.m_data[1][2];

        m_data[2][0] -= rhs.m_data[2][0];
        m_data[2][1] -= rhs.m_data[2][1];
        m_data[2][2] -= rhs.m_data[2][2];

        return *this;
    }

    Mat3 operator*(const Mat3& rhs)
    {
        Mat3 ret;

        ret.m_data[0][0] = (m_data[0][0] * rhs.m_data[0][0]) +
                           (m_data[0][1] * rhs.m_data[1][0]) +
                           (m_data[0][2] * rhs.m_data[2][0]);
        ret.m_data[0][1] = (m_data[0][0] * rhs.m_data[0][1]) +
                           (m_data[0][1] * rhs.m_data[1][1]) +
                           (m_data[0][2] * rhs.m_data[2][1]);
        ret.m_data[0][2] = (m_data[0][0] * rhs.m_data[0][2]) +
                           (m_data[0][1] * rhs.m_data[1][2]) +
                           (m_data[0][2] * rhs.m_data[2][2]);

        ret.m_data[1][0] = (m_data[1][0] * rhs.m_data[0][0]) +
                           (m_data[1][1] * rhs.m_data[1][0]) +
                           (m_data[1][2] * rhs.m_data[2][0]);
        ret.m_data[1][1] = (m_data[1][0] * rhs.m_data[0][1]) +
                           (m_data[1][1] * rhs.m_data[1][1]) +
                           (m_data[1][2] * rhs.m_data[2][1]);
        ret.m_data[1][2] = (m_data[1][0] * rhs.m_data[0][2]) +
                           (m_data[1][1] * rhs.m_data[1][2]) +
                           (m_data[1][2] * rhs.m_data[2][2]);

        ret.m_data[2][0] = (m_data[2][0] * rhs.m_data[0][0]) +
                           (m_data[2][1] * rhs.m_data[1][0]) +
                           (m_data[2][2] * rhs.m_data[2][0]);
        ret.m_data[2][1] = (m_data[2][0] * rhs.m_data[0][1]) +
                           (m_data[2][1] * rhs.m_data[1][1]) +
                           (m_data[2][2] * rhs.m_data[2][1]);
        ret.m_data[2][2] = (m_data[2][0] * rhs.m_data[0][2]) +
                           (m_data[2][1] * rhs.m_data[1][2]) +
                           (m_data[2][2] * rhs.m_data[2][2]);

        return ret;
    }

    Mat3& operator*=(float val)
    {
        m_data[0][0] *= val;
        m_data[0][1] *= val;
        m_data[0][2] *= val;

        m_data[1][0] *= val;
        m_data[1][1] *= val;
        m_data[1][2] *= val;

        m_data[2][0] *= val;
        m_data[2][1] *= val;
        m_data[2][2] *= val;

        return *this;
    }

    float operator()(int row, int col) const
    {
        ASSERT(row >= 0 && col >= 0);
        ASSERT(row < 3 && col < 3);
        return m_data[row][col];
    }

    void operator()(int row, int col, float val)
    {
        ASSERT(row >= 0 && col >= 0);
        ASSERT(row < 3 && col < 3);
        m_data[row][col] = val;
    }

    void print() const
    {
        for(int row = 0; row < 3; row++)
        {
            std::printf("[ ");
            for(int col = 0; col < 3; col++)
            {
                std::printf("%.4f ", m_data[row][col]);
            }

            std::printf("]\n");
        }
    }

private:
    float m_data[3][3]; // row x column
};