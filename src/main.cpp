#include <fstream>
#include <random>
#include <cfloat>

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

int main()
{
    const int nx = 500;
    const int ny = 250;
    const int ns = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    std::ofstream outfile ("image.ppm");
    outfile << "P3\n" << nx << " " << ny << "\n255\n";

    const int SIZE = 5;
   // float R = std::cos(M_PI/4);
    Hitable *list[SIZE];

    //list[0] = new Sphere(Vec3(-R, 0.0f, -1), R, new Lambertian(Vec3(0.0f, 0.0f, 1.0f)));
    //list[1] = new Sphere(Vec3(R, 0.0f, -1), R, new Lambertian(Vec3(1.0f, 0.0f, 0.0f)));
    
    list[0] = new Sphere(-vec3::Z, 0.5f, new Lambertian(Vec3(0.1f, 0.2f, 0.5f)));
    list[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(Vec3(0.8f, 0.8f, 0.0f)));
    list[2] = new Sphere(Vec3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f)));
    list[3] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, new Dielectric(1.5f));
    list[4] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f), 0.45f, new Dielectric(1.5f));
    Hitable *world = new HitableList(list, SIZE);

    Camera camera(Vec3(-2.0f, 2.0f, 1.0f), -vec3::Z, vec3::Y, 90.0f, float(nx)/float(float(ny)));

    for (int j = ny -1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            Vec3 col = vec3::ZERO;
            for (int s = 0; s < ns; s++) {
                float u = float(i + dist(gen)) / float(nx);
                float v = float(j + dist(gen)) / float(ny);
                
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
    return 0;
}