#include "D:\Study\repository_folder\Zad1 (Zad3)\histogram.h"
#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

int main() {
    test_positive();
}
