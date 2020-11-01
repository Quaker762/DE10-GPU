/**
 * This file is part of Rush3D.
 * Copyright (c) 2020 Jack Allan, Matthew Atkin and Jesse Buhagiar
 *
 * Rush3D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Rush3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Rush3D.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Jesse Buhagiar
 * Date: 2/4/2020
 */
#pragma once

#include "vec4.h"

#include <cstdio>
#include <cstring>

#ifdef USE_NEON
    #include <arm_neon.h>
#endif

class Vec4;

class Mat4 final
{
public:
    Mat4(bool identity = true)
    {
        if(identity)
            load_identity();
    }

    Mat4(float val) { memset(m_data, val, sizeof(float) * 16); }

    Mat4(const float data[4][4]) { memcpy(m_data, data, sizeof(float) * 16); }

    Mat4 operator+(const Mat4& rhs)
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

        ret_col0 = vaddq_f32(mat0_col0, mat1_col0);
        ret_col1 = vaddq_f32(mat0_col1, mat1_col1);
        ret_col2 = vaddq_f32(mat0_col2, mat1_col2);
        ret_col3 = vaddq_f32(mat0_col3, mat1_col3);

        vst1q_f32(ret.m_data[0], ret_col0);
        vst1q_f32(ret.m_data[1], ret_col1);
        vst1q_f32(ret.m_data[2], ret_col2);
        vst1q_f32(ret.m_data[3], ret_col3);
#else
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
#endif

        return ret;
    }

    Mat4& operator+=(const Mat4& rhs)
    {
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

        ret_col0 = vaddq_f32(mat0_col0, mat1_col0);
        ret_col1 = vaddq_f32(mat0_col1, mat1_col1);
        ret_col2 = vaddq_f32(mat0_col2, mat1_col2);
        ret_col3 = vaddq_f32(mat0_col3, mat1_col3);

        vst1q_f32(m_data[0], ret_col0);
        vst1q_f32(m_data[1], ret_col1);
        vst1q_f32(m_data[2], ret_col2);
        vst1q_f32(m_data[3], ret_col3);
#else
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
#endif

        return *this;
    }

    Mat4 operator-(const Mat4& rhs)
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

        ret_col0 = vsubq_f32(mat0_col0, mat1_col0);
        ret_col1 = vsubq_f32(mat0_col1, mat1_col1);
        ret_col2 = vsubq_f32(mat0_col2, mat1_col2);
        ret_col3 = vsubq_f32(mat0_col3, mat1_col3);

        vst1q_f32(ret.m_data[0], ret_col0);
        vst1q_f32(ret.m_data[1], ret_col1);
        vst1q_f32(ret.m_data[2], ret_col2);
        vst1q_f32(ret.m_data[3], ret_col3);
#endif

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

        ret_col0 = vsubq_f32(mat0_col0, mat1_col0);
        ret_col1 = vsubq_f32(mat0_col1, mat1_col1);
        ret_col2 = vsubq_f32(mat0_col2, mat1_col2);
        ret_col3 = vsubq_f32(mat0_col3, mat1_col3);

        vst1q_f32(m_data[0], ret_col0);
        vst1q_f32(m_data[1], ret_col1);
        vst1q_f32(m_data[2], ret_col2);
        vst1q_f32(m_data[3], ret_col3);
#else
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
#endif

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

    Vec4 operator*(const Vec4& rhs)
    {
        Vec4 ret;

#ifdef USE_NEON
        ret.x(rhs.x() * m_data[0][0] + rhs.y() * m_data[1][0] + rhs.z() * m_data[2][0] + rhs.w() * m_data[3][0]);
        ret.y(rhs.x() * m_data[0][1] + rhs.y() * m_data[1][1] + rhs.z() * m_data[2][1] + rhs.w() * m_data[3][1]);
        ret.z(rhs.x() * m_data[0][2] + rhs.y() * m_data[1][2] + rhs.z() * m_data[2][2] + rhs.w() * m_data[3][2]);
        ret.w(rhs.x() * m_data[0][3] + rhs.y() * m_data[1][3] + rhs.z() * m_data[2][3] + rhs.w() * m_data[3][3]);
#else
        ret.x(rhs.x() * m_data[0][0] + rhs.y() * m_data[1][0] + rhs.z() * m_data[2][0] + rhs.w() * m_data[3][0]);
        ret.y(rhs.x() * m_data[0][1] + rhs.y() * m_data[1][1] + rhs.z() * m_data[2][1] + rhs.w() * m_data[3][1]);
        ret.z(rhs.x() * m_data[0][2] + rhs.y() * m_data[1][2] + rhs.z() * m_data[2][2] + rhs.w() * m_data[3][2]);
        ret.w(rhs.x() * m_data[0][3] + rhs.y() * m_data[1][3] + rhs.z() * m_data[2][3] + rhs.w() * m_data[3][3]);
#endif

        return ret;
    }

    Mat4& operator*=(float val)
    {
#ifdef USE_NEON
        float32x4_t mat0_col0;
        float32x4_t mat0_col1;
        float32x4_t mat0_col2;
        float32x4_t mat0_col3;

        mat0_col0 = vld1q_f32(m_data[0]);
        mat0_col1 = vld1q_f32(m_data[1]);
        mat0_col2 = vld1q_f32(m_data[2]);
        mat0_col3 = vld1q_f32(m_data[3]);

        mat0_col0 = vmulq_n_f32(mat0_col0, val);
        mat0_col1 = vmulq_n_f32(mat0_col1, val);
        mat0_col2 = vmulq_n_f32(mat0_col2, val);
        mat0_col3 = vmulq_n_f32(mat0_col3, val);

        vst1q_f32(m_data[0], mat0_col0);
        vst1q_f32(m_data[1], mat0_col1);
        vst1q_f32(m_data[2], mat0_col2);
        vst1q_f32(m_data[3], mat0_col3);
#else
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
#endif

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

    void load_identity()
    {
#ifdef USE_NEON
        memset(&m_data, 0, 16 * sizeof(float32_t));
#else
        memset(&m_data, 0, 16 * sizeof(float));
#endif
        m_data[0][0] = 1.0f;
        m_data[1][1] = 1.0f;
        m_data[2][2] = 1.0f;
        m_data[3][3] = 1.0f;
    }

private:
#ifdef USE_NEON
    float32_t m_data[4][4] = { { 0 } };
#else
    float m_data[4][4] = { { 0 } }; // row x column
#endif
};
