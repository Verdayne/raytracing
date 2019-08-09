#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include "hitable.h"

struct Material {
    virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vec3& attenuation, Ray& scattered) const = 0;
};

Vec3 reflect(const Vec3& v, const Vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

Vec3 random_in_unit_sphere() {
    
    Vec3 point;
    do {
        point = 2.0f * Vec3(distribution(rng), distribution(rng), distribution(rng)) - vec3::ONE;
    } while (point.squared_length() >= 1.0f);
    return point;
}

struct Lambertian : public Material {
    Lambertian(const Vec3& _albedo) : albedo(_albedo){}
    virtual bool scatter(const Ray&, const HitRecord& record, Vec3& attenuation, Ray& scattered) const {
        Vec3 target = record.p + record.normal + random_in_unit_sphere();
        scattered = Ray(record.p, target-record.p);
        attenuation = albedo;
        return true;
    }

    Vec3 albedo;
};

struct Metal : public Material {
    Metal(const Vec3& _albedo, float _fuzz) : albedo(_albedo), fuzz(_fuzz) {}
    virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vec3& attenuation, Ray& scattered) const {
        Vec3 reflected = reflect(unit_vector(rayIn.direction), record.normal);
        scattered = Ray(record.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction, record.normal) > 0);
    }

    Vec3 albedo;
    float fuzz;
};


#endif //RAYTRACING_MATERIAL_H