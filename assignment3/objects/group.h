#pragma once
#include "object3d.h"

class Group : public Object3D {
public:
    explicit Group(int objectNum) : objectNum(objectNum) {
        assert(objectNum > 0);
        objects = new Object3D *[objectNum];
    }

    Group() : Group(1) {}

    ~Group() {
        delete[] objects;
    }

    void addObject(int index, Object3D *object);

    bool intersect(const Ray &r, Hit &h, float tMin) override;
    virtual void paint(void);

private:
    int objectNum;
    Object3D **objects;
};