//
// Created by isha on 8/22/23.
//

#include "Tanh.h"

#include <cmath>

Tanh::Tanh() {
    this->type = LayerType::ActivationFn;
}
float Tanh::f(float x) {
    return std::tanh(x);
}
float Tanh::dfdx(float x) {
    return 1 - powf(std::tanh(x), 2);
}