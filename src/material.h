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

bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) {
    Vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);

    if (discriminant > 0.0f) {
        refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
        return true;
    }
    return false;
}

float schlick(float cosine, float ref_idx) {
    float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * std::pow(1.0f - cosine, 5.0f);
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
    Metal(const Vec3& _albedo, float _fuzz = 0.0f) : albedo(_albedo), fuzz(_fuzz) {}
    virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vec3& attenuation, Ray& scattered) const {
        Vec3 reflected = reflect(unit_vector(rayIn.direction), record.normal);
        scattered = Ray(record.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction, record.normal) > 0);
    }

    Vec3 albedo;
    float fuzz;
};

struct Dielectric : public Material {
    Dielectric(float ri) : ref_idx(ri) {}

    virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vec3& attenuation, Ray& scattered) const {
        Vec3 outward_normal;
        Vec3 reflected = reflect(rayIn.direction, record.normal);
        float ni_over_nt;
        attenuation = Vec3(1.0f, 1.0f, 1.0f);
        Vec3 refracted;

        float reflect_prob;
        float cosine;

        if (dot(rayIn.direction, record.normal) > 0.0f) {
            outward_normal = -record.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(rayIn.direction, record.normal) / rayIn.direction.length();
        }
        else {
            outward_normal = record.normal;
            ni_over_nt = 1.0f / ref_idx;
            cosine = -dot(rayIn.direction, record.normal) / rayIn.direction.length();
        }

        if (refract(rayIn.direction, outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        }
        else {
            scattered = Ray(record.p, reflected);
            reflect_prob = 1.0f;
        }

        if(distribution(rng) < reflect_prob) {
            scattered = Ray(record.p, reflected);
        }
        else {
            scattered = Ray(record.p, refracted);
        }

        return true;
    }
    float ref_idx;
};

#endif //RAYTRACING_MATERIAL_H