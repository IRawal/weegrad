//
// Created by isha on 8/17/23.
//

#include "ActivationLayer.h"

Matrix *ActivationLayer::forward(Matrix *in) {
    return activate(in->copy());
}
Matrix* ActivationLayer::activate(Matrix* in) {
    for (int i = 0; i < in->rows; i++) {
        for (int j = 0; j < in->cols; j++) {
            in->elements[i][j] = f(in->elements[i][j]);
        }
    }
    return in;
}
/*Derivative of activation fn*/
Matrix* ActivationLayer::dactivate(Matrix* in) {
    for (int i = 0; i < in->rows; i++) {
        for (int j = 0; j < in->cols; j++) {
            in->elements[i][j] = f(in->elements[i][j]);
        }
    }
    return in;
}



