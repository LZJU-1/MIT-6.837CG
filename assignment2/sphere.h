#pragma once

#include "object3d.h"
#include <math.h>

class Sphere : public Object3D
{
private:
          Vec3f center;
          double radius;
public:
          virtual bool intersect(const Ray &r, Hit &h, float tmin){
                    Vec3f rayCenToSpereCen = center - r.getOrigin();
                    double rCToSCOnDirection = rayCenToSpereCen.Dot3(r.getDirection());
                    double distanceOfRTS2 = rayCenToSpereCen.Dot3(rayCenToSpereCen);


                    if (distanceOfRTS2 >= radius * radius)
                    {
                              if(rCToSCOnDirection < 0) return false;
                              else{
                                        double boundary = distanceOfRTS2 - radius * radius;
                                        if(rCToSCOnDirection * rCToSCOnDirection < boundary) return false;

                                        double t = rCToSCOnDirection - sqrt(radius * radius - (distanceOfRTS2 - rCToSCOnDirection * rCToSCOnDirection));
                                        if(t < tmin) return false;
                                        h.set(t, material, r);
                                        return true;
                              }                             
                    }
                    else if(distanceOfRTS2 < radius * radius){
                              double t = rCToSCOnDirection + sqrt(radius * radius - (distanceOfRTS2 - rCToSCOnDirection * rCToSCOnDirection));
                              if(t < tmin) return false;
                              h.set(t, material, r);
                              return true;
                    }
                    return false;

          }

          Sphere(Vec3f _center, double _radius, Material* material) : center(_center), 
          radius(_radius), Object3D(material) {}

          Vec3f getCenter() {
                    return center;
          }

          double getRadius(){
                    return radius;
          }
};
