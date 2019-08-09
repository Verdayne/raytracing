#pragma once
#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include <random>
#include "vec3.h"


std::random_device device;
std::mt19937 rng(device());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

struct Ray {
    Vec3 origin, direction;
    float time;

    Ray() = default;
    Ray(const Vec3& o, const Vec3& d, float t = 0.0f) : 
        origin(o), direction(d), time(t) {}

    Vec3 point_at_parameter(float t) const { return origin + t * direction; }
};

float hit_sphere(const Vec3& center, float radius, const Ray& ray) {
    Vec3 oc = ray.origin - center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0f * dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return -1.0f;

    return (-b - std::sqrt(discriminant)) / (2.0f * a);
}
#endif //RAYTRACING_RAY_H