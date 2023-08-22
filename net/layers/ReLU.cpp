//
// Created by isha on 8/10/23.
//

#include <cstdio>
#include "ReLU.h"

ReLU::ReLU() {
    this->type = LayerType::ActivationFn;
}
float ReLU::f(float x) {
    if (x < 0)
        return 0;
    else
        return x;
}
float ReLU::dfdx(float x) {
    if (x < 0)
        return 0.0001;
    else
        return 1;
}
