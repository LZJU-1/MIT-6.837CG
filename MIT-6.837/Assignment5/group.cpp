//
// Created by kskun on 2021/10/4.
//
#include <limits>
#include "group.h"
#include "global.h"

void Group::addObject(int index, Object3D *object) {
    assert(index < objectNum);
    objects[index] = object;

    // update bounding box
    auto objBBox = object->getBoundingBox();
    if (bbox == nullptr) {
        bbox = new BoundingBox(*objBBox);
    } else if (objBBox != nullptr) {
        bbox->Extend(objBBox);
    }
}

bool Group::intersect(const Ray &r, Hit &h, float tMin) {
    Hit hTmp;
    float tTmp = std::numeric_limits<float>::infinity();
    bool flagHasInter = false;
    for (int i = 0; i < objectNum; i++) {
        auto obj = objects[i];
        if (obj->intersect(r, hTmp, tMin) && hTmp.getT() < tTmp + EPSILON) {
            flagHasInter = true;
            h = hTmp;
            tTmp = h.getT();
        }
    }
    return flagHasInter;
}

void Group::paint() {
    for (int i = 0; i < objectNum; i++) {
        objects[i]->paint(); // iterate over objects and call paint()
    }
}
