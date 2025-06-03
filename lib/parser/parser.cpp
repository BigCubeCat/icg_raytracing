#include "parser.hpp"
#include <qcolor.h>
#include <QDebug>
#include <boost/variant/detail/apply_visitor_binary.hpp>
#include <istream>
#include <sstream>
#include "object_parser.hpp"

void Parser::set_objects_text(const std::string& text) {
    m_objects = text;
    std::stringstream stream(m_objects);
    m_valid = validate(stream);
}

void Parser::set_header(const std::string& text) {
    m_header = text;

    // Чтение рассеянного света
    std::stringstream stream(m_header);
    int ar;
    int ag;
    int ab;
    stream >> ar >> ag >> ab;
    m_config->m_ambient_color = QColor(ar, ag, ab);
    int num_lights;
    stream >> num_lights;
    for (int i = 0; i < num_lights; ++i) {
        float lx;
        float ly;
        float lz;
        int lr;
        int lg;
        int lb;
        stream >> lx >> ly >> lz >> lr >> lg >> lb;
        m_config->m_lights.push_back({lx, ly, lz});
        m_config->m_colors.emplace_back(lr, lg, lb);
    }
}

void Parser::set_scene(const std::string& text) {
    m_scene = text;
    std::stringstream stream(m_scene);
    int br;
    int bg;
    int bb;
    stream >> br >> bg >> bb;
    qDebug() << br << " " << bg << " " << bb;
    m_config->m_background_color = QColor(br, bg, bb);
    qDebug() << m_config->m_background_color;

    stream >> m_config->m_gamma;
    qDebug() << m_config->m_gamma;
    stream >> m_config->m_depth;
    qDebug() << m_config->m_depth;

    stream >> m_config->m_camera_position[0] >>
        m_config->m_camera_position[1] >> m_config->m_camera_position[2];
    qDebug() << m_config->m_camera_position[0];
    stream >> m_config->m_view_point[0] >> m_config->m_view_point[1] >>
        m_config->m_view_point[2];
    qDebug() << m_config->m_view_point[0];
    stream >> m_config->m_up_vector[0] >> m_config->m_up_vector[1] >>
        m_config->m_up_vector[2];
    qDebug() << m_config->m_up_vector[0];
    stream >> m_config->m_zn >> m_config->m_zf;
    qDebug() << m_config->m_zn << " " << m_config->m_zf;
    stream >> m_config->m_sw >> m_config->m_sh;
}

bool Parser::is_valid() const {
    return m_valid;
}

std::weak_ptr<SceneConfig> Parser::operator()() {
    std::stringstream stream(m_objects);
    auto objects = parse(stream);
    m_config->m_objects.clear();
    m_config->m_objects.reserve(objects.size());
    HittableObjectVisitor visitor;
    for (const auto& object : objects) {
        m_config->m_objects.push_back(boost::apply_visitor(visitor, object));
    }
    return m_config;
}
