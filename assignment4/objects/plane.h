#pragma once

#include "object3d.h"


class Plane : public Object3D
{
private:
          Vec3f normal;
          float d;
          constexpr const static float BIG = 1e5;
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
          virtual void paint(void) {
                    Vec3f v = Vec3f(1, 0, 0);

                    if(normal.y() == 0 && normal.z() == 0) v = Vec3f(0, 1, 0);

                    Vec3f b1, b2;
                    Vec3f::Cross3(b1, v, normal);
                    Vec3f::Cross3(b2, normal, b1);

                    Vec3f p1, p2, p3, p4;
                    p1 = BIG * b1 + BIG * b2;
                    p2 = -BIG * b1 + BIG * b2;
                    p3 = BIG * b1 - BIG * b2;
                    p4 = -BIG * b1 - BIG * b2;

                    material->glSetMaterial();
                    glBegin(GL_QUADS);
                    glNormal3f(normal.x(), normal.y(), normal.z());

                    glVertex3f(p1.x(), p1.y(), p1.z());
                    glVertex3f(p2.x(), p2.y(), p2.z());
                    glVertex3f(p3.x(), p3.y(), p3.z());
                    glVertex3f(p4.x(), p4.y(), p4.z());
                    glEnd();

          }
};
