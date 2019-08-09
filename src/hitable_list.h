#pragma once
#ifndef RAYTRACING_HITABLE_LIST_H
#define RAYTRACING_HITABLE_LIST_H

#include "hitable.h"

struct HitableList : public Hitable {
    HitableList() = default;
    HitableList(Hitable **_list, int _listSize) {
        list = _list;
        listSize = _listSize;
    }

    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const;

    Hitable **list;
    int listSize;
};

bool HitableList::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const {
    HitRecord tempRecord;
    bool hit = false;
    float closest = tMax;

    for (int i = 0; i < listSize; ++i) {
        if (list[i]->hit(ray, tMin, closest, tempRecord)) {
            hit = true;
            closest = tempRecord.t;
            record = tempRecord;
        }
    }
    return hit;
}

#endif // RAYTRACING_HITABLE_LIST_H