#pragma once
#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "hitable.h"

struct Sphere : public Hitable {
    Sphere() = default;
    Sphere(Vec3 _center, float _radius, Material *material) : center(_center), radius(_radius), mat_ptr(material) {}
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const;
    
    Vec3 center;
    float radius;
    Material *mat_ptr;
};

bool Sphere::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const {
    Vec3 oc = ray.origin - center;
    float a = dot(ray.direction, ray.direction);
    float b = dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0) {
        float temp = (-b - std::sqrt(discriminant)) / a;
        if(temp < tMax && temp > tMin) {
            record.t = temp;
            record.p = ray.point_at_parameter(temp);
            record.normal = (record.p - center) / radius;
            record.mat_ptr = mat_ptr;
            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;
            record.mat_ptr = mat_ptr;
            return true;
        } 
    }
    return false;
}

#endif // RAYTRACING_SPHERE_H