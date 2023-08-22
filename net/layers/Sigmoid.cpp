//
// Created by isha on 8/19/23.
//

#include "Sigmoid.h"

#include <cmath>

Sigmoid::Sigmoid() {
    this->type = LayerType::ActivationFn;
}

float Sigmoid::f(float x) {
    return 1 / (1 + exp(-x));
}

float Sigmoid::dfdx(float x) {
    float enegx = exp(-x);
    return enegx / pow((1 + enegx), 2);
}
