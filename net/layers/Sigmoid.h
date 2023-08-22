//
// Created by isha on 8/19/23.
//

#ifndef WEEGRAD_SIGMOID_H
#define WEEGRAD_SIGMOID_H


#include "../ActivationLayer.h"

class Sigmoid : public ActivationLayer {
    public:
        Sigmoid();
        float f(float x);
        float dfdx(float x);
};


#endif //WEEGRAD_SIGMOID_H
