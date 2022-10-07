#pragma once
#include <assert.h>

#include "vec.h"
#define MAT_EPSILON 0.000001f

namespace sl{
    template <size_t Dim, typename T> struct mat{
        vec<Dim, T> rows[Dim];

        inline mat(){ for(size_t i = Dim; i--;) for(size_t j = Dim; j--; rows[i][j] = i == j ? 1 : 0); }

        inline mat(std::initializer_list<vec<Dim, T>>&& _rows){
            size_t i = 0;
            for(auto it = _rows.begin(); it != _rows.end(); ++it, ++i){ rows[i] = *it; }
        }

        vec<Dim, T> Col(size_t index) const{
            assert(index<Dim);
            vec<Dim, T> ret;
            for(size_t i = Dim; i--; ret[i] = rows[i][index]);
            return ret;
        }
    };

    template <size_t Dim, typename T> mat<Dim, T> operator*(const mat<Dim, T>& l, const mat<Dim, T>& r);

    template <size_t Dim, typename T> vec<Dim, T> operator*(const mat<Dim, T>& m, const vec<Dim, T>& f);

    template <size_t Dim, typename T> mat<Dim, T> operator*(const mat<Dim, T>& m, float f);

    template <size_t Dim, typename T> bool operator==(const mat<Dim, T>& l, const mat<Dim, T>& r);

    template <size_t Dim, typename T> bool operator!=(const mat<Dim, T>& l, const mat<Dim, T>& r);

    template <size_t Dim, typename T> mat<Dim, T> Transposed(const mat<Dim, T>& m);

    template <size_t Dim, typename T> mat<Dim - 1, T> Cut(const mat<Dim, T>& m, int r, int c);

    template <size_t Dim, typename T> mat<Dim, T> Minor(const mat<Dim, T>& m);

    template <size_t Dim, typename T> mat<Dim, T> Cofactor(const mat<Dim, T>& m);

    template <size_t Dim, typename T> float Determinant(const mat<Dim, T>& m);

    template <typename T> float Determinant(const mat<2, T>& m);

    template <typename T> float Determinant(const mat<1, T>& m);

    template <size_t Dim, typename T> mat<Dim, T> Adjugate(const mat<Dim, T>& m);

    template <size_t Dim, typename T> mat<Dim, T> Inverse(const mat<Dim, T>& m);

    //template<size_t Dim,typename T>
    using mat4f = mat<4, float>;

    inline mat4f Frustum(float l, float r, float b, float t, float n, float f){
        return mat4f{
            {2 * n / (r - l),0.0f,-(r + l) / (r - l),0.0f},
            {0,2 * n / (t - b),-(t + b) / (t - b),0.0f},
            {0,0,(f + n) / (f - n),-2 * n * f / (f - n)},
            {0.0,0.0,1.0,0.0}
        };
    }

    inline mat4f Persp(float fov, float aspect, float znear, float zfar){
        float ymax = znear * tanf(fov * 3.14159265359f / 180.0f / 2.0f);
        float xmax = ymax * aspect;
        return Frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
    }

    inline mat4f Ortho(float l, float r, float b, float t, float n, float f){
        return mat4f{
            {2 / (r - l),0.0f,0.0f,-(r + l) / (r - l)},
            {0,2 / (t - b),0,-(t + b) / (t - b)},
            {0,0,2 / (f - n),-(f + n) / (f - n)},
            {0.0,0.0,0.0,1.0}
        };
    }
    
    inline mat4f LookAt(const vec3& pos, const vec3& target, const vec3& up){
        vec3 f = Normalized(target - pos);
        vec3 r = Cross(up, f);
        vec3 u = Cross(f, r);
        vec3 t = vec3(
            -Dot(r, pos),
            -Dot(u, pos),
            -Dot(f, pos)
        );
        return mat4f{
            {r.x,r.y,r.z,t.x},
            {u.x,u.y,u.z,t.y},
            {f.x,f.y,f.z,t.z},
            {0.0f,0.0f,0.0f,1.0f}
        };
    }
}

#include "mat.inl"
