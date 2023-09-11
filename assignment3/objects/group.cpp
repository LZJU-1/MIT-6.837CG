#include "group.h"

void Group::addObject(int index, Object3D *object) {
    assert(index < objectNum);
    objects[index] = object;
}

bool Group::intersect(const Ray &r, Hit &h, float tMin) {
    Hit hTmp;
    float tTmp = -1;
    bool flagHasInter = false;
    for (int i = 0; i < objectNum; i++) {
        auto obj = objects[i];
        if (obj->intersect(r, hTmp, tMin) &&(hTmp.getT() < tTmp || tTmp == -1)) {
            flagHasInter = true;
            h = hTmp;
            tTmp = h.getT();
        }
    }
    return flagHasInter;
}

void Group::paint(void) {
    for(int i = 0; i < objectNum; i++) {
        Object3D* one = objects[i];
        one->paint();
    }
}