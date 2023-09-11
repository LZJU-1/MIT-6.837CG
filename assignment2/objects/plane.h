#pragma once

#include "object3d.h"


class Plane : public Object3D
{
private:
          Vec3f normal;
          float d;
public:
          Plane(Vec3f &normal, float d, Material *m) : normal(normal), d(d), Object3D(m) {}
          ~Plane(){}
          virtual bool intersect(const Ray &r, Hit &h, float tmin) {
                    float rdDotN = r.getDirection().Dot3(normal);
                    float roDotN = r.getOrigin().Dot3(normal);

                    if(roDotN == d) {
                              h.set(0, material, normal, r);
                              return true;
                    }

                    if((roDotN - d) * rdDotN < 0) {
                              float t =   (d - roDotN) / rdDotN;
                              if(t < tmin) return false;
                              h.set(t, material, normal, r);
                              return true;                            
                    }

                    return false;
          }
};
