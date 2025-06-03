#pragma once

#include <qcolor.h>
#include <qobject.h>
#include <memory>

#include "../scene/scene.hpp"

class DataModel : public QObject {
    Q_OBJECT
   public:
    std::weak_ptr<SceneConfig> m_config;
    double m_zn;

    double m_rot_x;
    double m_rot_y;
    QColor m_near;
    QColor m_far;

    explicit DataModel(QObject* parent = nullptr) : QObject(parent) {}

    std::weak_ptr<SceneConfig> config() const { return m_config; }

    void set_config(std::weak_ptr<SceneConfig>& config) { m_config = config; }
};
