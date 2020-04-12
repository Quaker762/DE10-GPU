/**
 *
 */
#pragma once

#include <arm_neon.h>
#include <cstdio>
#include <cstring>

#ifdef USE_NEON
    #include <arm_neon.h>
#endif

class Mat4 final
{
public:
    Mat4() {}

    Mat4(float val) {}

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

    // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0472k/chr1360928373893.html
    // https://github.com/thenifty/neon-guide
    Mat4 operator*(const Mat4& rhs)
    {
        Mat4 ret;

#ifdef USE_NEON
        float32x4_t mat0_col0;
        float32x4_t mat0_col1;
        float32x4_t mat0_col2;
        float32x4_t mat0_col3;

        float32x4_t mat1_col0;
        float32x4_t mat1_col1;
        float32x4_t mat1_col2;
        float32x4_t mat1_col3;

        float32x4_t ret_col0;
        float32x4_t ret_col1;
        float32x4_t ret_col2;
        float32x4_t ret_col3;

        // Load LHS matrix
        mat0_col0 = vld1q_f32(m_data[0]);
        mat0_col1 = vld1q_f32(m_data[1]);
        mat0_col2 = vld1q_f32(m_data[2]);
        mat0_col3 = vld1q_f32(m_data[3]);

        // Load RHS matrix
        mat1_col0 = vld1q_f32(rhs.m_data[0]);
        mat1_col1 = vld1q_f32(rhs.m_data[1]);
        mat1_col2 = vld1q_f32(rhs.m_data[2]);
        mat1_col3 = vld1q_f32(rhs.m_data[3]);

        // Multiply lhs.col0 by rhs.col0
        ret_col0 = vmulq_n_f32(mat0_col0, mat1_col0[0]);
        ret_col0 = vmlaq_n_f32(ret_col0, mat0_col1, mat1_col0[1]);
        ret_col0 = vmlaq_n_f32(ret_col0, mat0_col2, mat1_col0[2]);
        ret_col0 = vmlaq_n_f32(ret_col0, mat0_col3, mat1_col0[3]);

        // Multiply lhs.col1 by rhs.col1
        ret_col1 = vmulq_n_f32(mat0_col0, mat0_col1[0]);
        ret_col1 = vmlaq_n_f32(ret_col1, mat0_col1, mat1_col1[1]);
        ret_col1 = vmlaq_n_f32(ret_col1, mat0_col2, mat1_col1[2]);
        ret_col1 = vmlaq_n_f32(ret_col1, mat0_col3, mat1_col1[3]);

        // Multiply lhs.col2 by rhs.col2
        ret_col2 = vmulq_n_f32(mat0_col0, mat0_col2[0]);
        ret_col2 = vmlaq_n_f32(ret_col2, mat0_col1, mat1_col2[1]);
        ret_col2 = vmlaq_n_f32(ret_col2, mat0_col2, mat1_col2[2]);
        ret_col2 = vmlaq_n_f32(ret_col2, mat0_col3, mat1_col2[3]);

        // Multiply lhs.col3 by rhs.col3
        ret_col3 = vmulq_n_f32(mat0_col0, mat0_col3[0]);
        ret_col3 = vmlaq_n_f32(ret_col3, mat0_col1, mat1_col3[1]);
        ret_col3 = vmlaq_n_f32(ret_col3, mat0_col2, mat1_col3[2]);
        ret_col3 = vmlaq_n_f32(ret_col3, mat0_col3, mat1_col3[3]);

        vst1q_f32(ret.m_data[0], ret_col0);
        vst1q_f32(ret.m_data[1], ret_col1);
        vst1q_f32(ret.m_data[2], ret_col2);
        vst1q_f32(ret.m_data[3], ret_col3);

#else
        ret.m_data[0][0] = (m_data[0][0] * rhs.m_data[0][0]) + (m_data[0][1] * rhs.m_data[1][0]) + (m_data[0][2] * rhs.m_data[2][0]) + (m_data[0][3] * rhs.m_data[3][0]);
        ret.m_data[0][1] = (m_data[0][0] * rhs.m_data[0][1]) + (m_data[0][1] * rhs.m_data[1][1]) + (m_data[0][2] * rhs.m_data[2][1]) + (m_data[0][3] * rhs.m_data[3][1]);
        ret.m_data[0][2] = (m_data[0][0] * rhs.m_data[0][2]) + (m_data[0][1] * rhs.m_data[1][2]) + (m_data[0][2] * rhs.m_data[2][2]) + (m_data[0][3] * rhs.m_data[3][2]);
        ret.m_data[0][3] = (m_data[0][0] * rhs.m_data[0][3]) + (m_data[0][1] * rhs.m_data[1][3]) + (m_data[0][2] * rhs.m_data[2][3]) + (m_data[0][3] * rhs.m_data[3][3]);

        ret.m_data[1][0] = (m_data[1][0] * rhs.m_data[0][0]) + (m_data[1][1] * rhs.m_data[1][0]) + (m_data[1][2] * rhs.m_data[2][0]) + (m_data[1][3] * rhs.m_data[3][0]);
        ret.m_data[1][1] = (m_data[1][0] * rhs.m_data[0][1]) + (m_data[1][1] * rhs.m_data[1][1]) + (m_data[1][2] * rhs.m_data[2][1]) + (m_data[1][3] * rhs.m_data[3][1]);
        ret.m_data[1][2] = (m_data[1][0] * rhs.m_data[0][2]) + (m_data[1][1] * rhs.m_data[1][2]) + (m_data[1][2] * rhs.m_data[2][2]) + (m_data[1][3] * rhs.m_data[3][2]);
        ret.m_data[1][3] = (m_data[1][0] * rhs.m_data[0][3]) + (m_data[1][1] * rhs.m_data[1][3]) + (m_data[1][2] * rhs.m_data[2][3]) + (m_data[1][3] * rhs.m_data[3][3]);

        ret.m_data[2][0] = (m_data[2][0] * rhs.m_data[0][0]) + (m_data[2][1] * rhs.m_data[1][0]) + (m_data[2][2] * rhs.m_data[2][0]) + (m_data[2][3] * rhs.m_data[3][0]);
        ret.m_data[2][1] = (m_data[2][0] * rhs.m_data[0][1]) + (m_data[2][1] * rhs.m_data[1][1]) + (m_data[2][2] * rhs.m_data[2][1]) + (m_data[2][3] * rhs.m_data[3][1]);
        ret.m_data[2][2] = (m_data[2][0] * rhs.m_data[0][2]) + (m_data[2][1] * rhs.m_data[1][2]) + (m_data[2][2] * rhs.m_data[2][2]) + (m_data[2][3] * rhs.m_data[3][2]);
        ret.m_data[2][3] = (m_data[2][0] * rhs.m_data[0][3]) + (m_data[2][1] * rhs.m_data[1][3]) + (m_data[2][2] * rhs.m_data[2][3]) + (m_data[2][3] * rhs.m_data[3][3]);

        ret.m_data[3][0] = (m_data[3][0] * rhs.m_data[0][0]) + (m_data[3][1] * rhs.m_data[1][0]) + (m_data[3][2] * rhs.m_data[2][0]) + (m_data[3][3] * rhs.m_data[3][0]);
        ret.m_data[3][1] = (m_data[3][0] * rhs.m_data[0][1]) + (m_data[3][1] * rhs.m_data[1][1]) + (m_data[3][2] * rhs.m_data[2][1]) + (m_data[3][3] * rhs.m_data[3][1]);
        ret.m_data[3][2] = (m_data[3][0] * rhs.m_data[0][2]) + (m_data[3][1] * rhs.m_data[1][2]) + (m_data[3][2] * rhs.m_data[2][2]) + (m_data[3][3] * rhs.m_data[3][2]);
        ret.m_data[3][3] = (m_data[3][0] * rhs.m_data[0][3]) + (m_data[3][1] * rhs.m_data[1][3]) + (m_data[3][2] * rhs.m_data[2][3]) + (m_data[3][3] * rhs.m_data[3][3]);
#endif
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

    float operator()(int col, int row) const { return m_data[col][row]; }

    void operator()(int col, int row, float val) { m_data[col][row] = val; }

    void print() const
    {
        for(int row = 0; row < 4; row++)
        {
            std::printf("[ ");
            for(int col = 0; col < 4; col++)
            {
                std::printf("%.4f ", m_data[col][row]);
            }

            std::printf("]\n");
        }
    }

private:
#ifdef USE_NEON
    float32_t m_data[4][4] = { { 0 } };
#else
    float m_data[4][4] = { { 0 } }; // row x column
#endif
};
