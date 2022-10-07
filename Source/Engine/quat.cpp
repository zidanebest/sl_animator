#include "quat.h"

#include <corecrt_math.h>

namespace sl{

    quat AngleAxis(float angle, const vec3& axis){
        float sinTheata = sinf(angle / 2);
        float cosTheata = cosf(angle / 2);
        vec3  norm      = Normalized(axis);
        return{
            cosTheata,
            norm.x * sinTheata,
            norm.y * sinTheata,
            norm.z * sinTheata
        };
    }

    quat FromTo(const vec3& from, const vec3& to){
        
    }
}
