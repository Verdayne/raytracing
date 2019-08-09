#include <fstream>
#include "sphere.h"
#include "hitable_list.h"
#include <cfloat>

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

    std::ofstream outfile ("image.ppm");
    outfile << "P3\n" << nx << " " << ny << "\n255\n";

    Vec3 lowerLeftCorner(-2.0f, -1.0f, -1.0f);
    Vec3 horizontal(4.0f, 0.0f, 0.0f);
    Vec3 vertical(0.0f, 2.0f, 0.0f);
    Vec3 origin = vec3::ZERO;

    const int SIZE = 2;
    Hitable *list[SIZE];
    list[0] = new Sphere(-vec3::Z, 0.5f);
    list[1] = new Sphere(Vec3(0, -100.5f, -1.0f), 100.0f);

    Hitable *world = new HitableList(list, SIZE);

    for (int j = ny -1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            
            Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
            Vec3 col = color(ray, world);
            
            int r = int(255.99f * col.x);
            int g = int(255.99f * col.y);
            int b = int(255.99f * col.z);

            outfile << r << " " << g << " " << b << "\n";
        }
    }
    outfile.close();
    return 0;
}