#pragma once
#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include "vec3.h"

struct Ray {
    Vec3 origin, direction;

    Ray() = default;
    Ray(const Vec3& o, const Vec3& d) : 
        origin(o), direction(d) {}

    Vec3 point_at_parameter(float t) const { return origin + t * direction; }
};
#endif //RAYTRACING_RAY_H