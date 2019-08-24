#pragma once
#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "ray.h"
#include "util.h"

Vec3 random_in_unit_disk() {
    Vec3 point;

    do {
        point = 2.f * Vec3(randf(), randf(), 0.f) - Vec3(1.f, 1.f, 0.f);
    } while(dot(point, point) >= 1.f);
    return point;
}

struct Camera {
    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
        lens_radius = aperture / 2.f;
        float theta = vfov * M_PI / 180.f;
        float halfHeight = std::tan(theta / 2.f);
        float halfWidth = aspect * halfHeight;
        origin = lookfrom; 
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        lowerLeft = origin - halfWidth * focus_dist * u - halfHeight * focus_dist * v - focus_dist * w;
        horizontal = 2.0f * halfWidth * focus_dist * u;
        vertical = 2.0f * halfHeight * focus_dist * v;   
    }

    Ray get_ray(float s, float t) {
        Vec3 rd = lens_radius * random_in_unit_disk();
        Vec3 offset = u * rd.x + v * rd.y;
        return Ray(origin + offset, lowerLeft + s * horizontal + t * vertical - origin - offset);
    }

    Vec3 origin;
    Vec3 w, u , v;
    Vec3 lowerLeft;
    Vec3 horizontal;
    Vec3 vertical;
    
    float lens_radius; 
};

#endif // RAYTRACING_CAMERA_H