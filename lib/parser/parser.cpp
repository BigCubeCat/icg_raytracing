#include "parser.hpp"
#include <boost/variant/detail/apply_visitor_binary.hpp>
#include <sstream>
#include "object_parser.hpp"

void Parser::set_text(const std::string& text) {
    m_text = text;
    std::stringstream stream(m_text);
    m_valid = validate(stream);
}

bool Parser::is_valid() const {
    return m_valid;
}

std::vector<std::shared_ptr<HittableIface<float>>> Parser::operator()() {
    if (!m_valid) {
        return {};
    }
    std::stringstream stream(m_text);
    auto objects = parse(stream);
    std::vector<std::shared_ptr<hittable>> result;
    result.reserve(objects.size());
    HittableObjectVisitor visitor;
    for (const auto& object : objects) {
        result.push_back(boost::apply_visitor(visitor, object));
    }
    return result;
}
