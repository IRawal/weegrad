//
// Created by isha on 8/19/23.
//

#include "Sigmoid.h"

#include <cmath>

Sigmoid::Sigmoid() {
    this->type = LayerType::ActivationFn;
}

double Sigmoid::f(double x) {
    return 1 / (1 + exp(-x));
}

double Sigmoid::dfdx(double x) {
    double enegx = exp(-x);
    return enegx / pow((1 + enegx), 2);
}
