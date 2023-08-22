//
// Created by isha on 8/17/23.
//

#ifndef WEEGRAD_ACTIVATIONLAYER_H
#define WEEGRAD_ACTIVATIONLAYER_H


#include "Layer.h"

class ActivationLayer : public Layer {
    public:
        virtual float f(float x) = 0;
        virtual float dfdx(float x) = 0;
        Matrix* forward(Matrix* in) override;
        Matrix *activate(Matrix *in);
        Matrix *dactivate(Matrix *in);
};


#endif //WEEGRAD_ACTIVATIONLAYER_H
