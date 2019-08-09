#pragma once
#ifndef RAYTRACING_HITABLE_H
#define RAYTRACING_HITABLE_H

#include "ray.h"

struct Material;

struct HitRecord {
    Vec3 p;
    Vec3 normal;
    float t;
    Material *mat_ptr;
};

struct Hitable {
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const = 0;
};

#endif // RAYTRACING_HITABLE_H