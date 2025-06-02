#pragma once

#include <qcolor.h>
#include <qobject.h>
#include <vector>

#include "../linal/hittable.hpp"

class DataModel : public QObject {
    Q_OBJECT
   public:
    std::vector<HittableIface<float>> m_objects;
    double m_zn;

    double m_rot_x;
    double m_rot_y;
    QColor m_near;
    QColor m_far;

    explicit DataModel(QObject* parent = nullptr) : QObject(parent) {}
};
