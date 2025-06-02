#pragma once

#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

struct Point {
    float x, y, z;
};

struct OpticalProperties {
    float KDr, KDg, KDb;
    float KSr, KSg, KSb;
    float Power;
};

struct Sphere {
    Point center;
    float radius;
    OpticalProperties optical;
};

struct Box {
    Point min, max;
    OpticalProperties optical;
};

struct Triangle {
    Point p1, p2, p3;
    OpticalProperties optical;
};

struct Quadrangle {
    Point p1, p2, p3, p4;
    OpticalProperties optical;
};

using Object = boost::variant<Sphere, Box, Triangle, Quadrangle>;

BOOST_FUSION_ADAPT_STRUCT(Point, x, y, z)
BOOST_FUSION_ADAPT_STRUCT(OpticalProperties, KDr, KDg, KDb, KSr, KSg, KSb,
                          Power)
BOOST_FUSION_ADAPT_STRUCT(Sphere, center, radius, optical)
BOOST_FUSION_ADAPT_STRUCT(Box, min, max, optical)
BOOST_FUSION_ADAPT_STRUCT(Triangle, p1, p2, p3, optical)
BOOST_FUSION_ADAPT_STRUCT(Quadrangle, p1, p2, p3, p4, optical)
