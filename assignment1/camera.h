#pragma once
#include "ray.h"

class Camera
{
public:
          virtual Ray generateRay(Vec2f point) = 0;
          virtual float getTMin() const = 0;
};


class OrthographicCamera : public Camera 
{
private:
          Vec3f center, up, horizontal, direction;
          double size;
public:

          OrthographicCamera(Vec3f _center, Vec3f _direction, Vec3f _up,
           float _size){
                    this->center = _center;

                    this->up = _up;
                    this->up.Normalize();
                    this->direction = _direction;
                    this->direction.Normalize();

                    Vec3f::Cross3(this->horizontal, direction, up);
                    this->horizontal.Normalize();

                    this->size = _size;
           }
          virtual Ray generateRay(Vec2f point) {
                    //转化成虚拟世界中的射线
                    point -= Vec2f(0.5, 0.5);
                    point *= size;
                    return Ray(center + point.x() * horizontal + point.y() * up, direction);
          };
          virtual float getTMin() const {
                    return -1;
          };
};