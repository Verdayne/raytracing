#pragma once
#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "ray.h"

struct Camera {

    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect) {
        float theta = vfov * M_PI / 180.0f;
        float halfHeight = std::tan(theta/2);
        float halfWidth = aspect * halfHeight;
        Vec3 w = unit_vector(lookfrom - lookat);
        Vec3 u = unit_vector(cross(vup, w));
        Vec3 v = cross(w, u);
        lowerLeft = Vec3(-halfWidth, -halfHeight, -1.0f);
        lowerLeft = lookfrom - halfWidth * u - halfHeight * v - w;
        horizontal = 2.0f * halfWidth * u;
        vertical = 2.0f * halfHeight * v;
        origin = lookfrom; 
    }

    Ray get_ray(float u, float v) {
        return Ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
    }

    Vec3 lowerLeft;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 origin; 
};

#endif // RAYTRACING_CAMERA_H