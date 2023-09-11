#pragma once

#include "object3d.h"
#include "../tools/matrix.h"

class Triangle : public Object3D
{
private:
          Vec3f a, b, c;
public:
          Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m) : a(a), b(b), c(c), Object3D(m) {}
          ~Triangle();
          virtual bool intersect(const Ray &r, Hit &h, float tmin) {
                    float detA = det3x3(
                              a.x() - b.x(), a.x() - c.x(), r.getDirection().x(),
                              a.y() - b.y(), a.y() - c.y(), r.getDirection().y(),
                              a.z() - b.z(), a.z() - c.z(), r.getDirection().z()
                    );
                    if (fabs(detA) == 0) {
                              return false;
                    }

                    float detA1 = det3x3(
                              a.x() - r.getOrigin().x(), a.x() - c.x(), r.getDirection().x(),
                              a.y() - r.getOrigin().y(), a.y() - c.y(), r.getDirection().y(),
                              a.z() - r.getOrigin().z(), a.z() - c.z(), r.getDirection().z()
                    );
                    float detA2 = det3x3(
                              a.x() - b.x(), a.x() - r.getOrigin().x(), r.getDirection().x(),
                              a.y() - b.y(), a.y() - r.getOrigin().y(), r.getDirection().y(),
                              a.z() - b.z(), a.z() - r.getOrigin().z(), r.getDirection().z()
                    );
                    auto detA3 = det3x3(
                              a.x() - b.x(), a.x() - c.x(), a.x() - r.getOrigin().x(),
                              a.y() - b.y(), a.y() - c.y(), a.y() - r.getOrigin().y(),
                              a.z() - b.z(), a.z() - c.z(), a.z() - r.getOrigin().z()
                    );

                    float beta = detA1 / detA;
                    float gamma = detA2 / detA;
                    float alpha = 1 - beta - gamma;
                    if (alpha < 0 || alpha > 1 ) return false;
                    if (beta < 0 || beta > 1 ) return false;
                    if (gamma < 0 || gamma > 1) return false;
                    auto t = detA3 / detA;
                    if (t < tmin) return false;
                    Vec3f normal;
                    Vec3f::Cross3(normal, b - a, c - a);
                    normal.Normalize();
                    h.set(t, material, normal, r);
                    return true;
          }
};
