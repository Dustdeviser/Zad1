#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "histogram.h"
using namespace std;

int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;
    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins);
}
