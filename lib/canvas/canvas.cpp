#include "canvas.hpp"

#include <qevent.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qpainterpath.h>
#include <qtpreprocessorsupport.h>
#include <qwidget.h>
#include <QTimer>

const int kAxesSize = 50;

const double kZoomStep = 0.1;
const double kMaxZoom = 3;
const double kMinZoom = 0.3;
const double kSensitivity = 0.5;  // чувствительность

Canvas::Canvas(QWidget* parent, DataModel* model)
    : QWidget(parent), m_data(model) {
    m_point_cam = Eigen::Vector3d(-10, 0, 0);
    m_point_view = Eigen::Vector3d(10, 0, 0);
    m_vec_up = Eigen::Vector3d(0, 1, 0);
}

void Canvas::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
}

void Canvas::pallete_changed(const QColor& a, const QColor& b) {}

void Canvas::mousePressEvent(QMouseEvent* event) {}

void Canvas::mouseMoveEvent(QMouseEvent* event) {}

void Canvas::mouseReleaseEvent(QMouseEvent* event) {}

void Canvas::mouseDoubleClickEvent(QMouseEvent* event) {}

void Canvas::wheelEvent(QWheelEvent* event) {}

void Canvas::update_from_data() {}

void Canvas::draw_axes(QPainter& painter) {}

void Canvas::keyPressEvent(QKeyEvent* event) {}

void Canvas::keyReleaseEvent(QKeyEvent* event) {}
