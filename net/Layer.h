//
// Created by isha on 8/10/23.
//

#ifndef WEEGRAD_LAYER_H
#define WEEGRAD_LAYER_H


#include "../linearalg/Matrix.h"

class Layer {
    public:
        virtual Matrix* forward(Matrix* in) = 0;
};


#endif //WEEGRAD_LAYER_H
