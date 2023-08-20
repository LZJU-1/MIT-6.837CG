#pragma once

#include "ray.h"
#include "hit.h"

class Object3D
{
protected:
          Material* material;
          constexpr static const double deta = 1e-8;
public:
          Object3D(Material* _material) : material(_material) {}
          Object3D(){}
          ~Object3D() {}
          virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;
};
