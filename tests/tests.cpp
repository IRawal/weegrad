//
// Created by isha on 8/8/23.
//

#include "tests.h"
#include "../net/Dense.h"

void test_mult() {

}
void test_dense() {
    Dense layer = Dense(2, 1);
    Matrix vec = Matrix(1, 2);
    layer.forward(&vec).print();
}