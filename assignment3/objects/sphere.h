#pragma once

#include "object3d.h"
#include <math.h>
#include "../tools/globalvals.h"

class Sphere : public Object3D
{
private:
          Vec3f center;
          double radius;
          Vec3f getPoint(float phi, float theta) {
                    return center + Vec3f(radius * cos(phi) * cos(theta),
                                        radius * cos(phi) * sin(theta), radius * sin(phi));
          }
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

          virtual void paint() {
                    float deltaPhi = M_PI / phiSteps,
                    deltaTheta = 2 * M_PI / thetaSteps;

                    material->glSetMaterial();
                    glBegin(GL_TRIANGLES);
                    // phi from -90 to 90
                    for (int iPhi = 1; iPhi <= phiSteps; iPhi++) {
                    // theta from 0 to 360
                    for (int iTheta = 1; iTheta <= thetaSteps; iTheta++) {
                              float phi = -M_PI / 2 + iPhi * deltaPhi,
                                        lastPhi = -M_PI / 2 + (iPhi - 1) * deltaPhi;
                              float theta = iTheta * deltaTheta,
                                        lastTheta = (iTheta - 1) * deltaTheta;

                              // compute appropriate coordinates & normals
                              Vec3f p1 = getPoint(lastPhi, lastTheta),
                                        p2 = getPoint(lastPhi, theta),
                                        p3 = getPoint(phi, lastTheta),
                                        p4 = getPoint(phi, theta);
                              Vec3f n1, n2, n3, n4;
                              if (!gouraud) { // (use one normal of the triangle)
                                        Vec3f::Cross3(n1, p2 - p1, p3 - p1);
                                        n1.Normalize();
                                        Vec3f::Cross3(n2, p4 - p2, p3 - p2);
                                        n2.Normalize();
                              } else { //(use normals of each vetrix)
                                        n1 = p1 - center; n1.Normalize();
                                        n2 = p2 - center; n2.Normalize();
                                        n3 = p3 - center; n3.Normalize();
                                        n4 = p4 - center; n4.Normalize();
                              }

                              // send gl vertex commands
                              if (!gouraud) {
                                        if ((p1 - p2).Length() > 0) {
                                                  glNormal3f(n1.x(), n1.y(), n1.z());
                                                  glVertex3f(p1.x(), p1.y(), p1.z());
                                                  glVertex3f(p2.x(), p2.y(), p2.z());
                                                  glVertex3f(p3.x(), p3.y(), p3.z());
                                        }
                                        if ((p3 - p4).Length() > 0) {
                                                  glNormal3f(n2.x(), n2.y(), n2.z());
                                                  glVertex3f(p2.x(), p2.y(), p2.z());
                                                  glVertex3f(p3.x(), p3.y(), p3.z());
                                                  glVertex3f(p4.x(), p4.y(), p4.z());
                                        }
                              } else {
                                        if ((p1 - p2).Length() > 0) {
                                                  glNormal3f(n1.x(), n1.y(), n1.z());
                                                  glVertex3f(p1.x(), p1.y(), p1.z());
                                                  glNormal3f(n2.x(), n2.y(), n2.z());
                                                  glVertex3f(p2.x(), p2.y(), p2.z());
                                                  glNormal3f(n3.x(), n3.y(), n3.z());
                                                  glVertex3f(p3.x(), p3.y(), p3.z());
                                        }
                                        if ((p3 - p4).Length() > 0) {
                                                  glNormal3f(n2.x(), n2.y(), n2.z());
                                                  glVertex3f(p2.x(), p2.y(), p2.z());
                                                  glNormal3f(n3.x(), n3.y(), n3.z());
                                                  glVertex3f(p3.x(), p3.y(), p3.z());
                                                  glNormal3f(n4.x(), n4.y(), n4.z());
                                                  glVertex3f(p4.x(), p4.y(), p4.z());
                                        }
                              }
                    }
                    }
                    glEnd();
          }

          Sphere(Vec3f _center, double _radius, Material* material) : center(_center), 
          radius(_radius), Object3D(material) {}
};
