//
// Created by isha on 8/8/23.
//

#include "tests.h"
#include "../net/dense.h"

void test_mult() {

}
void test_dense() {
    dense layer = dense(2, 1);
    matrix vec = matrix(1, 2);
    layer.forward(&vec).print();
}