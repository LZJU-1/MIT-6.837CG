#pragma once

#include "../scene/ray.h"
#include "../scene/hit.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

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
          virtual void paint(void) = 0;
};
