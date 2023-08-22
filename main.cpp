#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <filesystem>
#include <random>

#include "linearalg/Matrix.h"
#include "linearalg/Ops.h"
#include "net/Net.h"
#include "net/layers/ReLU.h"
#include "net/layers/Sigmoid.h"

#include "tests/tests.h"
int main() {
    test_nn_mult();
}

