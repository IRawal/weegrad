//
// Created by isha on 8/22/23.
//

#ifndef WEEGRAD_TANH_H
#define WEEGRAD_TANH_H


#include "../ActivationLayer.h"

class Tanh : public ActivationLayer {
public:
    Tanh();

    float f(float x);

    float dfdx(float x);
};


#endif //WEEGRAD_TANH_H
