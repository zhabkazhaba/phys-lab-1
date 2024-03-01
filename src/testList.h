//
// Created by zhabkazhaba on 2/29/24.
//

#ifndef PHYS_LAB_1_TESTLIST_H
#define PHYS_LAB_1_TESTLIST_H
#include <vector>

class testList {
private:
    constexpr static float g_acceleration = 9.8;
    std::vector<float> time_values;
    float av_time_value;
    float mass;
    float radius;
    float height;

    float impulse;
public:
    testList();
    testList(testList& o);
    ~testList() = default;
    float calculate_impulse();
    /**
     * @brief Overloaded operator that returns sum of impulses
     */
    float operator +(testList &o) const;
};


#endif //PHYS_LAB_1_TESTLIST_H
