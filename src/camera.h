#pragma once
#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "ray.h"

struct Camera {

    Camera() : 
        lowerLeft(Vec3(-2.0f, -1.0f, -1.0f)),
        horizontal(Vec3(4.0f, 0.0f, 0.0f)),
        vertical(Vec3(0.0f, 2.0f, 0.0f)),
        origin(vec3::ZERO) {}

    Ray get_ray(float u, float v) {
        return Ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
    }

    Vec3 lowerLeft;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 origin; 
};

#endif // RAYTRACING_CAMERA_H