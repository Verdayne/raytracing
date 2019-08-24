#include <fstream>

#include "sphere.h"
#include "hitable_list.h"
#include "material.h"
#include "camera.h"

Vec3 color(const Ray& ray, Hitable *world, int depth) {
    HitRecord record;
    if (world->hit(ray, 0.001f, MAXFLOAT, record)) {
        Ray scattered;
        Vec3 attenuation;
        if (depth < 50 && record.mat_ptr->scatter(ray, record, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        }
        return vec3::ZERO;
    }

    Vec3 unitDirection = unit_vector(ray.direction);
    float t = 0.5f * (unitDirection.y + 1.0f);
    return  (1.0f - t) * vec3::ONE + t * Vec3(0.5f, 0.7f, 1.0f);     
}

Hitable *random_scene() {
    const int n = 500;
    Hitable **list = new Hitable*[n + 1];
    list[0] = new Sphere(Vec3(0.f, -1000.f, 0.f), 1000.f, new Lambertian(Vec3(0.5f, 0.5f, 0.5f)));

    int i = 1;

    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            float choose_mat = randf();
            Vec3 center(a + 0.9f * randf(), 0.2f, b + 0.9f * randf());

            if((center - Vec3(4.f, 0.2f, 0.f)).length() > 0.9f) {
                // lambertian
                if (choose_mat < 0.8f) {
                    Vec3 col(randf() * randf(), randf()* randf(), randf()* randf());
                    list[i++] = new Sphere(center, 0.2f, new Lambertian(col));
                }
                // Metal
                else if (choose_mat < 0.95f) {
                    Vec3 col(0.5f *(1.f + randf()), 0.5f *(1.f + randf()), 0.5f *(1.f + randf()));
                    list[i++] = new Sphere(center, 0.2f, new Metal(col, 0.5f * randf()));
                }
                // Dielectric
                else {
                    list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
                }
            }
        }
    }

    list[i++] = new Sphere(Vec3(0.f, 1.f, 0.f), 1.0f, new Dielectric(1.5f));
    list[i++] = new Sphere(Vec3(-4.f, 1.f, 0.f), 1.f, new Lambertian(Vec3(0.4f, 0.2f, 0.1f)));
    list[i++] = new Sphere(Vec3(4.f, 1.f, 0.f), 1.f, new Metal(Vec3(0.7f, 0.6f, 0.5f), 0.f));

    return new HitableList(list, i);
}

int main()
{
    const int nx = 500;
    const int ny = 250;
    const int ns = 100;

    std::ofstream outfile ("image.ppm");
    outfile << "P3\n" << nx << " " << ny << "\n255\n";

    Hitable *world = random_scene();

    Vec3 lookfrom(13.f, 2.f, 3.f);
    Vec3 lookat(vec3::ZERO);
    float dist_to_focus = 10.0f;
    float aperture = 0.1f;

    Camera camera(lookfrom, lookat, vec3::Y, 20.f, float(nx)/float(ny), aperture, dist_to_focus);

    for (int j = ny -1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            Vec3 col = vec3::ZERO;
            for (int s = 0; s < ns; s++) {
                float u = float(i + randf()) / float(nx);
                float v = float(j + randf()) / float(ny);
                
                Ray ray = camera.get_ray(u, v);
                col += color(ray, world, 0);
            }

            col /= float(ns);
            col = Vec3(std::sqrt(col.x), std::sqrt(col.y), std::sqrt(col.z));

            int r = int(255.99f * col.x);
            int g = int(255.99f * col.y);
            int b = int(255.99f * col.z);

            outfile << r << " " << g << " " << b << "\n";
        }
    }
    outfile.close();

// @TODO Fix memory leaks
    return 0;
}