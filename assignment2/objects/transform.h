#pragma once

#include "object3d.h"
#include "../tools/matrix.h"

class Transform : public Object3D {
private:
          Matrix m, mInv, mTra;
          Object3D *o;
          static void TransformPosition(Vec3f &dst, const Vec3f &src, const Matrix &mat) {
                    auto src4 = Vec4f(src.x(), src.y(), src.z(), 1);
                    mat.Transform(src4);
                    dst = Vec3f(src4.x() / src4.w(), src4.y() / src4.w(), src4.z() / src4.w());
          }

          static void TransformDirection(Vec3f &dst, const Vec3f &src, const Matrix &mat){
                    auto src4 = Vec4f(src.x(), src.y(), src.z(), 0);
                    mat.Transform(src4);
                    dst = Vec3f(src4.x(), src4.y(), src4.z());
          }
public:
          Transform(Matrix &m, Object3D *o) : m(m), o(o) {
                    this->m.Inverse(mInv);
                    mInv.Transpose(mTra);
          }
          ~Transform() {}
          virtual bool intersect(const Ray &r, Hit &h, float tMin) {
                    Vec3f nRo, nRd;
                    TransformPosition(nRo, r.getOrigin(), mInv);
                    TransformDirection(nRd, r.getDirection(), mInv);
                    auto transformedRdLen = nRd.Length();
                    nRd.Normalize();
                    auto nRay = Ray(nRo, nRd);

                    if (!o->intersect(nRay, h, tMin)) return false;
                    auto t = h.getT() / transformedRdLen;

                    Vec3f n = h.getNormal();
                    TransformDirection(n, h.getNormal(), mTra);
                    n.Normalize();
                    h.set(t, h.getMaterial(), n, r);
                    return true;
          }
};
