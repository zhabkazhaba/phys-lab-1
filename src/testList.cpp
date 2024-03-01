#include <numeric>
#include "testList.h"
#include <numeric>
#include <stdexcept>

testList::testList() {
    mass = 0.0f;
    radius = 0.0f;
    height = 0.0f;
    av_time_value = 0.0f;
    impulse = 0.0f;
}

testList::testList(testList &o) {
    mass = o.mass;
    radius = o.radius;
    height = o.height;
    av_time_value = o.av_time_value;
    impulse = o.impulse;
}

float testList::calculate_impulse() {
    if (time_values.empty())
        throw std::runtime_error("Time values list is empty");
    float tmp_impulse;
    av_time_value = std::accumulate(time_values.begin(), time_values.end(), 0.0f) / (float) (time_values.size());
    tmp_impulse = (mass * radius * radius * (g_acceleration * av_time_value * av_time_value - 2 * height))
                  / (2 * height);
    impulse = tmp_impulse;
    return tmp_impulse;
}

float testList::operator+(testList &o) const {
    return impulse + o.impulse;
}