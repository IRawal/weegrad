//
// Created by isha on 8/17/23.
//

#ifndef WEEGRAD_ACTIVATIONLAYER_H
#define WEEGRAD_ACTIVATIONLAYER_H


#include "Layer.h"

class ActivationLayer : public Layer {
    public:
        virtual double f(double x) = 0;
        virtual double dfdx(double x) = 0;
        Matrix* forward(Matrix* in);
};


#endif //WEEGRAD_ACTIVATIONLAYER_H
