#include "model.hpp"

void DataModel::set_objects(
    std::vector<std::shared_ptr<HittableIface<float>>>&& objects) {
    m_objects = std::move(objects);
}
