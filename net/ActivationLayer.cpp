//
// Created by isha on 8/17/23.
//

#include "ActivationLayer.h"

Matrix *ActivationLayer::forward(Matrix *in) {
    return in->copy()->broadcast([this](double d){return f(d);});
}


