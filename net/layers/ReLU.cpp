//
// Created by isha on 8/10/23.
//

#include <cstdio>
#include "ReLU.h"

ReLU::ReLU() {
    this->type = LayerType::ActivationFn;
}
double ReLU::f(double x) {
    if (x < 0)
        return 0;
    else
        return x;
}
double ReLU::dfdx(double x) {
    if (x < 0)
        return 0.0001;
    else
        return 1;
}
