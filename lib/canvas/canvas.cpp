#include "canvas.hpp"

#include "../linal/shading.hpp"

#include <QKeyEvent>
#include <QPainter>

Canvas::Canvas(DataModel* data, QWidget* parent)
    : QWidget(parent),
      m_data(data)
      // Инициализиуем камеру где-нибудь «в точке (0,0,0), смотрит на (0,0,-1), up=(0,1,0)»,
      // fov=45°, aspect чётко по размеру виджета (установим .resizeEvent())
      ,
      m_camera(Eigen::Vector3f(0, 0, 5), Eigen::Vector3f(0, 0, 0),
               Eigen::Vector3f(0, 1, 0), 45.0f,
               float(width()) / float(height())) {
    setFocusPolicy(Qt::StrongFocus);  // чтобы получать keyPressEvent
}

void Canvas::setScene(
    std::vector<std::shared_ptr<HittableIface<float>>>&& objects,
    const std::vector<PointLight>& lights_) {
    m_scene_objects = objects;
    m_lights = lights_;
    m_need_render = true;
    update();  // вызовет paintEvent
}

void Canvas::resizeEvent(QResizeEvent* event) {
    int w = event->size().width();
    int h = event->size().height();
    if (w <= 0 || h <= 0)
        return;
    // Пересоздаём QImage под новый размер
    m_image = QImage(w, h, QImage::Format_RGB32);
    // Обновляем aspect_ratio камеры
    m_camera.updateOrientation(
        m_camera.position() -
            (-m_camera.front()),  // мы хотим сохранить lookat так же?
        Eigen::Vector3f(0, 1, 0), 45.0f, float(w) / float(h));
    m_need_render = true;
    update();
}

void Canvas::paintEvent(QPaintEvent* /*event*/) {
    if (m_need_render) {
        renderScene();
        m_need_render = false;
    }
    QPainter painter(this);
    painter.drawImage(0, 0, m_image);
}

void Canvas::keyPressEvent(QKeyEvent* event) {
    // Простая WASD-навигация: W=вперед, S=назад, A=влево, D=вправо
    float speed = m_camera.getMoveSpeed();
    Eigen::Vector3f pos = m_camera.position();
    Eigen::Vector3f front = m_camera.front();  // направление вперёд
    Eigen::Vector3f world_up(0, 1, 0);

    if (event->key() == Qt::Key_W) {
        pos += speed * front;
        m_camera.setPosition(pos);
        m_need_render = true;
    } else if (event->key() == Qt::Key_S) {
        pos -= speed * front;
        m_camera.setPosition(pos);
        m_need_render = true;
    } else if (event->key() == Qt::Key_A) {
        // влево = cross(world_up, front)
        Eigen::Vector3f left = world_up.cross(front).normalized();
        pos += speed * left;
        m_camera.setPosition(pos);
        m_need_render = true;
    } else if (event->key() == Qt::Key_D) {
        Eigen::Vector3f right = front.cross(world_up).normalized();
        pos += speed * right;
        m_camera.setPosition(pos);
        m_need_render = true;
    }
    // Можно добавить Q/E для подъёма/спуска по оси Y
    else if (event->key() == Qt::Key_Q) {
        pos += speed * world_up;
        m_camera.setPosition(pos);
        m_need_render = true;
    } else if (event->key() == Qt::Key_E) {
        pos -= speed * world_up;
        m_camera.setPosition(pos);
        m_need_render = true;
    }
    if (m_need_render) {
        update();  // вызовет paintEvent
    }
}

// Основная функция трассировки
void Canvas::renderScene() {
    int img_w = m_image.width();
    int img_h = m_image.height();
    // Преобразуем в [0,255]
    auto toInt = [](float x) {
        x = std::clamp(x, 0.0F, 0.999F);
        return static_cast<int>(256 * x);
    };

// Для каждого пикселя (x,y) отрисовываем цвет
#pragma omp parallel for schedule(dynamic)  // если хотим multithread
    for (int j = 0; j < img_h; ++j) {
        for (int i = 0; i < img_w; ++i) {
            // Нормализуем координаты в [0,1]
            float u = static_cast<float>(i) / static_cast<float>(img_w - 1);
            // В Qt y=0 — сверху, но в математике t=0 — снизу, поэтому:
            float v =
                1.0F - (static_cast<float>(j) / static_cast<float>(img_h - 1));
            Ray<float> r = m_camera.get_ray(u, v);

            // 1) Находим ближайший hit: перебираем все объекты, выбирая минимальное t
            HitRecord<float> closest_rec;
            float t_closest = std::numeric_limits<float>::infinity();
            bool hit_anything = false;

            for (const auto& obj : m_scene_objects) {
                HitRecord<float> temp_rec;
                if (obj->hit(r, 0.001F, t_closest, temp_rec)) {
                    hit_anything = true;
                    t_closest = temp_rec.m_t;
                    closest_rec = temp_rec;
                }
            }

            Eigen::Vector3f pixel_color;
            if (hit_anything) {
                // Для простоты возьмём только первый источник света
                // (или можно суммировать по всем)
                if (!m_lights.empty()) {
                    pixel_color =
                        phong_shade(closest_rec, r, m_lights[0], 0.1F);
                } else {
                    pixel_color = closest_rec.albedo *
                                  0.1F;  // только ambient, если нет света
                }
            } else {
                // Фон (градиент неба, например)
                Eigen::Vector3f unit_direction = r.m_direction.normalized();
                float t_bg = 0.5F * (unit_direction.y() + 1.0F);
                // линейный градиент от белого внизу до голубого вверху:
                pixel_color =
                    (1.0F - t_bg) * Eigen::Vector3f(1.0F, 1.0F, 1.0F) +
                    t_bg * Eigen::Vector3f(0.5F, 0.7F, 1.0F);
            }

            int ir = toInt(pixel_color.x());
            int ig = toInt(pixel_color.y());
            int ib = toInt(pixel_color.z());

            // В Qt: setPixel(x, y, QColor::rgb())
            // TODO: ОПТИМИЗИРОВАТЬ
            m_image.setPixel(i, j, qRgb(ir, ig, ib));
        }
    }
}
