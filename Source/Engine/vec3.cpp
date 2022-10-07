#include "vec.h"

#include <complex>

namespace sl{

    vec3 operator+(const vec3& l, const vec3& r){ return {l.x + r.x,l.y + r.y,l.z + r.z}; }

    vec3 operator-(const vec3& l, const vec3& r){ return {l.x - r.x,l.y - r.y,l.z - r.z}; }

    vec3 operator*(const vec3& v, float f){ return {v.x * f,v.y * f,v.z * f}; }

    vec3 operator*(const vec3& l, const vec3& r){ return {l.x * r.x,l.y * r.y,l.z * r.z}; }

    float Dot(const vec3& l, const vec3& r){ return l.x * r.x + l.y * r.y + l.z * r.z; }

    float LenSq(const vec3& v){ return v.x * v.x + v.y * v.y + v.z * v.z; }

    float Len(const vec3& v){
        if(LenSq(v) < VEC3_EPSILON) return 0.0f;
        return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    void Normalize(vec3& v){
        float lenSq = LenSq(v);
        if(lenSq < VEC3_EPSILON) return;
        float len = std::sqrt(lenSq);
        v.x *= len;
        v.y *= len;
        v.z *= len;
    }

    vec3 Normalized(const vec3& v){
        float lenSq = LenSq(v);
        if(lenSq < VEC3_EPSILON) return {};
        float len = std::sqrt(lenSq);
        return v * len;
    }

    float AngleRad(const vec3& l, const vec3& r){
        float lenSqL = LenSq(l);
        float lenSqR = LenSq(r);
        if(lenSqL < VEC3_EPSILON || lenSqR < VEC3_EPSILON) return 0;
        float dot       = l.x * r.x + l.y * r.y + l.z * r.z;
        float cosTheata = dot / (std::sqrt(lenSqL * lenSqR));
        return std::acos(cosTheata);
    }

#define PI 3.1415926535f
#define Rad2Deg(rad) ((rad)*57.2958f) //((rad)*(180.0f/PI))
#define Deg2Rad(deg) ((deg)*0.0174533f) //((rad)*(PI/180.0f))

    float AngleDeg(const vec3& l, const vec3& r){ return Rad2Deg(AngleRad(l,r)); }

    vec3 Project(const vec3& a, const vec3& b){
        float lenSqB = LenSq(b);
        if(lenSqB < VEC3_EPSILON) return {};
        return b * (Dot(a, b) / lenSqB);
    }

    vec3 Reject(const vec3& a, const vec3& b){
        float lenSqB = LenSq(b);
        if(lenSqB < VEC3_EPSILON) return {};
        return a - Project(a, b);
    }

    vec3 BoundReflect(const vec3& a, const vec3& b){
        float lenSqB = LenSq(b);
        if(lenSqB < VEC3_EPSILON) return {};
        vec3 proj2 = b * (Dot(a, b) / lenSqB * 2);
        return a - proj2;
    }

    vec3 MirrorReflect(const vec3& a, const vec3& b){
        float lenSqB = LenSq(b);
        if(lenSqB < VEC3_EPSILON) return {};
        vec3 proj2 = b * (Dot(a, b) / lenSqB * 2);
        return proj2 - a;
    }

    vec3 Cross(const vec3& l, const vec3& r){
        return vec3(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x);
    }

    vec3 Lerp(const vec3& s, const vec3& e, float t){
        return {
            s.x + (e.x - s.x) * t,
            s.y + (e.y - s.y) * t,
            s.z + (e.z - s.z) * t
        };
    }

    vec3 Slerp(const vec3& s, const vec3& e, float t){
        if(t < 0.01f) return Lerp(s, e, t);
        float theata    = AngleRad(s, e);
        float sinTheata = sinf(theata);
        return s * (sinf((1 - t) * theata) / sinTheata) + e * (sinf(t * theata) / sinTheata);
    }

    vec3 Nlerp(const vec3& s, const vec3& e, float t){
        return Normalized({
            s.x + (e.x - s.x) * t,
            s.y + (e.y - s.y) * t,
            s.z + (e.z - s.z) * t
        });
    }

    bool operator==(const vec3& l, const vec3& r){ return LenSq(l - r) < VEC3_EPSILON; }

    bool operator!=(const vec3& l, const vec3& r){ return !(l == r); }


}
