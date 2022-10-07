#pragma once
#include "mat.h"
#include "vec.h"

namespace sl{
    struct quat{
        union{
            struct{
                float w;

                float x;

                float y;

                float z;
            };

            struct{
                float scalar;

                vec3 vector;
            };
        };

        inline quat(): w(1), x(0), y(0), z(0){}

        inline quat(float _w, float _x, float _y, float _z): w(_w), x(_x), y(_y), z(_z){}
    };

    quat AngleAxis(float angle, const vec3& axis);

    quat FromTo(const vec3& from, const vec3& to);

    vec3 getAxis(const quat& quat);

    float getAngle(const quat& quat);

    quat operator+(const quat& a, const quat& b);

    quat operator-(const quat& a, const quat& b);

    quat operator*(const quat& a, float b);

    quat operator-(const quat& q);

    bool operator==(const quat& left, const quat& right);

    bool operator!=(const quat& a, const quat& b);

    bool sameOrientation(const quat& left, const quat& right);

    float dot(const quat& a, const quat& b);

    float lenSq(const quat& q);

    float len(const quat& q);

    void normalize(quat& q);

    quat normalized(const quat& q);

    quat conjugate(const quat& q);

    quat inverse(const quat& q);

    quat operator*(const quat& Q1, const quat& Q2);

    quat operator*(const quat& Q1, const quat& Q2);

    vec3 operator*(const quat& q, const vec3& v);

    quat mix(const quat& from, const quat& to, float t);

    quat nlerp(const quat& from, const quat& to, float t);

    quat operator^(const quat& q, float f);

    quat slerp(const quat& start, const quat& end, float t);

    quat lookRotation(const vec3& direcion, const vec3& up);

    mat4f quatToMat4(const quat& q);

    quat mat4ToQuat(const mat4f& m);
}
