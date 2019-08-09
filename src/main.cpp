#include <fstream>
#include <random>
#include <cfloat>

#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

Vec3 color(const Ray& ray, Hitable *world) {
    HitRecord record;

    if (world->hit(ray, 0.0f, MAXFLOAT, record)) {
        return 0.5f * (record.normal + vec3::ONE);
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

    const int SIZE = 2;
    Hitable *list[SIZE];
    list[0] = new Sphere(-vec3::Z, 0.5f);
    list[1] = new Sphere(Vec3(0, -100.5f, -1.0f), 100.0f);
    Hitable *world = new HitableList(list, SIZE);

    Camera camera;

    for (int j = ny -1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            Vec3 col = vec3::ZERO;
            for (int s = 0; s < ns; s++) {
                float u = float(i + dist(gen)) / float(nx);
                float v = float(j + dist(gen)) / float(ny);
                
                Ray ray = camera.get_ray(u, v);
                col += color(ray, world);
            }

            col /= float(ns);

            int r = int(255.99f * col.x);
            int g = int(255.99f * col.y);
            int b = int(255.99f * col.z);

            outfile << r << " " << g << " " << b << "\n";
        }
    }
    outfile.close();
    return 0;
}