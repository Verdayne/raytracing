#pragma once

#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <math.h>
#include <stdlib.h>
#include <iostream>

struct Vec3 {
    union 
    {
        float e[3];
        struct {float r, g, b;};
        struct {float x, y, z;};
    };

    Vec3() = default;
    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z){};

    const Vec3& operator+() const;
    Vec3 operator-() const;
    float operator[](int i) const;
    float& operator[](int i);

    Vec3& operator+=(const Vec3& v);
    Vec3& operator-=(const Vec3& v);
    Vec3& operator*=(const Vec3& v);
    Vec3& operator/=(const Vec3& v);
    Vec3& operator*=(const float t);
    Vec3& operator/=(const float t);

    float length() const;
    float squared_length() const;
    void normalize();
};

const Vec3& Vec3::operator+() const { return *this; }

Vec3 Vec3::operator-() const { return Vec3(-x, -y, -z); }

float Vec3::operator[](int i) const { return e[i]; }

float& Vec3::operator[](int i) { return e[i]; }

Vec3& Vec3::operator+=(const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
};

Vec3& Vec3::operator*=(const Vec3& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
};

Vec3& Vec3::operator/=(const Vec3& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
};

Vec3& Vec3::operator*=(const float t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
};

Vec3& Vec3::operator/=(const float t) {
    float k = 1.0f / t;
    x *= k;
    y *= k;
    z *= k;
    return *this;
};

float Vec3::length() const { return std::sqrt(squared_length()); }

float Vec3::squared_length() const { return x * x + y * y + z * z; };

void Vec3::normalize() {
    float k = 1.0f / length();
    x *= k;
    y *= k;
    z *= k;
}

Vec3 operator+(const Vec3& v1, const Vec3& v2) { return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }

Vec3 operator-(const Vec3& v1, const Vec3& v2) { return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); };

Vec3 operator*(const Vec3& v1, const Vec3& v2) { return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); };

Vec3 operator/(const Vec3& v1, const Vec3& v2) { return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z); };

Vec3 operator*(const Vec3& v1, const float t)  { return Vec3(v1.x * t, v1.y * t, v1.z * t); };

Vec3 operator/(const Vec3& v1, const float t)  { return Vec3(v1.x / t, v1.y / t, v1.z / t); };

Vec3 operator*(const float t, const Vec3& v1)  { return Vec3(v1.x * t, v1.y * t, v1.z * t); };

Vec3 operator/(const float t, const Vec3& v1)  { return Vec3(v1.x / t, v1.y / t, v1.z / t); };

float dot(const Vec3& v1, const Vec3& v2) { 
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 cross(const Vec3& v1, const Vec3& v2)
{
    return Vec3(
        (v1.y * v2.z - v1.z * v2.y),
        -(v1.x * v2.z - v1.z * v2.x),
        (v1.x * v2.y - v1.y * v2.x)
    );
}

Vec3 unit_vector(Vec3 v)
{
    return v / v.length();;
}

namespace vec3 {
    static const Vec3 X = { 1.0f, 0.0f, 0.0f };
    static const Vec3 Y = { 0.0f, 1.0f, 0.0f };
    static const Vec3 Z = { 0.0f, 0.0f, 1.0f };
    static const Vec3 ONE = { 1.0f, 1.0f, 1.0f };
    static const Vec3 ZERO = { 0.0f, 0.0f, 0.0f };
}
#endif //RAYTRACING_VEC3_H