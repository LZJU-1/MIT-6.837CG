#pragma once

#include "object3d.h"
#include <math.h>

class Sphere : public Object3D
{
private:
          Vec3f center;
          double radius;
public:
          virtual bool intersect(const Ray &r, Hit &h, float tMin){
                    auto vecOriCen = center - r.getOrigin();
                    auto disOriCen = vecOriCen.Length();
                    if (fabs(disOriCen) == 0) { // ray origin on sphere, origin is intersection
                    if (0 < tMin) return false;
                    auto n = vecOriCen;
                    n.Negate();
                    n.Normalize();
                    h.set(0, material, n, r);
                    return true;
                    }

                    auto disOriVer = vecOriCen.Dot3(r.getDirection());
                    if (disOriVer < tMin) return false; // the sphere is behind the origin

                    auto disVerSq = vecOriCen.Dot3(vecOriCen) - disOriVer * disOriVer;
                    if (disVerSq > radius * radius) return false; // the ray misses the sphere

                    auto disHitVer = sqrt(radius * radius - disVerSq);
                    float t;
                    if (disOriCen > radius  &&
                    disOriVer - disHitVer > tMin) { // ray origin outside the sphere
                    t = disOriVer - disHitVer;
                    } else { // ray origin inside the sphere
                    t = disOriVer + disHitVer;
                    }

                    if (t < tMin) return false; // intersection behind the camera
                    auto n = r.pointAtParameter(t) - center;
                    n.Normalize();
                    h.set(t, material, n, r);
                    return true;

          }

          Sphere(Vec3f _center, double _radius, Material* material) : center(_center), 
          radius(_radius), Object3D(material) {}
};
