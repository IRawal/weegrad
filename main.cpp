#include <iostream>

#include "linearalg/matrix.h"
#include "linearalg/ops.h"

int main() {
    matrix m = matrix(2, 1);
    m.transpose();
    m.print();
    return 0;
}
