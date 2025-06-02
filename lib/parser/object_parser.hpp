#pragma once

#include "objects.hpp"

#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct CommentSkipper : qi::grammar<Iterator> {
    CommentSkipper() : CommentSkipper::base_type(skip) {
        skip = qi::space |
               (qi::lit("//") >> *(qi::char_ - qi::eol) >> (qi::eol | qi::eoi));
    }
    qi::rule<Iterator> skip;
};

template <typename Iterator, typename Skipper>
struct ObjectParser : qi::grammar<Iterator, std::vector<Object>(), Skipper> {
    ObjectParser() : ObjectParser::base_type(start) {

        // возможно, стоит тут float_ заменить на double_
        point = qi::float_ >> qi::float_ >> qi::float_;
        optical = qi::float_ >> qi::float_ >> qi::float_ >> qi::float_ >>
                  qi::float_ >> qi::float_ >> qi::float_;

        sphere = qi::lit("SPHERE") >> point >> qi::float_ >> optical;
        box = qi::lit("BOX") >> point >> point >> optical;
        triangle = qi::lit("TRIANGLE") >> point >> point >> point >> optical;
        quad = qi::lit("QUADRANGLE") >> point >> point >> point >> point >>
               optical;

        object = sphere | box | triangle | quad;
        start = *object;
    }

    qi::rule<Iterator, Point(), Skipper> point;
    qi::rule<Iterator, OpticalProperties(), Skipper> optical;
    qi::rule<Iterator, Sphere(), Skipper> sphere;
    qi::rule<Iterator, Box(), Skipper> box;
    qi::rule<Iterator, Triangle(), Skipper> triangle;
    qi::rule<Iterator, Quadrangle(), Skipper> quad;
    qi::rule<Iterator, Object(), Skipper> object;
    qi::rule<Iterator, std::vector<Object>(), Skipper> start;
};

std::vector<Object> parse(std::istream& input);

/*!
 * Вернет true, если корректный конфиг
    */
bool validate(std::istream& input);
