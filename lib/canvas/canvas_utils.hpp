#pragma once

#include <Eigen/Dense>
#include <QColor>
#include <QPoint>

#include "../spline/point.hpp"

QColor interpolate_color(const QColor& near, const QColor& far, double t,
                         double min, double max);

void make_view_matrix(Eigen::Matrix4d& dest, const Eigen::Vector3d& eye,
                      const Eigen::Vector3d& center, const Eigen::Vector3d& up);

void make_projection_matrix(Eigen::Matrix4d& dest, double zn, double zf,
                            double sw, double sh);

void make_rotation_matrix(Eigen::Matrix4d& dest, double x, double y);

QPointF project_point(const Point3D& v, const Eigen::Matrix4d& func,
                      const Eigen::Matrix4d& proj, int width, int height,
                      double& depth);
