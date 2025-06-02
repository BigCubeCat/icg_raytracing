#include "object_parser.hpp"

bool validate(std::istream& input) {
    using Iterator = boost::spirit::istream_iterator;
    using Skipper = CommentSkipper<Iterator>;
    using Parser = ObjectParser<Iterator, Skipper>;

    // Настраиваем поток
    input.unsetf(
        std::ios::skipws);  // Важно! Отключаем автоматический пропуск пробелов
    Iterator begin(input);
    Iterator end;

    Skipper skipper;
    Parser parser;
    std::vector<Object> result;

    bool success = qi::phrase_parse(begin, end, parser, skipper, result);
    return success && (begin == end);
}

std::vector<Object> parse(std::istream& input) {
    using Iterator = boost::spirit::istream_iterator;
    using Skipper = CommentSkipper<Iterator>;
    using Parser = ObjectParser<Iterator, Skipper>;

    // Настраиваем поток
    input.unsetf(
        std::ios::skipws);  // Важно! Отключаем автоматический пропуск пробелов
    Iterator begin(input);
    Iterator end;

    Skipper skipper;
    Parser parser;
    std::vector<Object> result;

    bool success = qi::phrase_parse(begin, end, parser, skipper, result);

    if (!success || begin != end) {
        throw std::runtime_error("Parsing failed at position: " +
                                 std::to_string(input.tellg()));
    }

    return result;
}
