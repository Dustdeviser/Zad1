#pragma once
#define HISTOGRAM_H_INCLUDED
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
void find_minmax(const vector<double>& numbers, double& min, double& max);
vector<double> input_numbers(size_t number_count);

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count);
void svg_begin(double width, double height);
void svg_end();

void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height,
              string stroke = "black", string fill = "red");

void show_histogram_svg(const vector<size_t>& bins);
