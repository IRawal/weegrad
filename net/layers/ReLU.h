//
// Created by isha on 8/10/23.
//

#ifndef WEEGRAD_RELU_H
#define WEEGRAD_RELU_H

#include "../ActivationLayer.h"

class ReLU : public ActivationLayer {
    public:
        ReLU();
        float f(float x);
        float dfdx(float x);
};


#endif //WEEGRAD_RELU_H
