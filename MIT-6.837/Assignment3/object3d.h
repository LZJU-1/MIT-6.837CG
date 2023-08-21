#ifndef ASSIGNMENT1_OBJECT3D_H
#define ASSIGNMENT1_OBJECT3D_H

#include <GL/gl.h>

#include "material.h"
#include "ray.h"
#include "hit.h"

class Object3D {
public:
    explicit Object3D(Material *material) : material(material) {}

    Object3D() : Object3D(nullptr) {}

    virtual bool intersect(const Ray &r, Hit &h, float tMin) = 0;

    virtual void paint() = 0;

protected:
    Material *material;
};

#endif //ASSIGNMENT1_OBJECT3D_H
