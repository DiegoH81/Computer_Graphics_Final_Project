#ifndef SURFACE_H
#define SURFACE_H

#include "vector.h"

class SurfaceHit {
public:
    Point3  position;
    Vector3 normal;
};

class SurfaceFunction {
public:
    virtual ~SurfaceFunction() = default;
    
    virtual SurfaceHit project(float x, float z) const = 0;
    SurfaceHit project(const Point3& p) const { return project(p.x, p.z); }
};

class PlaneSurface : public SurfaceFunction {
    float height;
public:
    PlaneSurface(float h = 0.0f) : height(h) {}
    SurfaceHit project(float x, float z) const override {
        return { Point3(x, height, z), Vector3(0, 1, 0) };
    }
};

class SphereSurface : public SurfaceFunction {
    Point3 center;
    float  radius;
public:
    SphereSurface(Point3 c, float r) : center(c), radius(r) {}
    SurfaceHit project(float x, float z) const override {
        Vector3 dir = normalize(Vector3(x - center.x, radius, z - center.z));
        Point3  pos = Point3(center.x + dir.x * radius, center.y + dir.y * radius, center.z + dir.z * radius);
        return { pos, dir };
    }
};

class WaveSurface : public SurfaceFunction {
    float amplitude, freq_x, freq_z;
public:
    WaveSurface(float a = 0.2f, float fx = 2.0f, float fz = 2.0f): amplitude(a), freq_x(fx), freq_z(fz) {}

    SurfaceHit project(float x, float z) const override {
        float y  = amplitude * std::sin(freq_x * x) * std::cos(freq_z * z);

        float dx = -amplitude * freq_x * std::cos(freq_x * x) * std::cos(freq_z * z);
        float dz =  amplitude * freq_z * std::sin(freq_x * x) * std::sin(freq_z * z);
        Vector3 normal = normalize(Vector3(-dx, 1.0f, -dz));

        return { Point3(x, y, z), normal };
    }
};

class MountainSurface : public SurfaceFunction {
    float height;
    float steepness;

public:
    MountainSurface(float h = 2.0f, float k = 0.2f)
        : height(h), steepness(k) {}

    SurfaceHit project(float x, float z) const override
    {
        float r2 = x * x + z * z;

        float y = height * std::exp(-steepness * r2);

        float dx = -2.0f * steepness * x * y;
        float dz = -2.0f * steepness * z * y;

        Vector3 normal = normalize(Vector3(-dx, 1.0f, -dz));

        return { Point3(x, y, z), normal };
    }
};

#endif