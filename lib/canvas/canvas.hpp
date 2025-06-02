#pragma once

#include <QPainter>
#include <QWidget>
#include "model.hpp"

#include "../linal/camera.hpp"
#include "../linal/light.hpp"

const double kDefaultZn = 1.0;

class Canvas : public QWidget {
    Q_OBJECT

   public:
    explicit Canvas(DataModel* data, QWidget* parent = nullptr);
    // Установить сцену (список объектов) и источники света извне
    void setScene(
        const std::vector<std::shared_ptr<HittableIface<float>>>& objects,
        const std::vector<PointLight>& lights);

   protected:
    // От Qt: при изменении размера виджета
    void resizeEvent(QResizeEvent* event) override;
    // От Qt: когда нужно перерисовать
    void paintEvent(QPaintEvent* event) override;
    // От Qt: обрабатывать нажатия клавиш, чтобы двигать камеру
    void keyPressEvent(QKeyEvent* event) override;

    // Слот для изменения позиции камеры / ориентации
   public slots:
    void moveCameraForward() {}
    void moveCameraBackward() {}
    void moveCameraLeft() {}
    void moveCameraRight() {}
    void rotateCamera(float yaw_delta, float pitch_delta) {}

   private:
    DataModel* m_data;
    Camera<float> m_camera;
    std::vector<std::shared_ptr<HittableIface<float>>> m_scene_objects;
    std::vector<PointLight> m_lights;
    QImage m_image;  // сюда рендерим
    bool m_need_render = true;

    void renderScene();  // основной метод трассировки
};
