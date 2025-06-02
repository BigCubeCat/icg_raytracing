#pragma once

#include <boost/variant/variant.hpp>
#include <memory>
#include <string>
#include <vector>

#include "../linal/hittable.hpp"
#include "../linal/quad.hpp"
#include "../linal/sphere.hpp"
#include "../linal/triangle.hpp"
#include "objects.hpp"

using hittable = HittableIface<float>;

// Sphere, Box, Triangle, Quadrangle
struct HittableObjectVisitor
    : public boost::static_visitor<std::unique_ptr<hittable>> {
    std::unique_ptr<hittable> operator()(const Sphere& s) const {
        Eigen::Vector3f center(s.center.x, s.center.y, s.center.z);
        return std::make_unique<HittableSphere<float>>(center, s.radius);
    }
    std::unique_ptr<hittable> operator()(const Quadrangle& q) const {
        Eigen::Vector3f p1(q.p1.x, q.p1.y, q.p1.z);
        Eigen::Vector3f p2(q.p2.x, q.p2.y, q.p2.z);
        Eigen::Vector3f p3(q.p3.x, q.p3.y, q.p3.z);
        Eigen::Vector3f p4(q.p4.x, q.p4.y, q.p4.z);
        return std::make_unique<HittableQuad<float>>(p1, p2, p3, p4);
    }
    std::unique_ptr<hittable> operator()(const Box& b) const {
        Eigen::Vector3f p1(b.max.x, b.max.y, b.max.z);
        Eigen::Vector3f p2(b.min.x, b.min.y, b.min.z);
        Eigen::Vector3f p3(b.max.x - b.min.x, b.max.y - b.min.y,
                           b.max.z - b.min.z);

        return std::make_unique<HittableTriangle<float>>(p1, p2, p3);
    }
    std::unique_ptr<hittable> operator()(const Triangle& t) const {
        Eigen::Vector3f p1(t.p1.x, t.p1.y, t.p1.z);
        Eigen::Vector3f p2(t.p2.x, t.p2.y, t.p2.z);
        Eigen::Vector3f p3(t.p3.x, t.p3.y, t.p3.z);
        return std::make_unique<HittableTriangle<float>>(p1, p2, p3);
    }
};

class Parser {
   private:
    std::string m_text;
    bool m_valid;

   public:
    void set_text(const std::string& text);

    bool is_valid() const { return m_valid; }

    std::vector<std::unique_ptr<hittable>> operator()();

   private:
    std::unique_ptr<hittable> parse_object(const Object& object);
};
