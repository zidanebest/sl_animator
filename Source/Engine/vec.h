#pragma once
#define VEC3_EPSILON 0.000001f

namespace sl{
    
    template <size_t Dim, typename T> struct vec{};

    template <> struct vec<3, float>{
        union{
            struct{
                float x;

                float y;

                float z;
            };

            float v[3];
        };

        inline vec() : x(0.0f), y(0.0f), z(0.0f){ }

        inline vec(float _x, float _y, float _z) : x(_x), y(_y), z(_z){ }

        inline vec(float* fv) : x(fv[0]), y(fv[1]), z(fv[2]){ }

        inline float& operator[](size_t i){ return v[i]; }

        inline float operator[](size_t i) const{ return v[i]; }
    };

    using vec3 = vec<3, float>;

    vec3 operator+(const vec3& l, const vec3& r);

    vec3 operator-(const vec3& l, const vec3& r);

    vec3 operator*(const vec3& v, float f);

    vec3 operator*(const vec3& l, const vec3& r);

    float Dot(const vec3& l, const vec3& r);

    float LenSq(const vec3& v);

    float Len(const vec3& v);

    void Normalize(vec3& v);

    vec3 Normalized(const vec3& v);

    float AngleRad(const vec3& l, const vec3& r);

    float AngleDeg(const vec3& l, const vec3& r);

    vec3 Project(const vec3& a, const vec3& b);

    vec3 Reject(const vec3& a, const vec3& b);

    vec3 BoundReflect(const vec3& a, const vec3& b);

    vec3 MirrorReflect(const vec3& a, const vec3& b);

    vec3 Cross(const vec3& l, const vec3& r);

    vec3 Lerp(const vec3& s, const vec3& e, float t);

    vec3 Slerp(const vec3& s, const vec3& e, float t);

    vec3 Nlerp(const vec3& s, const vec3& e, float t);

    bool operator==(const vec3& l, const vec3& r);

    bool operator!=(const vec3& l, const vec3& r);


    template <typename T> struct vec<1, T>{
        union{
            struct{
                T x;
            };

            T v[1];
        };

        inline vec() : x(T(0)){ }

        inline vec(T _x) : x(_x){ }

        inline vec(T* fv) : x(fv[0]){ }

        inline T& operator[](size_t i){ return v[i]; }

        inline T operator[](size_t i) const{ return v[i]; }
    };

    template <typename T> struct vec<2, T>{
        union{
            struct{
                T x;

                T y;
            };

            T v[2];
        };

        inline vec() : x(T(0)), y(T(0)){ }

        inline vec(T _x, T _y) : x(_x), y(_y){ }

        inline vec(T* fv) : x(fv[0]), y(fv[1]){ }

        inline T& operator[](size_t i){ return v[i]; }

        inline T operator[](size_t i) const{ return v[i]; }
    };

    using vec2i = vec<2, int>;
    using vec2f = vec<2, float>;

    template <typename T> struct vec<4, T>{
        union{
            struct{
                T x;

                T y;

                T z;

                T w;
            };

            T v[4];
        };

        inline vec() : x(T(0)), y(T(0)), z(T(0)), w(T(0)){ }

        inline vec(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w){ }

        inline vec(T* fv) : x(fv[0]), y(fv[1]), z(fv[2]), w(fv[3]){ }

        inline T& operator[](size_t i){ return v[i]; }

        inline T operator[](size_t i) const{ return v[i]; }
    };

    using vec4i = vec<4, int>;
    using vec4f = vec<4, float>;
}
