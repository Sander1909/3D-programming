#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <QtGui/qopengl.h> // for GLfloat

#include <iostream>
#include <iomanip>
#include <cassert>
#include "vec4.h"

class Matrix4x4
{
public:
    Matrix4x4();

    Matrix4x4 identity();

    void translateX(GLfloat x = 0.f);
    void translateY(GLfloat y = 0.f);
    void translateZ(GLfloat z = 0.f);

    void rotateX(GLfloat degrees = 0.f);
    void rotateY(GLfloat degrees = 0.f);
    void rotateZ(GLfloat degrees = 0.f);

    void scale(GLfloat uniformScale = 1.f);
    void scale(GLfloat scaleX = 1.f, GLfloat scaleY = 1.f, GLfloat scaleZ = 1.f);

    GLfloat matrix[16]{};

    void transpose();

    void perspective(GLfloat verticalAngle, GLfloat aspectRatio, GLfloat nearPlane, GLfloat farPlane);

    void translate(GLfloat x = 0.f, GLfloat y = 0.f, GLfloat z = 0.f);

    GLfloat& operator[] (const int index)
    {
        assert(index <16 && index >=0);
        return matrix[index];
    }

    const GLfloat& operator[] (const int index) const
    {
        assert(index <16 && index >=0);
        return matrix[index];
    }


    //strassen's matrix multiplication
    friend Matrix4x4 operator*(const Matrix4x4 &in1, const Matrix4x4 &in2 )
    {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) //rows
        {
            for (int j = 0; j < 4; ++j) //columns
            {
                result[j + i * 4] = 0;
                for (int k = 0; k < 4; ++k) // this round temp counter
                {
                    result[j + i * 4] += in1[k + i * 4] * in2[j + k * 4];
                }
            }
        }
        return result;
    }

    //strassen's matrix multiplication
//    friend Matrix4x4* operator*(const Matrix4x4 &in1, const Matrix4x4 &in2 )
//    {
//        Matrix4x4 *result = new Matrix4x4;
//        for (int i = 0; i < 4; ++i) //rows
//        {
//            for (int j = 0; j < 4; ++j) //columns
//            {
//                result->matrix[j + i * 4] = 0;
//                for (int k = 0; k < 4; ++k) // this round temp counter
//                {
//                    result->matrix[j + i * 4] += in1[k + i * 4] * in2[j + k * 4];
//                }
//            }
//        }
//        return result;
//    }

    friend Vec4 operator*(const Matrix4x4 &in1, const Vec4 &in2 )
    {
        Vec4 result;
        for (int i = 0; i < 4; ++i) //rows
        {
            for (int j = 0; j < 4; ++j) //columns
            {
                result[i] += in1[i + j*4] * in2[j];
            }
        }
        return result;
    }

    //Operator overloading as friendfunction
    friend std::ostream &operator<<(std::ostream &output, const Matrix4x4 &mIn )
    {
        output << std::setprecision(4) <<
                  "{{" << mIn.matrix[0] << "\t, " << mIn.matrix[4] << "\t, " << mIn.matrix[8] << "\t, " << mIn.matrix[12] << "}\n" <<
                  " {" << mIn.matrix[1] << "\t, " << mIn.matrix[5] << "\t, " << mIn.matrix[9] << "\t, " << mIn.matrix[13] << "}\n" <<
                  " {" << mIn.matrix[2] << "\t, " << mIn.matrix[6] << "\t, " << mIn.matrix[10] << "\t, " << mIn.matrix[14] << "}\n" <<
                  " {" << mIn.matrix[3] << "\t, " << mIn.matrix[7] << "\t, " << mIn.matrix[11] << "\t, " << mIn.matrix[15] << "}}\n";
        return output;
    }

};
#endif // MATRIX4X4_H
